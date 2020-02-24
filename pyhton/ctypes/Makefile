all: libpydll.c 
	gcc -shared -o libpydll.so -I. libpydll.c
	sudo cp libpydll.so /usr/lib/
clean:
	rm libpydll.so

