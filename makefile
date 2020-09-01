build:
	gcc -o prettyfi main.c
clean:
	rm prettyfi
install:
	mv prettyfi /usr/bin/
uninstall:
	rm /usr/bin/prettyfi
