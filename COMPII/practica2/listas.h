/*****************************************************************************
	Tema:	TAD listas gen'ericas. 
	Uso:	Los algoritmos, detalladamente comentados, pueden encontrarse
			en cualquier libro de Estructuras de Datos y Algoritmos.
			
			Hay dos tipos de operaciones de observarci'on e inserci'on:
			
				-si el nombre acaba con '_copiando',  trabajan con copias
					 (devuelven una copia del dato,  insertan una copia, ..)
				-el resto,  se les suministra o bien un puntero a un dato
				 a insertar o bien un puntero para devolver una copia a
				 un dato buscado.
				 
			La lista gen'erica est'a implementada como una lista enlazada
			de nodos. Cada nodo contiene un enlace al siguiente nodo y
			un puntero gen'erico. De este puntero "colgar'a" el dato.
*****************************************************************************/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

/*****************************************************************************
TIPOS
*****************************************************************************/

typedef void *ELEMENTO; 		/* puntero geneérico */

typedef struct nodo {
	ELEMENTO dato; 
	struct nodo *siguiente; 
} NODO, *pNODO; 

typedef struct {
	pNODO primero, ultimo; 
	int elementos; 
} LISTA, *pLISTA; 

/*****************************************************************************
FUNCIONES
*****************************************************************************/

void crear_vacia (pLISTA pL);
void crear_unitaria (pLISTA pL, ELEMENTO e);
void crear_unitaria_copiando (pLISTA pL, ELEMENTO e, int tamano);
int es_vacia (LISTA l);
void anadir_derecha_copiando (ELEMENTO e, pLISTA pL, int tamano);
void anadir_derecha (ELEMENTO e, pLISTA pL);
void anadir_izquierda (ELEMENTO e, pLISTA pL);
void anadir_izquierda_copiando (ELEMENTO e, pLISTA pL, int tamano);
ELEMENTO observar_izquierda_copiando (LISTA l, int tamano);
ELEMENTO observar_izquierda (LISTA l);
ELEMENTO observar_derecha_copiando (LISTA l, int tamano);
ELEMENTO observar_derecha (LISTA l);
int longitud_lista (LISTA l);
ELEMENTO observar_copiando (LISTA l, int p, int tamano);
ELEMENTO observar (LISTA l, int p);
void eliminar_derecha (pLISTA pL);
void eliminar_izquierda (pLISTA pL);
void concatenar (pLISTA pL1, LISTA l2);
int esta (ELEMENTO e, LISTA l, int (*igual) (void *, void *));
ELEMENTO busca (ELEMENTO e, LISTA l, int (*igual) (void *, void *));
int pos (ELEMENTO e, LISTA l, int (*igual) (void *, void *));
int posGen (ELEMENTO e, LISTA l, int (*igual) (void *, void *));
void insertar_copiando (pLISTA pL, int i, ELEMENTO e, int tamano);
void borrar (pLISTA pL, int i);
void modificar_copiando (pLISTA pL, int i, ELEMENTO e, int tamano);
void asignar (pLISTA nueva, LISTA vieja, int tamano);
void liberar (pLISTA pL);
