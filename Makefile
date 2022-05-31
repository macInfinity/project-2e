CFLAGS=-W -Wall
OBJECTS = project2E.o
#comment here
build: $(OBJECTS)
	gcc -o project2E $(OBJECTS)
	chmod +x project2E
project2E.o: project2E.c

clean:
	rm -f $(OBJECTS) project2E valgrind-out.txt
