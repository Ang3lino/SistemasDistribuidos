#!/bin/sh

src=$1

if [ ! -f $src ]; then
    echo "$src NOT FOUND u-u"
    exit 1
fi

g++ ${src} -lpthread

if [ $? -eq 0 -a -f a.out ]; then
    ./a.out
fi

cat $src

exit 0
