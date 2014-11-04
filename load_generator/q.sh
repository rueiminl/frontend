#!/bin/bash
# argument:
# $1: query type
# $2: total number
count="0"
if [ $# -lt 2 ]; then
	num=10000
else
	num=$2
fi
while read line; do
	cmd="curl -s http://127.0.0.1:8080$line"
	$cmd
	count=$((count+1))
	if [ $count -ge $num ]; then
		break
	fi
done < q$1.txt
echo $count
