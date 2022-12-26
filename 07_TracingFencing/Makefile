
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

	echo $TEST_CONTENT_1 > input.txt
	! strace -eread -efault=read:error=EPERM ./move input.txt out.txt 2> error.txt
	touch error.txt
	[[ "$(tail -n 2 true_error.txt_)" == "$(tail -n 2 error.txt)" ]] && echo "not same" || echo "same"
	touch input.txt
