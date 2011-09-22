/*****************************************************************************
	Tema:		TAD LISTAs gen'ericas. 
	Uso:	Los algoritmos, detalladamente comentados, pueden encontrarse
			en cualquier libro de Estructuras de Datos y Algoritmos.
			
			Hay dos tipos de operaciones de observarci'on e inserci'on:
			
				-si el nombre acaba con 'C',  trabajan con copias
					 (devuelven una copia del dato,  insertan una copia, ..)
				-el resto,  se les suministra o bien un puntero a un dato
				 a insertar o bien un puntero para devolver una copia a
				 un dato buscado.
				 
			La LISTA gen'erica est'a implementado como una LISTA enlazada
			de NODOs. Cada NODO contiene un enlace al siguienteuiente NODO y
			un puntero gen'erico. Des este puntero "colgar'a" el dato.
*****************************************************************************/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

/*****************************************************************************
				TIPOS
*****************************************************************************/
typedef void *ELEMENTO; 		/* puntero genŽrico */

typedef struct nodo{
	ELEMENTO dato; 
	struct nodo *siguiente; 
} NODO, *pNODO; 

typedef struct LISTA{
	pNODO primero, ultimo; 
	int elementos; 
} LISTA, *pLISTA; 


/**********************************************************************/
void crear_vacia (pLISTA pL)
/**********************************************************************/
{
	pL->primero = NULL; 
	pL->ultimo = NULL; 
	pL->elementos = 0; 
}
/**********************************************************************/
void crear_unitaria (pLISTA pL, ELEMENTO e)
/**********************************************************************/
{
	pL->primero = (pNODO) malloc (sizeof (NODO)); 
	pL->ultimo = pL->primero; 
	pL->primero->dato = e; 
	pL->primero->siguiente = NULL; 
	pL->elementos = 1; 
}

/**********************************************************************/
void crear_unitaria_copiando (pLISTA pL, ELEMENTO e, int tamano)
/**********************************************************************/
{
	pL->primero = (pNODO) malloc (sizeof (NODO)); 
	pL->ultimo = pL->primero; 
	pL->primero->dato = (void *) malloc (tamano); 
	memcpy (pL->primero->dato, e, tamano); 
	pL->primero->siguiente = NULL; 
	pL->elementos = 1; 
}

/**********************************************************************/
int es_vacia (LISTA l)
/**********************************************************************/
{	
	return (l.elementos == 0); 
}

/**********************************************************************/
void anadir_derecha_copiando (ELEMENTO e, pLISTA pL, int tamano)
/**********************************************************************/
{	
	if (es_vacia (*pL))
	   crear_unitaria_copiando (pL, e, tamano); 
	else
	{
		pL->ultimo->siguiente = (pNODO) malloc (sizeof (NODO)); 
		pL->ultimo = pL->ultimo->siguiente; 
		pL->ultimo->dato = (void *) malloc (tamano); 
		memcpy (pL->ultimo->dato, e, tamano); 
		pL->ultimo->siguiente = NULL; 
	    pL->elementos++; 
	}
}

/**********************************************************************/
void anadir_derecha (ELEMENTO e, pLISTA pL)
/**********************************************************************/
{	
	if (es_vacia (*pL))
	   crear_unitaria (pL, e); 
	else
	{
		pL->ultimo->siguiente = (pNODO) malloc (sizeof (NODO)); 
		pL->ultimo = pL->ultimo->siguiente; 
		pL->ultimo->dato = e; 
		pL->ultimo->siguiente = NULL; 
	   pL->elementos++; 
	}
}

/**********************************************************************/
void anadir_izquierda (ELEMENTO e, pLISTA pL)
/**********************************************************************/
{
	if (es_vacia (*pL))
	   crear_unitaria (pL, e); 
	else
	{
	    pNODO nuevoNodo; 

		nuevoNodo = (pNODO) malloc (sizeof (NODO)); 
		nuevoNodo->dato = e; 
		nuevoNodo->siguiente = pL->primero; 
		pL->primero = nuevoNodo; 
	    pL->elementos++; 
	}
}

/**********************************************************************/
void anadir_izquierda_copiando (ELEMENTO e, pLISTA pL, int tamano)
/**********************************************************************/
{
	if (es_vacia (*pL))
	   crear_unitaria_copiando (pL, e, tamano); 
	else
	{
        pNODO nuevoNodo; 

		nuevoNodo = (pNODO) malloc (sizeof (NODO)); 
		nuevoNodo->dato = (void *) malloc (tamano); 
		memcpy (nuevoNodo->dato, e, tamano); 
		nuevoNodo->siguiente = pL->primero; 
		pL->primero = nuevoNodo; 
	    pL->elementos++; 
	}
}
/**********************************************************************/
ELEMENTO observar_izquierda_copiando (LISTA l, int tamano)
/**********************************************************************/
{
	ELEMENTO res; 

	res = (void *) malloc (tamano); 
	memcpy (res, l.primero->dato, tamano); 
	return (res); 
}

/**********************************************************************/
ELEMENTO observar_izquierda (LISTA l)
/**********************************************************************/
{	
	return (l.primero->dato); 
}

/**********************************************************************/
ELEMENTO observar_derecha_copiando (LISTA l, int tamano)
/**********************************************************************/
{
	ELEMENTO res; 

	res = (void *) malloc (tamano); 
	memcpy (res, l.ultimo->dato, tamano); 
	return (res); 
}

/**********************************************************************/
ELEMENTO observar_derecha (LISTA l)
/**********************************************************************/
{	
	return (l.ultimo->dato); 
}

/**********************************************************************/
int longitud_lista (LISTA l)
/**********************************************************************/
{
	return (l.elementos); 
}

/**********************************************************************/
ELEMENTO observar_copiando (LISTA l, int p, int tamano)
/**********************************************************************/
{
	int i; 
	ELEMENTO res; 
	pNODO aux; 
	
	res = (void *) malloc (tamano); 
	if (p == longitud_lista (l))
		memcpy (res, l.ultimo->dato, tamano); 
	else
	{
		aux = l.primero; 
		for (i = 1; i < p; i++)
			aux = aux->siguiente; 
		memcpy (res, aux->dato, tamano); 
	}
		
	return (res); 
}

/**********************************************************************/
ELEMENTO observar (LISTA l, int p)
/**********************************************************************/
{
	int i; 
	pNODO aux; 
	
	if (p == longitud_lista (l))
		return (l.ultimo->dato); 
	else{
		aux = l.primero; 
		for (i = 1; i < p; i++)
			aux = aux->siguiente; 
		return (aux->dato); 
	}
}

/**********************************************************************/
void eliminar_derecha (pLISTA pL)
/**********************************************************************/
{
	if (pL->primero == pL->ultimo)
	{
		free (pL->primero->dato); 
		free (pL->primero); 
		pL->primero = NULL; 
		pL->ultimo = NULL; 
	}
	else
	{
        pNODO aux; 

		aux = pL->primero; 
		while (aux->siguiente != pL->ultimo)
			aux = aux->siguiente; 
		aux->siguiente = NULL; 
		free (pL->ultimo->dato); 
		free (pL->ultimo); 
		pL->ultimo = aux; 
	}
	pL->elementos--; 
}

/**********************************************************************/
void eliminar_izquierda (pLISTA pL)
/**********************************************************************/
{	pNODO aux; 

	aux = pL->primero; 
	pL->primero = pL->primero->siguiente; 
	if (pL->primero == NULL)
		pL->ultimo = NULL; 
	free (aux->dato); 
	free (aux); 
	pL->elementos--; 
}

/**********************************************************************/
void concatenar (pLISTA pL1, LISTA l2)
/**********************************************************************/
{	
	if (l2.elementos != 0)
	{
		if (es_vacia(*pL1))
		{
			*pL1 = l2; 
		}
		else
		{
			pL1->ultimo->siguiente = l2.primero; 
			pL1->ultimo = l2.ultimo; 
			pL1->elementos = pL1->elementos+l2.elementos; 
		}
	}

}

/**********************************************************************/
int esta (ELEMENTO e, LISTA l, int (*igual) (void *, void *))
/**********************************************************************/
{
	if (l.primero == NULL)
		return (0); 
	else
	{
	    pNODO aux; 
	
		aux = l.primero; 
		while (! (*igual) (aux->dato, e) && (aux != l.ultimo))
			aux = aux->siguiente; 
		return ((*igual) (aux->dato, e)); 
	}

}

/**********************************************************************/
ELEMENTO busca (ELEMENTO e, LISTA l, int (*igual) (void *, void *))
/**********************************************************************/
{
	if (l.primero == NULL)
		return ((ELEMENTO) NULL); 
	else
	{
		pNODO aux; 
	
		aux = l.primero; 
		while (! (*igual) (aux->dato, e) && (aux != l.ultimo))
			aux = aux->siguiente; 
		if ((*igual) (aux->dato, e))
		  return ((ELEMENTO) aux); 
		else
		  return ((ELEMENTO) NULL); 
	}

}

/**********************************************************************/
int pos (ELEMENTO e, LISTA l, int (*igual) (void *, void *))
/**********************************************************************/
{
	pNODO aux; 
	int i; 
	
	aux = l.primero; 
	i = 1; 
	while (! (*igual) (aux->dato, e) ){
		aux = aux->siguiente; 
		i++; 
	}
	return (i); 
}

/**********************************************************************/
int posGen (ELEMENTO e, LISTA l, int (*igual) (void *, void *))
/**********************************************************************/
{
	pNODO aux; 
	int pos = 1; 
	
	if (l.primero == NULL)
		return (0); 
	else{
		aux = l.primero; 
		while (! (*igual) (aux->dato, e) && (aux != l.ultimo))
		{
			aux = aux->siguiente; 
			pos++; 
		}
		if ((*igual) (aux->dato, e))
			return (pos); 
		else
			return (0); 
	}
}

/**********************************************************************/
void insertar_copiando (pLISTA pL, int i, ELEMENTO e, int tamano)
/**********************************************************************/
{	pNODO aux, siguienteAux; 
	int indSig; 
	
	if (i == 1)
		anadir_izquierda_copiando (e, pL, tamano); 
	else if (i == longitud_lista (*pL)+1)
		anadir_derecha_copiando (e, pL, tamano); 
	else{
		aux = pL->primero; 
		indSig = 2; 
		while (indSig<i){
			aux = aux->siguiente; 
			indSig++; 
		}
		siguienteAux = aux->siguiente; 
		aux->siguiente = (pNODO) malloc (sizeof (NODO)); 
		aux = aux->siguiente; 
		memcpy (aux->dato, e, tamano); 
		aux->siguiente = siguienteAux; 
		pL->elementos++; 
	}
}
 
/**********************************************************************/
void borrar (pLISTA pL, int i)
/**********************************************************************/
{	pNODO aux, siguienteAux; 
	int indSig; 
	
	if (i == 1)
		eliminar_izquierda (pL); 
	else if (i == longitud_lista (*pL))
		eliminar_derecha (pL); 
	else{
		aux = pL->primero; 
        indSig = 2; 
        while (indSig<i){
          aux = aux->siguiente; 
          indSig++; 
        }
        siguienteAux = aux->siguiente; 
        aux->siguiente = siguienteAux->siguiente; 
        free (siguienteAux->dato); 
        free (siguienteAux); 
        pL->elementos--; 
	}
}

/**********************************************************************/
void modificar_copiando (pLISTA pL, int i, ELEMENTO e, int tamano)
/**********************************************************************/
{ 	pNODO aux;  
	int ind; 
  
    if (i == longitud_lista (*pL))
    	memcpy (pL->ultimo->dato, e, tamano); 
    else
	{
    	aux = pL->primero; 
        ind = 1; 
        while (ind < i)
		{
          aux = aux->siguiente; 
          ind++; 
        }
        memcpy (aux->dato, e, tamano); 
    }
}

/**********************************************************************/
void asignar (pLISTA nueva, LISTA vieja, int tamano)
/**********************************************************************/
{	int i; 

	crear_vacia (nueva); 
	for (i = 1; i <= longitud_lista (vieja); i++){
		anadir_derecha_copiando (vieja.primero->dato, nueva, tamano); 
		vieja.primero = vieja.primero->siguiente; 
	}
}

/**********************************************************************/
void liberar (pLISTA pL)
/**********************************************************************/
{	int n, i; 

	n = longitud_lista (*pL); 
	for (i = 1; i <= n; i++)
		eliminar_izquierda (pL); 
}
