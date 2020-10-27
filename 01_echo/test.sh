#!/bin/sh

make

for i in 1 2 ; do
    ./my_echo `cat test$i.cmd` >test$i.output
    if diff test$i.correct test$i.output ; then
        echo "Test $i OK"
    else
        echo "Test $i failed"
        exit
    fi  
done
