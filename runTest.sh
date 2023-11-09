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
	./build/bin/test/test04 1 > ./logs/test04-01.log
	./build/bin/test/test04 2 > ./logs/test04-02.log
	./build/bin/test/test04 3 > ./logs/test04-03.log
	./build/bin/test/test04 4 > ./logs/test04-04.log
	./build/bin/test/test04 5 > ./logs/test04-05.log
	./build/bin/test/test04 6 > ./logs/test04-06.log
	./build/bin/test/test04 7 > ./logs/test04-07.log
	./build/bin/test/test04 8 > ./logs/test04-08.log
	./build/bin/test/test04 9 > ./logs/test04-09.log
	./build/bin/test/test04 10 > ./logs/test04-10.log
	./build/bin/test/test04 11 > ./logs/test04-11.log
	./build/bin/test/test05 1 > ./logs/test05-1.log
	./build/bin/test/test05 2 > ./logs/test05-2.log
	./build/bin/test/test05 3 > ./logs/test05-3.log
	./build/bin/test/test05 4 > ./logs/test05-4.log
	./build/bin/test/test05 5 > ./logs/test05-5.log
	./build/bin/test/test05 6 > ./logs/test05-6.log
	./build/bin/test/test05 7 > ./logs/test05-7.log
else
	echo "GG, i have no idea how you got here, i probably forgot a way to escape my conditions"
	exit -69
fi