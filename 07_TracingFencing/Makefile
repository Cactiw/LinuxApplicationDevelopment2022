
TEST_CONTENT_1 = "dasjfdajlflsajlkjaldslajdlasjfsakjdfsakldj"

all: build test

build: move remove

move:
	cc move.c -o move
remove:
	cc -shared -fPIC remove.c -o remove.so -ldl
clean:
	rm remove remove.so *.txt

test:
	echo $TEST_CONTENT_1 > input.txt
	./move input.txt out.txt
	! test -f input.txt
	touch out.txt


	echo $TEST_CONTENT_1 > input.txt
	! ./move not_extist.txt out.txt

	echo $TEST_CONTENT_1 > input_protected.txt
	LD_PRELOAD=`pwd`/remove.so ./move input_protected.txt out.txt
