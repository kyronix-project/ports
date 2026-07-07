#include "memory.h"
#include "common/io.h"

const char* ffDetectMemory(FFMemoryResult* ram) {
    FF_STRBUF_AUTO_DESTROY buf = ffStrbufCreate();

    if (!ffAppendFileBuffer("/proc/meminfo", &buf)) {
        return "ffAppendFileBuffer(\"/proc/meminfo\", ...)";
    }

    uint64_t memTotal = 0,
             memAvailable = 0,
             shmem = 0,
             memFree = 0,
             buffers = 0,
             cached = 0,
             sReclaimable = 0;

    char* token = NULL;
    if ((token = memmem(buf.chars, buf.length, "MemTotal:", strlen("MemTotal:"))) != NULL) {
        memTotal = strtoul(token + strlen("MemTotal:"), NULL, 10);
    } else {
        return "MemTotal not found in /proc/meminfo";
    }

    if ((token = memmem(buf.chars, buf.length, "MemAvailable:", strlen("MemAvailable:"))) != NULL) {
        memAvailable = strtoul(token + strlen("MemAvailable:"), NULL, 10);
    }

    if (memAvailable == 0 || memAvailable >= memTotal) {
        if ((token = memmem(buf.chars, buf.length, "MemFree:", strlen("MemFree:"))) != NULL) {
            memFree = strtoul(token + strlen("MemFree:"), NULL, 10);
        }

        if ((token = memmem(buf.chars, buf.length, "Buffers:", strlen("Buffers:"))) != NULL) {
            buffers = strtoul(token + strlen("Buffers:"), NULL, 10);
        }

        if ((token = memmem(buf.chars, buf.length, "Cached:", strlen("Cached:"))) != NULL) {
            cached = strtoul(token + strlen("Cached:"), NULL, 10);
        }

        if ((token = memmem(buf.chars, buf.length, "Shmem:", strlen("Shmem:"))) != NULL) {
            shmem = strtoul(token + strlen("Shmem:"), NULL, 10);
        }

        if ((token = memmem(buf.chars, buf.length, "SReclaimable:", strlen("SReclaimable:"))) != NULL) {
            sReclaimable = strtoul(token + strlen("SReclaimable:"), NULL, 10);
        }

        memAvailable = memFree + buffers + cached + sReclaimable - shmem;
    }

    ram->bytesTotal = memTotal * 1024lu;
    ram->bytesUsed = (memTotal - memAvailable) * 1024lu;

    uint64_t arcSize = 0;
    FF_STRBUF_AUTO_DESTROY arc = ffStrbufCreate();
    if (ffAppendFileBuffer("/proc/spl/kstat/zfs/arcstats", &arc) && arc.length > 0) {
        const char* p = memchr(arc.chars, '\n', arc.length);
        if (p != NULL) {
            ++p;
            size_t remaining = arc.length - (size_t)(p - arc.chars);
            const char* pData = memmem(p, remaining, "data\n", strlen("data\n"));
            if (pData != NULL) {
                uint32_t dataOffset = (uint32_t)(pData - p);
                p += dataOffset + strlen("data\n");
                remaining = arc.length - (size_t)(p - arc.chars);
                if ((token = memmem(p, remaining, "\nsize ", strlen("\nsize "))) != NULL) {
                    arcSize = strtoul(token + 1 + dataOffset, NULL, 10);
                    if (arcSize > 0) {
                        uint64_t arcMin = 0;
                        if ((token = memmem(p, remaining, "\nc_min ", strlen("\nc_min "))) != NULL) {
                            arcMin = strtoul(token + 1 + dataOffset, NULL, 10);
                            if (arcSize > arcMin) {
                                arcSize -= arcMin;
                                if (ram->bytesUsed > arcSize) {
                                    ram->bytesUsed -= arcSize;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return NULL;
}
