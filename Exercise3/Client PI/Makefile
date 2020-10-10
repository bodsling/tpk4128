vpath %.h ../Headers

vpath serverUtils.c ../Utilities

CC = gcc #Which compiler to use
CFLAGS = -g -pthread #g flag tells compiler to make debug information
DEPS = serverUtils.h
OBJ = client3.o serverUtils.o 

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
client: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
