DEFS =
OPT = -O
CFLAGS = $(INC) $(OPT) $(DEFS)

simseg: trace.o simseg.o
	cc  -o simseg trace.o simseg.o

trace.o: trace.c
	cc -c $(CFLAGS) trace.c

clean:
	rm -f $(OBJ)
