This is a static build (musl, `-static`).

Even though the libraries and programs are statically linked, ncurses still needs a terminfo database at runtime (configured here as `/usr/share/terminfo`). Do not forget to copy `misc/terminfo.src` (compiled with `tic`) or the generated terminfo tree into the Kyronix rootfs at `/usr/share/terminfo`, otherwise `clear`, `tput`, and any program linked against `libncurses` will fail to find the terminal type.

Known issue: line-drawing (ACS) characters show up as raw letters (`q`, `x`, `l`, `k`, `m`, `j`, ...) instead of actual box-drawing lines when testing ncurses demos in QEMU. This is not a bug in this port or in the terminfo database, it is the Kyronix framebuffer console that does not correctly handle the escape sequences ncurses sends to switch into the alternate character set. Needs a fix on the Kyronix framebuffer/console side, not here.
