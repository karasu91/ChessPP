#!/bin/sh

LIBDIR="./lib"
TMPDIR="./tmp"
mkdir $LIBDIR
mkdir $TMPDIR
cd $TMPDIR &&
cmake ../../lib/wt/ && \
DESTDIR="./build" make install -j20 &&
echo copying tmp files into $LIBDIR...
cp ./build/usr/local/* -R ../$LIBDIR
cd ..
echo "cleaning up..."
rm $TMPDIR -rf
echo "finished."
