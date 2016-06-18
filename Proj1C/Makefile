all:
	mkdir include lib
	cp math330.h include
	gcc -Iinclude/ -c trig/*.c
	gcc -Iinclude/ -c exp/*.c
	mv *.o lib
	ar r lib/libmath330.a lib/*.o
	gcc -Iinclude cli/cli.c -Llib -lmath330 -lm

clean:
	rm -rf include lib *.o
