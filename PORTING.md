# Porting Guide

This document explains how to add a new port to the Kyronix Ports Collection.

## Directory layout

Ports are grouped by category. Existing categories:

- `compilers/` - compilers and assemblers, for example nasm, tcc.
- `interpreters/` - language interpreters, for example lua, perl.
- `tools/` - tools, for example bmake, gmake.
- `utils/` - general command line utilities, for example fastfetch.
- `wm/` - window managers, for example jwm.

Place the port source tree under the matching category directory, for example `interpreters/foo`.

If none of the existing categories fit, create a new one. Use a short, lowercase directory name that describes the category (for example `libs/` for libraries, `net/` for networking tools), and put the port source tree inside it the same way as for the existing categories.

## Build target

Kyronix uses musl libc, not glibc. A binary built against glibc will not run on Kyronix. Keep this in mind while building a port:

- Compile with a musl toolchain (for example `musl-gcc`, or a cross compiler targeting `*-linux-musl`).
- Prefer static linking when possible, so the binary does not depend on shared libraries that may be missing on Kyronix.
- After building, check the binary is not linked against glibc, for example with `file <binary>` or `ldd <binary>`.

## Testing in Kyronix

A port is not done until it has been tested inside a real Kyronix rootfs.

1. Copy the compiled binary into the rootfs.
2. Do not put test binaries in `/bin/`. The `/bin` directory is overwritten every time `make` and `make run` are executed, so anything placed there will be lost.
3. Run `make` and `make run` to boot Kyronix, then confirm the binary runs and behaves as expected.

## Reporting issues

If something is broken, missing, or needs a workaround, write it down in a `note.md` or `note.txt` file inside the port directory. Keep notes short and specific, for example what does not work and why.

## Checklist for a new port

- [ ] Source added under the correct category directory
- [ ] Compiled for Linux musl, not glibc
- [ ] Tested by copying the binary to `/usr/bin` in a Kyronix rootfs
- [ ] Issues or remarks documented in `note.md` or `note.txt`, if any
