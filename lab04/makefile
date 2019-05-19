CC=gcc
CFLAGS= -O2 -lm -lm -lgsl -lgslcblas
DEPS=
OBJS=lab04.o
OUT=lab04

$(OUT): $(OBJS)
	$(CC)  -o $@  $^ $(CFLAGS)
	
.c.o:
	$(CC) -c -o $@ $< $(CFLAGS) 
	
.PHONY: clean	
clean:
	rm -f *o
	rm -f *~
	rm -f $(OUT)
	
run:
	./lab04