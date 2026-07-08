Built both static (`libz.a`) and shared (`libz.so.1.3.2`) under musl.

Verified with zlib's own bundled self-test (`./example`): compress/uncompress, gzread/gzwrite, gzseek, inflate, inflateSync, and dictionary inflate all passed.
