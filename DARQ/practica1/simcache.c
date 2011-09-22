#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAXLINE	32

/* POR HACER: definir estructuras de datos */

int
main(int argc, char *argv[])
{
    int size_cache = 14;		/* log2 del tamaño de cache en bytes */
    int size_bloque = 5;		/* log2 del tamaño de bloque en bytes */
    int num_max_refer = 10000;
    int i, tipo_acceso, direccion;
    char politica = 'c';
    char linea[MAXLINE], *otra;
	
	//Estructuras para BLOQUE y CACHE
	struct bloque{
		int TAG;
		int val;
		int sucio; //Sucio = 1 | Limpio = 0
	};

	//SALIDAS
	/**
		- ins: Total de instrucciones ejecutadas (#ins)
		- lec: Total de lecturas de datos (#lec)
		- esc: Total de escrituras de datos (#esc)
		- refs: Número de referencias (#refs = #ins + #lec + #esc)
		- fallos: Fallos en total (#fallos) 
		- m: Tasa de fallos m = #fallos/#refs
		- mdatos: Tasa de fallos de datos mdatos = #flec + #fesc / #lec + #esc
		- fins: Fallos buscando instrucción (#fins)
		- mins: Tasa de fallos de instrucción m = #fins/#refs
		- flec: Fallos en lectura de datos (#flec)
		- mlec: Tasa de fallos de lectura m = #flec/#lec
		- fesc: Fallos en escritura de datos (#fesc)
		- mesc: Tasa de fallos de escritura m = #fesc/#esc
		- mp_mc: B transferidos de MP -> MC
		- mc_mp: B transferidos de MC -> MP
		- sucios: Total bloques sucios
	*/
	int ins, lec, esc, refs, fallos, fins, flec, fesc, mp_mc, mc_mp, sucios;
	float m, mins, mlec, mesc, mdatos;
	
	for (i = 1; i < argc; i++)
    {
		switch (argv[i][1])		/* argv[i][0]='-' */
		{
			case 'U':
				size_cache = atoi(argv[i] + 2);
			break;
			case 'B':
				size_bloque = atoi(argv[i] + 2);
			break;
			case 'w':
				politica = *(argv[i] + 2);
			break;
			case 'z':
				num_max_refer = atoi(argv[i] + 2);
			break;
			default:
				printf("Parametros incorrectos\n");
				exit(1);
		} /* del switch */
    }	/* del for */
	
    /* comprobación de los parámetros especificados por el usuario */
    /*printf("U=%d, B=%d, W=%c, MAX=%d\n", 
		size_cache, size_bloque, politica, num_max_refer);*/
		
    /* POR HACER: inicializar estructuras de datos */
	
	//INICIANDO CACHE
	struct bloque cache[1<<size_cache];
	for(i=0;i<(1<<size_cache);i++){
		cache[i].TAG = 0;
		cache[i].val = 0;
		cache[i].sucio = 0;
	}
	
	ins = 0, lec = 0, esc = 0, refs = 0, fallos = 0, mdatos = 0.0, m = 0.0, fins = 0, mins = 0.0, flec = 0, mlec = 0.0, fesc = 0, mesc = 0.0, mp_mc = 0, mc_mp = 0, sucios = 0;
	
	
	//Variables de ejecucion
	int set = 0, tag = 0, num_bloque= 0, bloque = 0, contenedores = 0, bytes_bloque = 0, bytes_cache = 0;
    otra = fgets(linea, MAXLINE, stdin);	   /* lectura de primera línea de la traza */
	
    for (i = 0; (i < num_max_refer) && (otra != NULL); i++)
    {
		sscanf(linea, "%d%x", &tipo_acceso, &direccion);
		/*Obteniendo los datos necesarios*/
		num_bloque = (direccion>>size_bloque); //num_bloque
		contenedores = 1<<(size_cache - size_bloque); //Numero de contenedores 2^(U-B)
		bytes_bloque = 1 << size_bloque; //Tamaño del bloque: 2^B
		tag = num_bloque >> (size_cache-size_bloque);
		set = num_bloque%contenedores;
		bytes_cache = 1 << size_cache;
		
		/*	volcado de la línea de traza
		printf("acc:%d, dir:%x\n", tipo_acceso, direccion);*/

		/* POR HACER: procesado de linea de traza */
		//Contando las instrucciones ejecutadas
		switch(tipo_acceso){
			case 0: //Lectura
				lec++;
				if(cache[set].val == 0 || cache[set].TAG != num_bloque/contenedores){ //Lectura NOK
					if(politica == 'c' && cache[set].sucio == 1){
						//Hay que enviar el bloque Mc->Mp por ser CB al RPL
						mc_mp += bytes_bloque;
					}
					
					//Traemos el bloque de memoria y validamos en cache FLEC++ y FALLOS++
					mp_mc += bytes_bloque;
					cache[set].TAG = tag;
					cache[set].val = 1;
					cache[set].sucio = 0;
					flec++;
					fallos++;
				}else{ //Lectura OK
					/*No hay transferencia de datos*/
				}
			break;
			case 1: //Escritura
				esc++;
				if(cache[set].val == 0 || cache[set].TAG != num_bloque/contenedores){ //Escritura NOK
					if(politica == 'c' && cache[set].sucio == 1){
						//Se envía el bloque Mc->Mp por ser CB al RPL
						mc_mp += bytes_bloque;
					}
					
					//Traemos el bloque de Mp->Mc
					mp_mc += bytes_bloque;
					cache[set].TAG = tag;
					cache[set].val = 1;
					cache[set].sucio = 0;
					fesc++;
					fallos++;
					
					if(politica == 'c'){ //Política CB
						//Marcamos el bloque sucio
						cache[set].sucio = 1;
					}else if(politica == 'w'){ //Politica WT
						//Enviamos la palabra a Mc->Mp
						mc_mp += 4;
					}
				}else{ //Escritura OK
					if(politica == 'c'){
						//Marcamos el bloque sucio
						cache[set].sucio = 1;
					}else if(politica == 'w'){
						//Enviamos la palabra a Mc->Mp
						mc_mp += 4;
					}
				}
			break;
			case 2: //Instruccion
				ins++;
				if(cache[set].val == 0 || cache[set].TAG != num_bloque/contenedores){ //Escritura NOK
					if(politica == 'c' && cache[set].sucio == 1){
						//Se envía el bloque Mc->Mp por ser CB al RPL
						mc_mp += bytes_bloque;
					}
					
					//Traemos el bloque de Mp->Mc
					mp_mc += bytes_bloque;
					cache[set].TAG = tag;
					cache[set].val = 1;
					cache[set].sucio = 0;
					fins++;
					fallos++;
					
				}else{ //Escritura OK
					/* No hay transferencia de datos */
				}
			break;
		}
		
		otra = fgets(linea, MAXLINE, stdin);   /* lectura de siguiente línea de la traza */
    }
	
	if(politica == 'c'){
		for(i = 0;i<=(1<<size_cache);i++)
			if(cache[i].sucio == 1)
				sucios++;
	}
	
    /* POR HACER: volcado de resultados */
	//Calculando resultados finales
	refs = ins + lec + esc;
	//Calculando tasas
	m = (float)fallos/refs;
	mins = (float)fins/ins;
	mlec = (float)flec/lec;
	mesc = (float)fesc/esc;
	mdatos = (float)(fesc+flec)/(esc+lec);
	
	//Mostrando los datos
	printf("Cache(bytes): Blocksize= %d, Usize= %d\n", size_bloque, size_cache);
	printf("Politicas: asociativ=1, escrit: %c\n\n", politica);
	printf("Métricas\tTotal\tInstr\tDatos\tlect\tescr\n");
	printf("--------\t-----\t-----\t-----\t----\t----\n");
	printf("Total accesos\t%d\t%d\t%d\t%d\t%d\n", refs, ins, lec+esc, lec, esc);
	printf("Fracción\t%d\t%4.4f\t%4.4f\t%4.4f\t%4.4f\n\n", refs/refs, (float)ins/refs, (float)(lec+esc)/refs, (float)lec/refs, (float)esc/refs);
	printf("Fallos\t\t%d\t%d\t%d\t%d\t%d\n", fallos, fins, flec+fesc, flec, fesc);
	printf("Fracción\t%4.4f\t%4.4f\t%4.4f\t%4.4f\t%4.4f\n\n", m, mins, mdatos, mlec, mesc);
	printf("Bytes desde Mp hacia Mc = %d\n", mp_mc);
	printf("Bytes desde Proc/Mc hacia Mp = %d\n", mc_mp);
	printf("Tráfico total (bytes) por referencia = %d\n", mp_mc+mc_mp);
	printf("Bloques sucios al finalizar simulación (CB) = %d\n", sucios);
}
