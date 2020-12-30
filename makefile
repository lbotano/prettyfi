build:
	gcc -Wall -o prettyfi main.c
clean:
	rm prettyfi
install:
	mv prettyfi /usr/bin/
uninstall:
	rm /usr/bin/prettyfi

debug:
	gcc -Wall -g -o prettyfi main.c
	gdb prettyfi
