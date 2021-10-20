# spanfsd

One time setup:

```
meson setup builddir
cd builddir/
```

Compiling and running (from `builddir/`):

```
meson --reconfigure && ninja && ./spanfsd
```
