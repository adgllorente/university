%{
/**********************************************************************
 * fichero: pascual.l
 *          Analizador lexico de Pascual
 *          2010-03-21
 *             jfabra - Añadidos tipos enumerativos
 **********************************************************************/

#include <stdio.h>
#include <string.h>
#include "errores.h"
#include "listas.h"
#include "tabla.h"
#include "y.tab.h"

int lineno = 1, linepos = 0;
extern TABLA_SIMBOLOS tabsim;

extern YYSTYPE yylval;

#define TRATA(token) { linepos += yyleng; return (token); }

/**********************************************************************/
void mayusculas (char ident[])
/**********************************************************************/
{
   int i;
     
   for (i = 0; i <= strlen (ident) - 1; i++)
         ident[i] = toupper (ident[i]);
}
%}

comentario      "%".*$
separador       [\t ]
letra           [_a-zA-Z]
digito          [0-9]
identificador   {letra}({letra}|{digito})*
constEntera     {digito}+
constChar       \'.\'
constCad        \'[^\'][^\']+\'
opAs            ":="
carSimples      [\+\-\*\/\[\]\:\;\,\(\)\<\>\=\.]    
A               [Aa]
B               [Bb]
C               [Cc]
D               [Dd]
E               [Ee]
F               [Ff]
G               [Gg]
H               [Hh]
I               [Ii]
J               [Jj]
K               [Kk]
L               [Ll]
M               [Mm]
N               [Nn]
O               [Oo]
P               [Pp]
Q               [Qq]
R               [Rr]
S               [Ss]
T               [Tt]
U               [Uu]
V               [Vv]
W               [Ww]
X               [Xx]
Y               [Yy]
Z               [Zz]

%%
{P}{R}{O}{G}{R}{A}{M}{A}       { TRATA(tPROGRAMA); }
{A}{N}{D}                      { TRATA(tAND); }
{O}{R}                         { TRATA(tOR); }
{N}{O}{T}                      { TRATA(tNOT); }
{P}{R}{I}{N}{C}{I}{P}{I}{O}    { TRATA(tPRINCIPIO); }
{F}{I}{N}                      { TRATA(tFIN); }
{S}{I}                         { TRATA(tSI); }
{E}{N}{T}                      { TRATA(tENT); }
{S}{I}_{N}{O}                  { TRATA(tSI_NO);    }
{F}{S}{I}                      { TRATA(tFSI); }
{M}{Q}                         { TRATA(tMQ); }
{F}{M}{Q}                      { TRATA(tFMQ); }
{E}{S}{C}{R}{I}{B}{I}{R}       { TRATA(tESCRIBIR); }
{L}{E}{E}{R}                   { TRATA(tLEER); }
{M}{O}{D}                      { TRATA(tMOD); }
{D}{I}{V}                      { TRATA(tDIV); }
{E}{N}{T}{E}{R}{O}             { TRATA(tENTERO);}
{B}{O}{O}{L}{E}{A}{N}{O}       { TRATA(tBOOLEANO);}
{C}{A}{R}{A}{C}{T}{E}{R}       { TRATA(tCARACTER);}
{T}{R}{U}{E}                   { TRATA(tTRUE);}
{F}{A}{L}{S}{E}                { TRATA(tFALSE);}
{E}{N}{T}{A}{C}{A}{R}          { TRATA(tENTACAR);}
{C}{A}{R}{A}{E}{N}{T}          { TRATA(tCARAENT);}
{A}{C}{C}{I}{O}{N}             { TRATA(tACCION); }
{V}{A}{L}                      { TRATA(tVAL); }
{R}{E}{F}                      { TRATA(tREF); }
{V}{E}{C}{T}{O}{R}				{ TRATA(tVECTOR); }
{D}{E}							{ TRATA(tDE); }
">="                           { TRATA(tMAI); }
"<="                           { TRATA(tMEI); }
"<>"                           { TRATA(tNI); }
{opAs}                         { TRATA(tOPAS);}
{comentario}                   { }
{constEntera}                  {
                                 yylval.constante = atoi (yytext);
                                 TRATA(tCONSTENTERA);
                               }
{constChar}                    {
                                 yylval.constante = yytext[1];
                                 TRATA(tCONSTCHAR);
                               }
{constCad}                     {
                                 yylval.cadena = strdup(&(yytext[1]));
                                 yylval.cadena[strlen(yylval.cadena)-1] = '\0';
                                 TRATA(tCONSTCAD);
                               }
{identificador}                {
                                 mayusculas (yytext);
                                 yylval.cadena = strdup(yytext);
								 //Devolvemos el nombre y la posición
								 yylval.identificador.simbolo = buscar_simbolo(tabsim, yytext);
								 yylval.identificador.nombre = yytext;
                                 TRATA(tIDENTIFICADOR);
                               }
{carSimples}                   { linepos++; return (yytext[0]);}
{separador}                    { linepos++;};
\n                             { linepos = 1; lineno++; }
.                              { 
                                 warning ("Caracter extraño.");
                                 linepos++;
                               }
%%
