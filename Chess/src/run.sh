#!/bin/sh

run_game() {
	font="Dejavu Sans Oblique, 34"
	/usr/bin/sakura -f "$font" --execute ./main
}

if [ -z ./main ] || [ ! -z $1 ] && [ $1 == "-b" ]; then
    echo "Building game using g++"
	/usr/bin/g++ -o2 -std=c++20 *.cpp -o main
fi

run_game
