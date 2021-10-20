# spanfsd

One time setup:

```
meson setup builddir
```

Compiling and running:

```
export workdir=`pwd` 
cd $workdir/builddir; meson --reconfigure && ninja && cd $(mktemp -d) && echo && pwd && echo && $workdir/builddir/spanfsd .
cd $workdir
```

To debug, pass the following flags:

```
$workdir/builddir/spanfsd . -f -s -d
```