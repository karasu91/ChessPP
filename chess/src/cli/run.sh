#!/bin/sh

LD_LIBRARY_PATH=./lib/lib build/client --docroot . --http-address 0.0.0.0 --http-port 9090
