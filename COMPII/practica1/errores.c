/**********************************************************************
 Prog.:		errores.c
 Tema:		rutinas de manejo de error para COMPII
 Fecha:		Enero-98
 Fuente:	Propio
 Com.:		Se sumistra a los alumnos compilado
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>			  /*para "exit ()"*/

extern int nErrores;			/*Para controlar el número de errores*/

extern int yydebug;           /*para usar el debugger*/

extern int dar_warnings;		/*Para dar warnings*/

extern int lineno,linepos;    /*Estas variables globales se usan para 
                                almacenar la l'inea y columna del fuente,
                                y se suponen declaradas en el fuente Lex.
                                Algunos generadores de analizadores l'exicos
                                las incluyen en la librer'ia del analizador.
                                Para usar en "yyerror()", que redefine la
                                rutina de error de Yacc (para el an'alisis
                                sint'actico
                              */
extern char yytext[];         /*Contenida en la librer'ia de Lex
                                (compilaci'on con la opci'on "-ll")
                              */

/**********************************************************************/
void warning (char *mens)
/**********************************************************************
    Pre:     (lin, col) es la localizaci'on del principio del
            lexema causa del error. (*mens) contiene el mensaje
            de error a sacar por stderr. (*lexema) contiene
            el lexema que se est'a analizando
    Post: escribe (*mens) en stderr y sigue ejecuci'on
**********************************************************************/
{
	if(dar_warnings)
		fprintf (stderr, "AVISO! (%d, %d, %s): %s\n", lineno, linepos, yytext, mens);
}

/**********************************************************************/
void yyerror (char *mens)
/**********************************************************************
	Pre:	 (lin, col) es la localizaci'on del principio del 
			lexema causa del error. (*mens) contiene el mensaje
			de error a sacar por stderr. (*lexema) contiene
			el lexema que se est'a analizando
	Post: escribe (*mens) en stderr y aborta ejecuci'on
	   
			Lo invoca el analizador sint'actico "yyparse ()"
**********************************************************************/
{
	fprintf (stderr, "ERROR SINTACTICO! (%d, %d, %s): %s\n", lineno, linepos, yytext, mens);
	exit (1);
}

/**********************************************************************/
void error_semantico (char *mens)
/**********************************************************************
	Pre: (lin, col) es la localizaci'on del principio del 
			lexema causa del error. (*mens) contiene el mensaje
			de error a sacar por stderr. (*lexema) contiene
			el lexema que se est'a analizando
	Post: escribe (*mens) en stderr
	   
			Lo invoca el an'alisis sem'antico
**********************************************************************/
{
	nErrores++;
	fprintf (stderr, "ERROR SEMANTICO! (%d, %d, %s) %s\n", lineno, linepos, yytext, mens);
}
