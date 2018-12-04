all: tigger

tigger: y.tab.c lex.yy.c util.c
	g++ -o tigger y.tab.c util.c -ly -ll -std=c++11

y.tab.c: eeyore.lex eeyore.y
	lex eeyore.lex
	yacc eeyore.y

.PHONY clean:
clean:
	rm -f tigger *.o lex.yy.c y.tab.c ee.out
