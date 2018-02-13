CC=gcc
CFLAGS=-Wall -O2 -march=native

c-version: c-version.o speed-test.o

asm-version: asm-version.o speed-test.o

data.txt: gen-data
	./gen-data >data.txt

test: c-version asm-version data.txt
	gcc --version
	uname -srp
	@echo -en "C version: "
	@bash -c "time ./c-version"
	@echo -en "\n\"Asm\" version: "
	@bash -c "time ./asm-version"

clean:
	rm -f *.o *~
	rm -f c-version asm-version gen-data
