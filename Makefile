CC=gcc
BIN=bin

all: builddir
	echo "all"

builddir:
	mkdir -p $(BIN)
