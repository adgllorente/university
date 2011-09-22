LEX=flex
YACC=bison 
CC=gcc 

pascual1: y.tab.o lex.yy.o tabla.o errores.o listas.o
	$(CC) -o pascual1 y.tab.o lex.yy.o tabla.o errores.o listas.o -ll -ly

listas.o: listas.c listas.h
	$(CC) -c listas.c
			
tabla.o: tabla.c tabla.h
	$(CC) -c tabla.c
			
errores.o: errores.c
	$(CC) -c errores.c
			
lex.yy.o: y.tab.h errores.h
	$(CC) -c lex.yy.c
	
y.tab.o: y.tab.c errores.h
	$(CC) -c y.tab.c -DYYDEBUG

y.tab.c: pascual1.y
	$(YACC) -ydvt pascual1.y

lex.yy.c: pascual1.l
	$(LEX) pascual1.l
