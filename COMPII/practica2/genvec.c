/**********************************************************************
 * Practicas de Compiladores II 2010/11
 *
 * Fichero: genvec.c
 **********************************************************************/

/**********************************************************************/
/*               F I C H E R O S   I N C L U I D O S                  */
/**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <malloc.h>
#include "codigop.h"
#include "genvec.h"

extern int lineno, linepos;
extern int PC;
extern char *yytext;
extern FILE *yyout;

OPCODE codigo[MAXINST];

/**********************************************************************/
char *nueva_etiqueta ()
/**********************************************************************/
{
   static int l = 0;
   char *m = malloc (5);

   sprintf (m, "L%d", l++);
   return m;
}

/**********************************************************************/
void inicio_generacion_codigo ()
/**********************************************************************/
{
   int i;

   for (i = 0; i < MAXINST; ++i) {
       codigo[i].comentarios = NULL;
       codigo[i].etiq = NULL;
   }
}

/**********************************************************************/
void comentario (char *c)
/**********************************************************************/
{
  char *com;

  com = malloc(strlen (c) + 3 + 1);
  sprintf(com, "; %s\n", c);

  if (codigo[PC].comentarios == NULL)
     codigo[PC].comentarios = com;
  else
  {
     int l = strlen (codigo[PC].comentarios) + strlen (com) + 1;

     codigo[PC].comentarios = realloc (codigo[PC].comentarios, l);
     strcat (codigo[PC].comentarios, com);
  }
}

/**********************************************************************/
void etiqueta (char *c)
/**********************************************************************/
{
  char *etiq;

  etiq = malloc(strlen (c) + 2 + 1);
  sprintf(etiq, "%s:\n", c);

  if (codigo[PC].comentarios == NULL)
     codigo[PC].comentarios = etiq;
  else
  {
     int l = strlen (codigo[PC].comentarios) + strlen (etiq) + 1;

     codigo[PC].comentarios = realloc (codigo[PC].comentarios, l);
     strcat (codigo[PC].comentarios, etiq);
  }
}

/**********************************************************************/
char *mnemonic (int code)
/**********************************************************************/
{
   switch (code) {
          case AND   :  return ("AND "); break;
          case ASG   :  return ("ASG "); break;
          case ASGI  :  return ("ASGI "); break;
          case CSF   :  return ("CSF "); break;
          case DRF   :  return ("DRF "); break;
          case DUP   :  return ("DUP "); break;
          case ENP   :  return ("ENP "); break;
          case EQ    :  return ("EQ "); break;
          case GT    :  return ("GT "); break;
          case GTE   :  return ("GTE "); break;
          case DIV   :  return ("DIV "); break;
          case MOD   :  return ("MOD "); break;
          case OR    :  return ("OR "); break;
          case JMF   :  return ("JMF "); break;
          case JMP   :  return ("JMP "); break;
          case JMT   :  return ("JMT "); break;
          case LT    :  return ("LT "); break;
          case LTE   :  return ("LTE "); break;
          case LVP   :  return ("LVP "); break;
          case NEQ   :  return ("NEQ "); break;
          case NGB   :  return ("NGB "); break;
          case NGI   :  return ("NGI "); break;
          case NOP   :  return ("NOP "); break;
          case OSF   :  return ("OSF "); break;
          case PLUS  :  return ("PLUS "); break;
          case POP   :  return ("POP "); break;
          case RD    :  return ("RD "); break;
          case SBT   :  return ("SBT "); break;
          case SRF   :  return ("SRF "); break;
          case STC   :  return ("STC "); break;
          case SWP   :  return ("SWP "); break;
          case TMS   :  return ("TMS "); break;
          case WRT   :  return ("WRT "); break;
          default    :  fprintf (stderr, "MNEMONIC (generador.c): code %d desconocido!", code);
                        exit(1);
   }
}

/**********************************************************************/
void escribir_instruccion (FILE * salida, int i)
/**********************************************************************/
{
   if (codigo[i].comentarios != NULL)
      fprintf (salida, "%s", codigo[i].comentarios);
   fprintf (salida, "   ");
   fprintf (salida, "%s", mnemonic (codigo[i].op));
   switch (codigo[i].op) {
          case STC:
          case RD:
          case WRT: fprintf (salida, "%2d", codigo[i].arg1); break;
          case ENP:
          case JMP:
          case JMT:
          case JMF: if (codigo[i].etiq == NULL)
                       fprintf (salida, "%2d", codigo[i].arg1);
                    else
                       fprintf (salida, "%s", codigo[i].etiq);
                    break ;
          case SRF: fprintf (salida, "%2d %2d", codigo[i].arg1, codigo[i].arg2); break;
          case OSF: fprintf (salida, "%2d %2d %s", codigo[i].arg1, codigo[i].arg2, codigo[i].etiq); break;
   }
   fprintf (salida, "\n");
}

/**********************************************************************/
void generar (int op, ...)
/**********************************************************************/
{
   va_list args;
   short int arg;
   char operator;
   char *argumento;

   if (PC == MAXINST)
      printf ("Vector de instrucciones agotado", yytext, lineno, linepos);
   else {
      va_start (args, op);
      codigo[PC].op = op ;
      switch (op)
      {
             case AND  :
             case ASG  :
             case ASGI :
             case CSF  :
             case DRF  :
             case EQ   :
             case GT   :
             case GTE  :
             case DIV  :
             case MOD  :
             case OR   :
             case LT   :
             case LTE  :
             case LVP  :
             case NEQ  :
             case NGB  :
             case NGI  :
             case PLUS :
             case SBT  :
             case TMS  :
             case NOP  :
             case DUP  :
             case POP  :
             case SWP  :
                    break ;
             case ENP  :
             case JMF  :
             case JMP  :
             case JMT  :
                    argumento = va_arg (args, char*);
                    if (isdigit(*argumento))
                       codigo[PC].arg1 = atoi (argumento);
                    else
                       codigo[PC].etiq = argumento;
                    break;
             case STC  :
             case RD   :
             case WRT  :
                    codigo[PC].arg1 = va_arg (args, int);
                    break;
             case SRF  :
                    codigo[PC].arg1 = va_arg (args, int);
                    codigo[PC].arg2 = va_arg (args, int);
                    break;
             case OSF  :
                    codigo[PC].arg1 = va_arg (args, int);
                    codigo[PC].arg2 = va_arg (args, int);
                    codigo[PC].etiq = strdup (va_arg (args, char*));
                    break;
             default : fprintf (stderr, "GENERAR: codigo %d desconocido!!!\n", op);
      }
      ++PC;
   }
}

/**********************************************************************/
void fin_generacion_codigo ()
/**********************************************************************/
{
   int i;

   for (i = 0; i < PC; ++i)
	  escribir_instruccion (yyout, i);
}

