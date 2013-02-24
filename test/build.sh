#!/bin/bash

ACTION="$1"
BUILD="$2"

# guess OS
if [ $# -lt 2 ]; then
	unamestr=`uname`
	if [[ "$unamestr" == MINGW32_NT* ]]; then # msysgit
		BUILD="vs2010"
	fi
fi

if [ -z "$BUILD" ]; then
	BUILD="gmake"
fi

function clean_output() {
	if [ "$BUILD" == "gmake" ]; then
		make config=all clean
	fi
}

if [ "$ACTION" == "clean" ]; then
	clean_output
	premake4 clean
	exit
fi

function fix_makefile() {
	echo "sedding: $1"
	sed -i -e 's/ -L\/usr\/lib32//g' -e 's/ -L\/usr\/lib64//g' $1
}

if [ ! -f "Makefile" ]; then
	premake4 ${@:3} $BUILD
	if [ "$BUILD" == "gmake" ]; then
		# Toss explicit 32-bit and 64-bit library search paths
		echo "Removing /usr/libxx lib dirs"
		export -f fix_makefile
		find . -maxdepth 2 -name "*.make" -exec bash -c 'fix_makefile {}' \;
	fi
fi

if [ "$BUILD" == "gmake" ]; then
	if [ -z "$ACTION" ]; then
		make config=all
	else
		make config="$ACTION"
	fi
fi
