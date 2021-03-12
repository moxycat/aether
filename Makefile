all:
	gcc -static-libgcc -O2 -fcompare-debug-second -Wall -Wno-incompatible-pointer-types -Wno-int-conversion -Wno-unused-but-set-variable -o game.exe *.c
	strip --strip-all game.exe

clean:
	del game.exe