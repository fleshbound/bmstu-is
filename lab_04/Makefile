CC = gcc
#CFLAGS = -std=c99 -Wall -Werror -pedantic -Wfloat-conversion -Wvla -Wfloat-equal -Wpedantic -Wextra -Iinc -g3
CFLAGS = -std=c99 -I -g3
.PHONY = clean

app.exe: main.o rsa.o io.o md5.o sign.o
	$(CC) -o $@ $^

rsa.o: rsa.c rsa.h bignum.h
	$(CC) $(CFLAGS) -o $@ -c $<

bignum.o: bignum.c bignum.h
	$(CC) $(CFLAGS) -o $@ -c $<

main.o: main.c rsa.h sign.h
	$(CC) $(CFLAGS) -o $@ -c $<

io.o: io.c io.h
	$(CC) $(CFLAGS) -o $@ -c $<

md5.o: md5.c md5.h
	$(CC) $(CFLAGS) -o $@ -c $<

sign.o: sign.c sign.h rsa.h io.h md5.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm *.o
