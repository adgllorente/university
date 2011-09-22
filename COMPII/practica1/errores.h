/**********************************************************************
 Prog.:		errores.h
 Tema:		rutinas de manejo de error para COMPII
 Fecha:		Enero-98
 Fuente:	Propio
 Com.:		Se sumistra a los alumnos
**********************************************************************/
#include <stdio.h>

/**********************************************************************/
void warning (char *mens);
/**********************************************************************
    Pre:     (lineno, linepos) es la localizaci'on del principio del
            lexema causa del error. (*mens) contiene el mensaje
            de error a sacar por stderr. yytext contiene
            el lexema que se est'a analizando
    Post: escribe (*mens) en stderr y sigue ejecuci'on
**********************************************************************/

/**********************************************************************/
void yyerror (char *mens);
/**********************************************************************
    Pre:     (lineno, linepos) es la localizaci'on del principio del
            lexema causa del error. (*mens) contiene el mensaje
            de error a sacar por stderr. yytext contiene
            el lexema que se est'a analizando
	Post: escribe (*mens) en stderr y aborta ejecuci'on
	   
			Lo invoca el analizador sint'actico "yyparse()"
**********************************************************************/

/**********************************************************************/
void error_semantico (char *mens);
/**********************************************************************
    Pre:     (lineno, linepos) es la localizaci'on del principio del
            lexema causa del error. (*mens) contiene el mensaje
            de error a sacar por stderr. yytext contiene
            el lexema que se est'a analizando
	Post: escribe (*mens) en stderr
	   
			Lo invoca el an'alisis sem'antico
**********************************************************************/
