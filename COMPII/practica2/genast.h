/**********************************************************************
 * Practicas de Compiladores II 2010/11
 *
 * Fichero: genast.h
 **********************************************************************/

/**********************************************************************/
/*                              T I P O S                             */
/**********************************************************************/

typedef enum { comm, inst, lab} NODETYPE;

typedef struct {
		char op;
		short arg1, arg2, arg3;
		char *etiq;
		} OPCODE;

typedef union {
		char *comentario;
		OPCODE instr;
		char *etiqueta;
	      } CONTENT;

typedef struct {
                NODETYPE type;
		CONTENT content;
	       } NODE;

/**********************************************************************/
/*                          F U N C I O N E S                         */
/**********************************************************************/

char *newtemp ();
char *newlabel ();
LISTA newcode ();
void comment (pLISTA codigo, char *c);
void label (pLISTA codigo, char *c);
char *mnemonic (int code);
void dumpnode (FILE * salida,  NODE *node);
void xmldumpnode (FILE * salida,  NODE *node);
LISTA code (int op, ...);
void emit (pLISTA codigo, int op, ...);
void dumpcode (LISTA codigo, FILE* salida);
void xmldumpcode (LISTA codigo, FILE* salida);

