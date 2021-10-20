# spanfsd

One time setup:

```
meson setup builddir
```

Compiling and running:

```
export workdir=`pwd` 
cd $workdir/builddir; meson --reconfigure && ninja && cd $(mktemp -d) && pwd && $workdir/spanfsd .; cd $workdir
```
