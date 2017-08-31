#!/bin/bash
#

./bigm &
for ii in {1..8}
do
    ps u |grep -v "grep"|grep "bigm"
    #busybox usleep 500000
    sleep 1
done
