```makefile
   CC=g++
   CFLAGS=-I.

   dmre: src/dmre_core.cpp
   	$(CC) -o dmre src/dmre_core.cpp $(CFLAGS)
