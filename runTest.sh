#!/bin/bash
mkdir -p ./out
rm -rf ./out/*
test_number=$1
if [ -z "$test_number" ]
then
	echo "No test number provided"
	exit -1
fi
./build/bin/test/test$(printf "%02d" $test_number)
