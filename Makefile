CC=gcc
LIB=
INCLUDE=.
CFFLAG=
objects=websvr.o bignum.o
websvr : $(objects)
	$(CC) $(CFFLAG) $^ $(LIB) -o $@ 
