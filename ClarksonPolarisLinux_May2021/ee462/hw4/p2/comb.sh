#!/bin/sh
if [ ! -p /tmp/f1fo ]
then
    mkfifo /tmp/f1fo
fi
if [ ! -p /tmp/f2fo ]
then
    mkfifo /tmp/f2fo
fi
cat $1 > f1fo
bash prog1.sh > f2fo < f1fo
bash prog2.sh < f2fo
bash prog3.sh < f2fo