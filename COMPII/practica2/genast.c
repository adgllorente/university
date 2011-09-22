/**********************************************************************
 * Practicas de Compiladores II 2010-11
 *
 * Fichero: genast.c
 **********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <malloc.h>
#include "listas.h"
#include "codigop.h"
#include "genast.h"

/**********************************************************************/
char *newlabel ()
/**********************************************************************/
{
   static int l = 0;
   char *m = malloc (5);

   sprintf (m, "L%d", l++);
   
   return m;
}

/**********************************************************************/
LISTA newcode ()
/**********************************************************************/
{
  LISTA codigo;

  crear_vacia (&codigo);
  return codigo;
}

/**********************************************************************/
void comment (pLISTA codigo, char *c)
/**********************************************************************/
{
  NODE node;
  char *com;

  com = malloc(strlen (c) + 3);
  sprintf(com, "; %s", c);

  node.type = comm;
  node.content.comentario = com;

  anadir_derecha_copiando ((ELEMENTO) &node, codigo, sizeof(node));
}

/**********************************************************************/
void label (pLISTA codigo, char *c)
/**********************************************************************/
{
  NODE node;
  char *etiq;

  etiq = malloc(strlen (c) + 2);
  sprintf(etiq, "%s:", c);

  node.type = lab;
  node.content.etiqueta = etiq;

  anadir_derecha_copiando ((ELEMENTO) &node, codigo, sizeof(node));
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
void dumpnode (FILE * salida,  NODE *node)
/**********************************************************************/
{
   switch(node->type) {
     case comm : fprintf (salida, "%s\n", node->content.comentario);
		 break;
     case lab : fprintf (salida, "%s\n", node->content.etiqueta);
		 break;
     case inst : fprintf (salida, "   ");
                 fprintf (salida, "%s", mnemonic (node->content.instr.op));
                 switch (node->content.instr.op) {
                        case STC:
                        case RD:
                        case WRT: fprintf (salida, "%2d", node->content.instr.arg1); break;
                        case ENP:
                        case JMP:
                        case JMT:
                        case JMF: if (node->content.instr.etiq == NULL)
				     fprintf (salida, "%2d", node->content.instr.arg1);
                                  else
                                     fprintf (salida, "%s", node->content.instr.etiq);
                                  break ;
                        case SRF: fprintf (salida, "%2d %2d", node->content.instr.arg1, node->content.instr.arg2); break;
                        case OSF: if (node->content.instr.etiq == NULL)
                                     fprintf (salida, "%2d %2d %2d", node->content.instr.arg1, node->content.instr.arg2, node->content.instr.arg3);
                                  else
                                     fprintf (salida, "%2d %2d %s", node->content.instr.arg1, node->content.instr.arg2, node->content.instr.etiq);
                                  break ;
		 }
                 fprintf (salida, "\n");
     }
}

/**********************************************************************/
void xmldumpnode (FILE * salida,  NODE *node)
/**********************************************************************/
{
   switch(node->type) {
     case lab :  fprintf (salida, "<l>%s</l>\n", node->content.etiqueta);
		 break;
     case inst : fprintf (salida, "<p>%s", mnemonic (node->content.instr.op));
                 switch (node->content.instr.op) {
                        case STC:
                        case RD:
                        case WRT: fprintf (salida, "%2d", node->content.instr.arg1); break;
                        case ENP:
                        case JMP:
                        case JMT:
                        case JMF: if (node->content.instr.etiq == NULL)
				     fprintf (salida, "%2d", node->content.instr.arg1);
                                  else
                                     fprintf (salida, "%s", node->content.instr.etiq);
                                  break ;
                        case SRF: fprintf (salida, "%2d %2d", node->content.instr.arg1, node->content.instr.arg2); break;
                        case OSF: if (node->content.instr.etiq == NULL)
                                     fprintf (salida, "%2d %2d %2d", node->content.instr.arg1, node->content.instr.arg2, node->content.instr.arg3);
                                  else
                                     fprintf (salida, "%2d %2d %s", node->content.instr.arg1, node->content.instr.arg2, node->content.instr.etiq);
                                  break ;
		 }
                 fprintf (salida, "</p>\n");
     }
}

/**********************************************************************/
void emit (pLISTA codigo, int op, ...)
/**********************************************************************/
{
   va_list args;
   short int arg;
   char operator;
   char *argumento;
   OPCODE instr;
   NODE node;

   va_start (args, op);
   instr.etiq = NULL;
   instr.op = op ;
   switch (op)
   {
          case AND  :
          case ASG  :
          case ASGI :
          case CSF  :
          case DIV  :
          case DRF  :
          case DUP  :
          case EQ   :
          case GT   :
          case GTE  :
          case LT   :
          case LTE  :
          case LVP  :
          case MOD  :
          case NEQ  :
          case NGB  :
          case NGI  :
          case NOP  :
          case OR   :
          case PLUS :
          case POP  :
          case SBT  :
          case SWP  :
          case TMS  :
                    break ;
          case ENP  :
          case JMF  :
          case JMP  :
          case JMT  :
                    argumento = va_arg (args, char*);
                    if (isdigit(*argumento))
                       instr.arg1 = atoi (argumento);
                    else
                       instr.etiq = strdup(argumento);
                    break;
          case STC  :
          case RD   :
          case WRT  :
                    instr.arg1 = va_arg (args, int);
                    break;
          case SRF  :
                    instr.arg1 = va_arg (args, int);
                    instr.arg2 = va_arg (args, int);
                    break;
          case OSF  :
                    instr.arg1 = va_arg (args, int);
                    instr.arg2 = va_arg (args, int);
                    argumento = va_arg (args, char*);
                    if (isdigit(*argumento))
                       instr.arg3 = atoi (argumento);
                    else
                       instr.etiq = strdup(argumento);
                    break;
          default : fprintf (stderr, "GENERAR: codigo %d desconocido!!!\n", op);
                    exit(1);
   }

   node.type = inst;
   node.content.instr = instr;
   anadir_derecha_copiando ((ELEMENTO) &node, codigo, sizeof(node));
}

/**********************************************************************/
LISTA code (int op, ...)
/**********************************************************************/
{
   va_list args;
   short int arg;
   char operator;
   char *argumento;
   OPCODE instr;
   LISTA codigo;
   NODE node;

   va_start (args, op);
   instr.etiq = NULL;
   instr.op = op ;
   switch (op)
   {
          case AND  :
          case ASG  :
          case ASGI :
          case CSF  :
          case DIV  :
          case DRF  :
          case DUP  :
          case EQ   :
          case GT   :
          case GTE  :
          case LT   :
          case LTE  :
          case LVP  :
          case MOD  :
          case NEQ  :
          case NGB  :
          case NGI  :
          case NOP  :
          case OR   :
          case PLUS :
          case POP  :
          case SBT  :
          case SWP  :
          case TMS  :
                    break ;
          case ENP  :
          case JMF  :
          case JMP  :
          case JMT  :
                    argumento = va_arg (args, char*);
                    if (isdigit(*argumento))
                       instr.arg1 = atoi (argumento);
                    else
                       instr.etiq = strdup(argumento);
                    break;
          case STC  :
          case RD   :
          case WRT  :
                    instr.arg1 = va_arg (args, int);
                    break;
          case SRF  :
                    instr.arg1 = va_arg (args, int);
                    instr.arg2 = va_arg (args, int);
                    break;
          case OSF  :
                    instr.arg1 = va_arg (args, int);
                    instr.arg2 = va_arg (args, int);
                    argumento = va_arg (args, char*);
                    if (isdigit(*argumento))
                       instr.arg3 = atoi (argumento);
                    else
                       instr.etiq = strdup(argumento);
                    break;
          default : fprintf (stderr, "GENERAR: codigo %d desconocido!!!\n", op);
                    exit(1);
   }
   node.type = inst;
   node.content.instr = instr;
   crear_unitaria_copiando (&codigo, (void *) &node, sizeof(node));

   return codigo;
}

/**********************************************************************/
void dumpcode (LISTA codigo, FILE* salida)
/**********************************************************************/
{
   int i;

   for (i = 1; i <= longitud_lista(codigo); ++i)
	 dumpnode (salida, observar(codigo, i));
}

/**********************************************************************/
void xmldumpcode (LISTA codigo, FILE* salida)
/**********************************************************************/
{
   int i;

   for (i = 1; i <= longitud_lista(codigo); ++i)
	 xmldumpnode (salida, observar(codigo, i));
}

