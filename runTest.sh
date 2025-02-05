#!/bin/bash
mkdir -p ./out/test03 ./out/test05 ./out/test08 ./logs
rm -rf ./out/test03/* ./out/test05/* ./out/test08/* ./logs/*
test_number=$1
if [ -z "$test_number" ]; then
	echo "No test number provided"
	exit -1
elif ! [[ $test_number =~ ^-?[0-9]+$ ]] && ! [[ $test_number =~ ^-?[0-9]+[a-z]$ ]]; then
	echo "Invalid test number"
	exit -2
elif [[ $test_number =~ ^-?[0-9]+[a-z]$ ]] || [ $test_number -gt 9 ]; then
	./build/bin/test/test$test_number
elif [ $test_number -gt 0 ]; then
	./build/bin/test/test0$test_number
elif [ $test_number -eq 0 ]; then
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
	./build/bin/test/test06 1 > ./logs/test06-1.log
	./build/bin/test/test06 2 > ./logs/test06-2.log
	./build/bin/test/test06 3 > ./logs/test06-3.log
	./build/bin/test/test06 4 > ./logs/test06-4.log
	./build/bin/test/test06 5 > ./logs/test06-5.log
	./build/bin/test/test06 6 > ./logs/test06-6.log
	./build/bin/test/test07 1 > ./logs/test07-1.log
	./build/bin/test/test07 2 > ./logs/test07-2.log
	./build/bin/test/test07 3 > ./logs/test07-3.log
	./build/bin/test/test07 4 > ./logs/test07-4.log
	./build/bin/test/test07 5 > ./logs/test07-5.log
	./build/bin/test/test07 6 > ./logs/test07-6.log
	./build/bin/test/test08 1 > ./logs/test08-1.log
	./build/bin/test/test08 2 > ./logs/test08-2.log
	./build/bin/test/test08 3 > ./logs/test08-3.log
	./build/bin/test/test08 4 > ./logs/test08-4.log
	./build/bin/test/test08 5 > ./logs/test08-5.log
	./build/bin/test/test09 1 > ./logs/test09-1.log
	./build/bin/test/test09 2 > ./logs/test09-2.log
	./build/bin/test/test09 3 > ./logs/test09-3.log
	./build/bin/test/test09 4 > ./logs/test09-4.log
	./build/bin/test/test09 5 > ./logs/test09-5.log
	./build/bin/test/test09 6 > ./logs/test09-6.log
	./build/bin/test/test09 7 > ./logs/test09-7.log
	#./build/bin/test/test10a > ./logs/test10a.log
	./build/bin/test/test10b > ./logs/test10b.log
elif [ $test_number -eq -1 ]; then
	./build/bin/test/test01 > ./logs/test01.log
	./build/bin/test/test02 1 > ./logs/test02-1.log
	./build/bin/test/test02 2 > ./logs/test02-2.log
	./build/bin/test/test03 1 > ./logs/test03-1.log
	./build/bin/test/test03 2 > ./logs/test03-2.log
	./build/bin/test/test03 3 > ./logs/test03-3.log
	./build/bin/test/test04 1 > ./logs/test04-01.log
	./build/bin/test/test04 2 > ./logs/test04-02.log
	#./build/bin/test/test04 3 > ./logs/test04-03.log
	./build/bin/test/test04 4 > ./logs/test04-04.log
	./build/bin/test/test04 5 > ./logs/test04-05.log
	./build/bin/test/test04 6 > ./logs/test04-06.log
	./build/bin/test/test04 7 > ./logs/test04-07.log
	./build/bin/test/test04 8 > ./logs/test04-08.log
	#./build/bin/test/test04 9 > ./logs/test04-09.log
	./build/bin/test/test04 10 > ./logs/test04-10.log
	./build/bin/test/test04 11 > ./logs/test04-11.log
	./build/bin/test/test05 1 > ./logs/test05-1.log
	./build/bin/test/test05 2 > ./logs/test05-2.log
	./build/bin/test/test05 3 > ./logs/test05-3.log
	./build/bin/test/test05 4 > ./logs/test05-4.log
	./build/bin/test/test05 5 > ./logs/test05-5.log
	./build/bin/test/test05 6 > ./logs/test05-6.log
	./build/bin/test/test05 7 > ./logs/test05-7.log
	#./build/bin/test/test06 1 > ./logs/test06-1.log
	#./build/bin/test/test06 2 > ./logs/test06-2.log
	#./build/bin/test/test06 3 > ./logs/test06-3.log
	#./build/bin/test/test06 4 > ./logs/test06-4.log
	#./build/bin/test/test06 5 > ./logs/test06-5.log
	#./build/bin/test/test06 6 > ./logs/test06-6.log
	./build/bin/test/test07 1 > ./logs/test07-1.log
	./build/bin/test/test07 2 > ./logs/test07-2.log
	./build/bin/test/test07 3 > ./logs/test07-3.log
	./build/bin/test/test07 4 > ./logs/test07-4.log
	./build/bin/test/test07 5 > ./logs/test07-5.log
	./build/bin/test/test07 6 > ./logs/test07-6.log
	./build/bin/test/test08 1 > ./logs/test08-1.log
	./build/bin/test/test08 2 > ./logs/test08-2.log
	./build/bin/test/test08 3 > ./logs/test08-3.log
	./build/bin/test/test08 4 > ./logs/test08-4.log
	./build/bin/test/test08 5 > ./logs/test08-5.log
	#./build/bin/test/test09 1 > ./logs/test09-1.log
	./build/bin/test/test09 2 > ./logs/test09-2.log
	#./build/bin/test/test09 3 > ./logs/test09-3.log
	#./build/bin/test/test09 4 > ./logs/test09-4.log
	#./build/bin/test/test09 5 > ./logs/test09-5.log
	./build/bin/test/test09 6 > ./logs/test09-6.log
	./build/bin/test/test09 7 > ./logs/test09-7.log
	#./build/bin/test/test10a > ./logs/test10a.log
	./build/bin/test/test10b > ./logs/test10b.log
else
	echo "GG, i have no idea how you got here, i probably forgot a way to escape my conditions"
	exit -69
fi
