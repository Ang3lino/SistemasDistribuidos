#!/bin/sh

src=$1
g++ ${src} -lpthread
./a.out
