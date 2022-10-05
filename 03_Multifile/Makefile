
all: prog prog-a prog-so

prog:   const.o fun.o prog.o
	cc const.o fun.o prog.o -o prog

prog-a: prog.o liboutput-static
	cc prog.o liboutput_static.a -o prog-a

prog-so: prog.o liboutput-so
	cc prog.o liboutput.so -o prog-so

fun.o:  fun.c
	cc fun.c -c -o fun.o

prog.o: prog.c
	cc prog.c -c -o prog.o

const.o:        const.c
	cc const.c -c -o const.o

liboutput-static:	fun.o const.o
	ar -rcs liboutput_static.a fun.o const.o

liboutput-so:	fun.o const.o
	cc -shared fun.o const.o -o liboutput.so

clean:
	rm -f prog a.out *.o liboutput.so liboutput_static.a prog-a prog-so test-res*

test: run-test check-tests

check-tests:
	cmp test-res-0.txt test-res-0-a.txt
	cmp test-res-0-a.txt test-res-0-so.txt
	cmp test-res-0-so.txt test-res-0.txt
	cmp test-res-1.txt test-res-1-a.txt
	cmp test-res-1-a.txt test-res-1-so.txt
	cmp test-res-1-so.txt test-res-1.txt
	cmp test-res-2.txt test-res-2-a.txt
	cmp test-res-2-a.txt test-res-2-so.txt
	cmp test-res-2-so.txt test-res-2.txt

run-test: all
	./prog > test-res-0.txt 2>&1
	./prog one > test-res-1.txt>&1
	./prog one two three > test-res-2.txt 2>&1
	./prog-a > test-res-0-a.txt 2>&1
	./prog-a one > test-res-1-a.txt 2>&1
	./prog-a one two three > test-res-2-a.txt 2>&1
	./prog-so > test-res-0-so.txt 2>&1
	./prog-so one > test-res-1-so.txt 2>&1
	./prog-so one two three > test-res-2-so.txt 2>&1
