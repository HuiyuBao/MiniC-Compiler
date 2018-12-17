all: riscv64

riscv64: y.tab.c lex.yy.c
	g++ -o riscv64 y.tab.c -ly -ll -std=c++11

y.tab.c: tigger.lex tigger.y
	lex tigger.lex
	yacc tigger.y

.PHONY clean:
clean:
	rm -rf riscv64 *.o lex.yy.c y.tab.c
