CC=gcc
CFLAGS= -O2 -lm
DEPS=
OBJS=lab06.o
OUT=lab06

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
	./lab06