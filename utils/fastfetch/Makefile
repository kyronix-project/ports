CC = musl-gcc
CFLAGS = -static -no-pie -O2 -march=x86-64 -std=c11 -g0 \
	 -D_GNU_SOURCE -D_XOPEN_SOURCE -D_ATFILE_SOURCE \
	 -I src/ -I gen/ -I include/ \
	 -Wno-trigraphs -Wno-unused-parameter -Wno-unused-variable \
	 -Wno-unused-function -Wno-missing-braces \
	 -ffunction-sections -fdata-sections

LDFLAGS = -static -lm -Wl,--gc-sections -Wl,--print-gc-sections

# Modules to keep enabled (not disabled)
KEEP_MODULES = BREAK COLORS COMMAND CPU CPUCACHE CPUUSAGE DATETIME \
	       DISPLAY EDITOR HOST KERNEL LOADAVG LOCALE LOGO MEMORY \
	       OS PROCESSES SEPARATOR SHELL SWAP TERMINAL TERMINALFONT \
	       TERMINALSIZE TERMINALTHEME TITLE UPTIME USERS VERSION

# Generate disable defines for all modules not in KEEP_MODULES
ALL_MODULES = BATTERY BIOS BLUETOOTH BLUETOOTHRADIO BOARD BOOTMGR \
	      BRIGHTNESS BTRFS CAMERA CHASSIS CODEC CURSOR CUSTOM DE \
	      DISK DISKIO DNS FONT GAMEPAD GPU ICONS INITSYSTEM KEYBOARD \
	      LM LOCALIP MEDIA MONITOR MOUSE NETIO OPENCL OPENGL PACKAGES \
	      PHYSICALDISK PHYSICALMEMORY PLAYER POWERADAPTER PUBLICIP \
	      SOUND THEME TPM VULKAN WALLPAPER WEATHER WIFI WM WMTHEME ZPOOL

DISABLE_FLAGS = $(foreach mod,$(ALL_MODULES),$(if $(filter $(mod),$(KEEP_MODULES)),,-DFF_MODULE_DISABLE_$(mod)=1))

# Feature flags (only positive ones - undefined = false for the preprocessor)
FEATURE_FLAGS = -DFF_HAVE_PIPE2=1 -DFF_DISABLE_DLOPEN=1 -DFF_ENABLE_WCWIDTH=1 -fno-link-libatomic

# Collect all .c files, excluding platform-specific and problematic ones
SRC_DIR = src
SRCS = $(shell find $(SRC_DIR) -name '*.c' \
	! -path '*/tests/*' \
	! -name '*_apple*' \
	! -name '*_windows*' \
	! -path '*/windows/*' \
	! -path '*/apple/*' \
	! -name '*_android*' \
	! -name '*_obsd*' \
	! -name '*_nbsd*' \
	! -name '*_haiku*' \
	! -name '*_sunos*' \
	! -name '*_gnu*' \
	! -name '*_mac*' \
	! -name '*_bsd*' \
	! -name '*_nosupport*' \
	! -path '*/logo/image/*' \
	! -path '*/displayserver/linux/wayland/*' \
	! -name '*gpu_drm*' \
	! -name '*gpu_windows*' \
	! -name '*gpu_nvidia*' \
	! -name '*gpu_mthreads*' \
	! -name '*gpu_intel*' \
	! -name '*gpu_amd*' \
	! -name '*gpu_linux*' \
	! -name '*gtk*' \
	! -name '*qt*' \
	! -name '*dbus*' \
	! -name '*camera*' \
	! -name '*vulkan*' \
	! -path '*/displayserver/linux/xcb*' \
	! -path '*/displayserver/linux/xlib*' \
	! -path '*/displayserver/linux/drm*' \
	! -name '*sound_linux*' \
	! -name '*wallpaper*' \
	! -name '*wifi*' \
	! -name '*codec_vulkan*' \
	! -name '*keyboard_linux*' \
	! -name '*localip_linux*' \
	! -name '*netif_linux*' \
	! -name '*sysctl*' \
	! -name '*flashfetch*' \
	! -name '*cpucache_shared*' \
) 

OBJS = $(patsubst $(SRC_DIR)/%.c, build/%.o, $(SRCS))

# Source files for logo_builtin.h generation
LOGO_FILES = $(wildcard $(SRC_DIR)/logo/ascii/[a-z_]/*.txt)
GEN_HEADERS_DEPS = gen_headers.py $(LOGO_FILES)

# Target
all: gen/logo_builtin.h fastfetch

# Generate headers
gen/logo_builtin.h: $(GEN_HEADERS_DEPS)
	python3 gen_headers.py

# Build fastfetch
fastfetch: $(OBJS)
	$(CC) $(CFLAGS) $(DISABLE_FLAGS) $(FEATURE_FLAGS) -o $@ $(filter %.o,$^) $(LDFLAGS)

# Pattern rule for .c -> .o
build/%.o: $(SRC_DIR)/%.c gen/logo_builtin.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DISABLE_FLAGS) $(FEATURE_FLAGS) -c -o $@ $<

clean:
	rm -rf build/ gen/ fastfetch fastfetch.o

.PHONY: all clean
