all:
	gcc -static-libgcc -O2 -o bin/lsrpg.exe *.c
	strip --strip-all bin/lsrpg.exe

clean:
	del bin/lsrpg.exe

.PHONY: clean