#!/bin/bash

CWD=$(pwd)
collatz=2000000
maxThreads=30
name="mt-collatz"
output="testNoLockOutput"

if [ ! -s $name ]; then
	echo "Program not found; running 'make'..."
	make > /dev/null 2> /dev/null
	echo "Compiled prorgram!"
fi

if [ ! -d $CWD/$output/cout ]; then
	mkdir -p $CWD/$output/cout
fi

if [ ! -d $CWD/$output/cerr ]; then
	mkdir -p $CWD/$output/cerr
fi

for i in {1..30}
do
	for j in {1..20}
	do
		./$name $collatz $i -nolock > $CWD/$output/cout/values-$i-$j.out 2> $CWD/$output/cerr/time-$i-$j.out
		echo "Finished iteration $j with threadCount $i"
	done
	echo "Finished with threadCount $i!"
done
