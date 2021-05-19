EXCEL=test.xlsx

all:
	g++ -std=c++14 main.cpp -I xlnt/include -o xlsx2csv -L ./xlnt/build/source -lxlnt

exec:
	LD_LIBRARY_PATH=./xlnt/build/source ./xlsx2csv test.xlsx


prepare:
	git clone --recursive https://github.com/tfussell/xlnt.git
	cd xlnt; mkdir build; cd build; cmake ..; make
