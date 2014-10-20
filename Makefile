CC=gcc
LIB=-lgmp -lpthread
INCLUDE=.
CFFLAG=
objects=websvr.o bignum.o
websvr : $(objects)
	$(CC) $(CFFLAG) $^ $(LIB) -o $@ 
