#!/bin/bash
mkdir -p ./out ./logs
rm -rf ./out/* ./logs/*
test_number=$1
if [ -z "$test_number" ]
then
	echo "No test number provided"
	exit -1
elif ! [[ $test_number =~ ^[0-9]+$ ]] && ! [[ $test_number =~ ^[0-9]+[a-z]$ ]]
then
	echo "Invalid test number"
	exit -2
elif [[ $test_number =~ ^[0-9]+[a-z]$ ]] || [ $test_number -gt 9 ]
then
	./build/bin/test/test$test_number
elif [ $test_number -gt 0 ]
then
	./build/bin/test/test0$test_number
elif [ $test_number -eq 0 ]
then
	./build/bin/test/test01 > ./logs/test01.log
	./build/bin/test/test02 1 > ./logs/test02-1.log
	./build/bin/test/test02 2 > ./logs/test02-2.log
	./build/bin/test/test03 1 > ./logs/test03-1.log
	./build/bin/test/test03 2 > ./logs/test03-2.log
	./build/bin/test/test03 3 > ./logs/test03-3.log
else
	echo "GG, i have no idea how you got here, i probably forgot a way to escape my conditions"
	exit -69
fi