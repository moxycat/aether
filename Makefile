all:
	gcc -static-libgcc -O2 -Wall -o game.exe *.c
	strip --strip-all game.exe

clean:
	del game.exe