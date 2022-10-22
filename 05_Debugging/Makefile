all: build test
build:
	gcc -O0 -g range.c -o range.o
test:
	gdb --batch --quiet -x script1.gdb --args ./range.o 1 12 | grep -o '{.*}' > out_cur_1.txt
	gdb --batch --quiet -x script1.gdb --args ./range.o -100 100 3 | grep -o '{.*}' > out_cur_2.txt
	cmp out1.txt out_cur_1.txt
	cmp out2.txt out_cur_2.txt
clean:
	rm *.o
	rm out_cur_*.txt
