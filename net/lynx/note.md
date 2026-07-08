This is a static build, same reasoning as bmake/strace/ncurses: lynx is a self-contained end-user program, not a shared library, so no reason to keep it dynamic. Built against the static `libs/ncurses` (via `--with-curses-dir`) and `libs/openssl` (via pkg-config against the staged install, see below).

The real binary is `obj-musl-static/lynx`.

Config file: lynx looks for `/etc/lynx.cfg` at runtime (compiled in via `--sysconfdir=/etc`). Copy the source tree's `lynx.cfg` there, otherwise lynx refuses to start ("Configuration file ... is not available").

Gotcha hit while porting: `--with-ssl=<path>` (pointing straight at `libs/openssl/obj-musl`) silently fails to detect OpenSSL. Lynx's configure only looks for a bare `ssl.h` in `<path>/include` plus a fixed list of system directories, it never tries `<path>/include/openssl`, so `cf_cv_have_ssl` ends up `no` and the binary builds without HTTPS support (fails at runtime with "This client does not contain support for HTTPS URLs"). Fixed the same way as `net/curl`: install OpenSSL into `libs/openssl/stage` (`make DESTDIR=... install_sw`) and configure lynx with `--with-ssl` (no path) plus `PKG_CONFIG_LIBDIR`/`PKG_CONFIG_SYSROOT_DIR` pointing at the staged `.pc` files, so it finds OpenSSL through pkg-config instead. Confirmed working with a real HTTPS render of github.com.

`lynx.cfg` ships with `SSL_CERT_FILE` commented out. Leave it commented out: OpenSSL's own compiled-in default already points at `/etc/ssl/cert.pem` (see `libs/openssl/note.md`), which matches this project's convention. Do not uncomment the shipped example (`/etc/ssl/certs/ca-certificates.crt`), that's a Debian-style path that does not exist here and would break certificate verification.

Not included in this build: zlib, libidn2 (mentioned as optional deps, not ported yet).
