#!/bin/bash

if [ ! `id -u` -eq 0 ]
then
	echo  -e "ERROR:Permission denied!\nPlease use root!";
	exit;
fi
if [ ! -f ./src ]
then 
	echo "ERROR:No find file(./src)";
	echo "Please make first!"
	exit;
fi
if [ ! -f ./trace ]
then 
	echo "ERROR:No find file(./trace)";
	echo "Please make first!"
	exit;
fi
if [ ! -f ./rule ]
then 
	echo "ERROR:No find file(./rule)";
	echo "Please make first!"
	exit;
fi

rm -rf log/* 2> /dev/null;

./src 2> /dev/null 1> /dev/null &
./rule;
killall src 2> /dev/null;
killall strace 2> /dev/null;
rm cmd.txt 2> /dev/null;
