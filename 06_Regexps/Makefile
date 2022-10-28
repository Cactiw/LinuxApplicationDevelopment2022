all: build test

build:
	cc esub.c -o esub

test:
	./esub [0-9] A abcde1234xyz > out1.txt
	echo 'abcde1234xyz' | sed -E 's/[0-9]/A/' > out1_true.txt
	cmp out1.txt out1_true.txt


	./esub ab[a-z] A abcde1234xyz > out2.txt
	echo 'abcde1234xyz' | sed -E 's/ab[a-z]/A/' > out2_true.txt
	cmp out2.txt out2_true.txt

clean:
	rm esub out*.txt
