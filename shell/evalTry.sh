#!/bin/sh

labels="test1 test2 test3"
for item in $labels
do
	if [ -s "${test}.log" ];then
		eval ${item}_color="red"
	else
		eval ${item}_color="green"
	fi
	eval echo '$'${item}_color
done

