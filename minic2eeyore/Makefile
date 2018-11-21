all: eeyore

eeyore: y.tab.c lex.yy.c util.c
	g++ -o eeyore y.tab.c util.c -ly -ll -std=c++11

y.tab.c: minic.lex minic.y
	lex minic.lex
	yacc minic.y

.PHONY clean:
clean:
	rm -f eeyore *.o lex.yy.c y.tab.c ee.out
