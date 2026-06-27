#!/usr/bin/env python3
"""Generate CMake-style headers for fastfetch: fastfetch_config.h, fastfetch_datatext.h, logo_builtin.h"""
import os, sys, json, re, glob

SRC_DIR = os.path.join(os.path.dirname(__file__), "src")
OUT_DIR = os.path.join(os.path.dirname(__file__), "gen")

def c_escape(s):
    s = s.rstrip("\n")
    s = s.replace("\\", "\\\\")
    s = s.replace("\n", "\\n")
    s = s.replace('"', '\\"')
    result = []
    for c in s:
        if ord(c) < 32 and c != '\t':
            result.append(f'\\x{ord(c):02x}')
        else:
            result.append(c)
    return '"' + ''.join(result) + '"'

def gen_fastfetch_config():
    content = """#pragma once

#define FASTFETCH_PROJECT_NAME "fastfetch"
#define FASTFETCH_PROJECT_VERSION "2.65.1"
#define FASTFETCH_PROJECT_VERSION_MAJOR 2
#define FASTFETCH_PROJECT_VERSION_MINOR 65
#define FASTFETCH_PROJECT_VERSION_PATCH 1
#define FASTFETCH_PROJECT_VERSION_GIT ""
#define FASTFETCH_PROJECT_VERSION_TWEAK ""
#define FASTFETCH_PROJECT_VERSION_TWEAK_NUM 0
#define FASTFETCH_PROJECT_CMAKE_BUILD_TYPE "Release"
#define FASTFETCH_PROJECT_HOMEPAGE_URL "https://github.com/fastfetch-cli/fastfetch"
#define FASTFETCH_PROJECT_DESCRIPTION "A neofetch-like tool for fetching system information"
#define FASTFETCH_PROJECT_LICENSE "MIT"

#define FASTFETCH_TARGET_DIR_ROOT "/"
#define FASTFETCH_TARGET_DIR_USR "/usr"
#define FASTFETCH_TARGET_DIR_HOME "/home"
#define FASTFETCH_TARGET_DIR_ETC "/etc"

#define FASTFETCH_TARGET_DIR_INSTALL_SYSCONF "/etc"

#define FF_PACKAGES_DISABLE_LIST FF_PACKAGES_FLAG_NONE
"""
    os.makedirs(OUT_DIR, exist_ok=True)
    with open(os.path.join(OUT_DIR, "fastfetch_config.h"), "w") as f:
        f.write(content)

def gen_fastfetch_datatext():
    help_path = os.path.join(SRC_DIR, "..", "doc", "help.json")
    with open(help_path) as f:
        help_data = json.load(f)
    help_json = json.dumps(help_data, separators=(',', ':'))
    help_escaped = c_escape(help_json)

    # Minimal default structure with only modules we keep
    default_structure = "Title:Separator:OS:Host:Kernel:Uptime:Shell:Terminal:TerminalFont:TerminalSize:CPU:CPUUsage:Memory:Swap:Processes:LoadAvg:Locale:Users:Editor:Command:DateTime:Version:Display:LibC:Break:Colors"

    content = f"""#pragma once

#define FASTFETCH_DATATEXT_JSON_HELP {help_escaped}
#define FASTFETCH_DATATEXT_STRUCTURE "{default_structure}"
"""
    os.makedirs(OUT_DIR, exist_ok=True)
    with open(os.path.join(OUT_DIR, "fastfetch_datatext.h"), "w") as f:
        f.write(content)

def gen_logo_builtin():
    logo_dir = os.path.join(SRC_DIR, "logo", "ascii")
    lines = ["#pragma once", '#pragma GCC diagnostic ignored "-Wtrigraphs"', ""]
    for letter_dir in sorted(glob.glob(os.path.join(logo_dir, "[a-z_]"))):
        for txt_file in sorted(glob.glob(os.path.join(letter_dir, "*.txt"))):
            name = os.path.splitext(os.path.basename(txt_file))[0]
            with open(txt_file) as f:
                content = f.read()
            escaped = c_escape(content)
            macro_name = f"FASTFETCH_DATATEXT_LOGO_{name.upper()}"
            lines.append(f"#define {macro_name} {escaped}")
    lines.append("")
    os.makedirs(OUT_DIR, exist_ok=True)
    with open(os.path.join(OUT_DIR, "logo_builtin.h"), "w") as f:
        f.write("\n".join(lines))

if __name__ == "__main__":
    gen_fastfetch_config()
    gen_fastfetch_datatext()
    gen_logo_builtin()
    print("Headers generated in", OUT_DIR)
