all:	Hello,World

Hello,World:	Hello,World.c
	gcc -o -Wall -Werror Hello,World Hello,World.c

clean:
	rm Hello,World

run:
	./Hello,World
