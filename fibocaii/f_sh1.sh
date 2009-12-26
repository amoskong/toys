#!/bin/bash

echo "please input a number"
read N
echo "----------"
let x=0
let y=1
let i=0

for((i=1;i<=N;i++))
do
	echo $y
	let y2=$y
	let y=$x+$y
	let x=$y2
done
