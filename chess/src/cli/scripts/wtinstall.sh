#!/bin/sh

LIBDIR="./lib"
TMPDIR="./tmp"
mkdir $LIBDIR
mkdir $TMPDIR
cmake ../lib/wt/ && \
DESTDIR="$TMPDIR/build" make install -j20 &&
echo copying tmp files into $LIBDIR...
cp $TMPDIR/build/usr/* -R $LIBDIR
echo "finished."
