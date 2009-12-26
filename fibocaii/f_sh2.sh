#!/bin/bash

echo "please input a number:"
read N
let x=1
let y=1
let z=0
if((N>1))
then
echo $x
echo $y
for((i=3;i<=N;i++))
do
 let z=$x+$y
 echo $z
 let x=$y
 let y=$z
done
fi
