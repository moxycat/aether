gcc -static-libgcc -O2 -fcompare-debug-second -Wall -Wno-incompatible-pointer-types -Wno-int-conversion -Wno-unused-but-set-variable -Wno-unused-variable -o game.exe *.c
strip --strip-all game.exe
