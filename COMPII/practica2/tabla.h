/**********************************************************************
 * fichero: tabla.h
 *          definiciones de una libreria de manejo de tablas de simbolos
 *          2010-11
 **********************************************************************/

/**********************************************************************/
/*                      D E F I N I C I O N E S                       */
/**********************************************************************/

#define TRUE            1
#define FALSE           0
#define TAMANO_TABLA    7    /* Numero de entradas en la tabla hash */

/**********************************************************************/
/*                              T I P O S                             */
/**********************************************************************/

typedef enum {
        PROGRAMA, 
        VARIABLE, 
        ACCION, 
        PARAMETRO, 
        } TIPO_SIMBOLO;

typedef enum {
        DESCONOCIDO,
        ENTERO,
        BOOLEANO,
        CHAR,
        CADENA
        } TIPO_VARIABLE;

typedef enum {
        VAL,
        REF
        } CLASE_PARAMETRO;

typedef struct {
    char *nombre;
    int nivel;

    TIPO_SIMBOLO tipo;

    /* Variables */
    TIPO_VARIABLE variable;

    /* Si variable, direccion; si accion, primera instruccion */
    int dir;

    /* Si accion, etiqueta primera instruccion */
    char etiq[50];
	
    /* Si es un parametro */
    CLASE_PARAMETRO parametro;
    int visible;
                 
    /* Si accion, lista de parametros */
    LISTA parametros;
	
	/* Si es un tipo o una variable de un tipo enumerativo, punteros 
	al primer y último elemento de la declaración, y al siguiente
	símbolo */
	struct SIMBOLO *tipoEnum;
	struct SIMBOLO *primerSimbolo;
	struct SIMBOLO *ultimoSimbolo;
	struct SIMBOLO *siguienteSimbolo;
	/* Ejemplos:
		enum Dias [LUNES, MARTES, MIERCOLES];
		Dias variableEnum;
		
		Variable -> tipo / variable / *tipoEnum / *primerSimbolo / *ultimoSimbolo / *siguienteSimbolo 
		Dias -> TIPO_ENUM / - / NULL / &LUNES / &MIERCOLES / NULL
		LUNES -> TIPO_ENUM / ENUM / &Dias / - / - / &MARTES
		etc.
		variableEnum -> VARIABLE / ENUM / &Dias / - / - / -
	*/ 
	
	/* Añadimos los datos necesarios para los vectores */
	int extremo1, extremo2, es_vector;
	TIPO_VARIABLE tipo_extremo;
	
	int valor;
	int asignado; //0: NO | 1: SI
	int es_componente; //Sirve para garantizar que como parámetro sólo pasamos una componente de un vector
	
} SIMBOLO;

typedef LISTA TABLA_SIMBOLOS[TAMANO_TABLA];

/**********************************************************************/
/*                              M A C R O S                           */
/**********************************************************************/

#define ES_VARIABLE(e) ((e).tipo == VARIABLE)
#define ES_PARAMETRO(e) ((e).tipo == PARAMETRO)
#define ES_ACCION(e) ((e).tipo == ACCION)
#define ES_VALOR(e) (((e).tipo == PARAMETRO) && ((e).parametro == VAL))
#define ES_REFERENCIA(e) (((e).tipo == PARAMETRO) && ((e).parametro == REF))

/**********************************************************************/
/*                          F U N C I O N E S                         */
/**********************************************************************/

/**********************************************************************/
void inicializar_tabla (TABLA_SIMBOLOS tabla);
/**********************************************************************
Crea una tabla de simbolos vacia.  Este procedimiento debe invocarse 
antes de hacer ninguna operacion con la tabla de simbolos.
**********************************************************************/

/**********************************************************************/
SIMBOLO *buscar_simbolo (TABLA_SIMBOLOS tabla, 
                         char *nombre);
/**********************************************************************
Busca en la tabla el simbolo de mayor nivel cuyo nombre coincida
con el del parametro (se distinguen minusculas y mayusculas).  Si
existe, devuelve un puntero como resultado, de lo contrario devuelve
NULL.
**********************************************************************/

/**********************************************************************/
SIMBOLO *introducir_programa (TABLA_SIMBOLOS tabla, 
                              char *nombre, 
                              char* etiq);
/**********************************************************************
Introduce en la tabla un simbolo PROGRAMA,  con el nombre
del parametro, de nivel 0, con la direccion del parametro. Dado que debe
ser el primer simbolo a introducir, NO SE VERIFICA QUE EL SIMBOLO YA
EXISTA.
**********************************************************************/

/**********************************************************************/
SIMBOLO *introducir_variable (TABLA_SIMBOLOS tabla, 
                              char *nombre, 
                              TIPO_VARIABLE variable, 
                              int nivel, 
                              int dir);
							  
SIMBOLO *introducir_variable_vector (TABLA_SIMBOLOS tabla, 
                              char *nombre, 
                              TIPO_VARIABLE variable, 
                              int nivel, 
                              int dir,
							  int extremo1,int extremo2,
							  int tipo_extremo);
/**********************************************************************
Si existe un simbolo en la tabla del mismo nivel y con el mismo
nombre, devuelve NULL.  De lo contrario, introduce un simbolo
VARIABLE (simple) con los datos de los argumentos.
**********************************************************************/

/**********************************************************************/
SIMBOLO *introducir_accion (TABLA_SIMBOLOS tabla, 
                            char *nombre, 
                            int nivel, 
                            char *etiq);
/**********************************************************************
Si existe un simbolo en la tabla del mismo nivel y con el mismo
nombre, devuelve NULL.  De lo contrario, introduce un simbolo
ACCION con los datos de los argumentos.
**********************************************************************/

/**********************************************************************/
SIMBOLO *introducir_parametro (TABLA_SIMBOLOS tabla, 
                               char *nombre, 
                               TIPO_VARIABLE variable, 
                               CLASE_PARAMETRO parametro, 
                               int nivel, 
                               int dir);
/**********************************************************************
Si existe un simbolo en la tabla del mismo nivel y con el mismo
nombre, devuelve NULL.  De lo contrario, introduce un simbolo
PARAMETRO con los datos de los argumentos. 
**********************************************************************/

/**********************************************************************/
void eliminar_programa (TABLA_SIMBOLOS tabla);
/**********************************************************************
Elimina de la tabla todos los simbolos PROGRAMA de nivel 0 (deberia 
haber uno solo).
**********************************************************************/

/**********************************************************************/
void eliminar_variables (TABLA_SIMBOLOS tabla, 
                         int nivel);
/**********************************************************************
Elimina de la tabla todas las variables (simples y vectores) que sean
del nivel del argumento. NO ELIMINA PARAMETROS.
**********************************************************************/

/**********************************************************************/
void ocultar_parametros (TABLA_SIMBOLOS tabla, 
                         int nivel);
/**********************************************************************
Marca todos los parametros de un nivel como ocultos para que no puedan
ser encontrados, pero se mantenga la definicion completa de la
accion donde estan declarados para verificacion de 
invocaciones a la accion.
**********************************************************************/

/**********************************************************************/
void eliminar_parametros_ocultos (TABLA_SIMBOLOS tabla, 
                                  int nivel);
/**********************************************************************
Elimina de la tabla todas los parametros que hayan sido ocultados
previamente.  LOS PROCEDIMIENTOS Y FUNCIONES DONDE ESTABAN DECLARADOS
DEBEN SER ELIMINAODS TAMBIEN PARA MANTENER LA COHERENCIA DE LA TABLA.
**********************************************************************/

/**********************************************************************/
void eliminar_acciones (TABLA_SIMBOLOS tabla, 
                        int nivel);
/**********************************************************************
Elimina de la tabla todas los proceidimientos de un nivel.  
LOS PARAMETROS DE ESTAS ACCIONES
DEBEN SER ELIMINADOS TAMBIEN PARA MANTENER LA COHERENCIA DE LA TABLA.
**********************************************************************/

