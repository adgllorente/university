#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#include "trace.h"

/* variable global usada en simseg.c y trace_r.c */
char depura = 0;

/******************************************************************************
VARIABLES PARA CONTAR LOS CORTOCIRCUITOS
******************************************************************************/

int corto32 = 0;
int corto42 = 0;
int corto52 = 0;
int corto43 = 0;
int corto53 = 0;
int banco_registros = 0;

int ref;
float mcorto32 = 0;
float mcorto42 = 0;
float mcorto52 = 0;
float mcorto43 = 0;
float mcorto53 = 0;
float mbanco_registros = 0;

/******************************************************************************/
/* variables usadas en las funciones de simseg.c */
static IREG inula = {0, 0, 0, 0, -1, -1, -1, NOP, 0, 0};
static IREG etapa_Bin, etapa_Din, etapa_Ain, etapa_Min, etapa_Ein;
static IREG etapa_Bout, etapa_Dout, etapa_Aout, etapa_Mout, etapa_Eout;
static char carga_B = 2, carga_D = 1, carga_A = 1, carga_M = 1, carga_E = 1;

static unsigned long int instrucciones = 0;
static unsigned long int aritm = 0, loads = 0, stores = 0, saltos = 0, fp = 0;
static unsigned long int nulas = 0, validas = 0;
static unsigned long ccpu = 0, craw = 0;
static unsigned long int ciclos = 0;

/* tiempo de ejecución del mbanco_registrossimulador (ns) */
static hrtime_t user0, user1;

/******************************************************************************/

/* declaracion de funcion definida en trace_r.c */
extern int get_instr(IREG *ir);

/******************************************************************************/
/* funciones privadas */

static void
ini_cpu()
{ 
    etapa_Ein  = inula;
    etapa_Eout = inula;
    etapa_Min  = inula;
    etapa_Mout = inula;
    etapa_Ain  = inula;
    etapa_Aout = inula;
    etapa_Din  = inula;
    etapa_Dout = inula;
    etapa_Bout = inula;
}

static void
fin_cpu()
{
    unsigned long todocpu;

    fprintf(stdout, "\nCPI = %lu inst. / %lu ciclos = %2.2f ciclos/inst.\n", 
	    instrucciones, ciclos, ciclos/(float) instrucciones);

    fprintf(stdout, "%lu NOPs, %lu inst.validas -> %2.2f ciclos/inst.valida\n",
	    nulas, validas, ciclos/(float) validas);

    todocpu = ccpu + craw;
    fprintf(stdout, "ciclos: %lu cpu + %lu RAW = %lu ciclos\n",
	    ccpu, craw, todocpu);

    fprintf(stdout, "instr.: %lu aritm, %lu loads, %lu stores, %lu saltos, %lu fp\n",
	    aritm, loads, stores, saltos, fp);
	   
	/****************************************************
	Calculamos y mostramos los resultados de los cortos
	****************************************************/
	ref = corto32 + corto42 + corto52 + corto53 + corto43 + banco_registros;
	mcorto32 = (float)100*(corto32)/ref;
	mcorto42 = (float)100*(corto42)/ref;
	mcorto52 = (float)100*(corto52)/ref;
	mbanco_registros = (float)100*(banco_registros)/ref;
	
	printf("TOTALES: %d | CORTOS32 %d | CORTOS42 %d | CORTOS52 %d | BR: %d\n",ref, corto32, corto42, corto52, banco_registros);
	printf("MCORTOS32 %2.2f%% | MCORTOS42 %2.2f%% | MCORTOS52 %2.2f%% | MBR: %2.2f%%\n",mcorto32, mcorto42, mcorto52, mbanco_registros);
}

static void
reloj()
{
    if (carga_D)  etapa_Din = etapa_Bout;
    if (carga_A)  etapa_Ain = etapa_Dout;
    if (carga_M)  etapa_Min = etapa_Aout;
    if (carga_E)  etapa_Ein = etapa_Mout;
    ciclos++;
    /* chivato(); */
}

static void
ini_sim()
{
    /* devuelve nanosegundos */
    user0 = gethrvtime();
}

static void
fin_sim()
{
    /* devuelve nanosegundos */
    user1 = gethrvtime();

    /* tiempo en segundos,
       velocidad en miles de instrucciones por segundo */
    fprintf(stdout, "\nTiempo de simulación: %.3f sg (%.1f KIPS)\n\n",
	(float) (user1 - user0)/1e9, (float) instrucciones*1e6/(user1 - user0));
}


/******************************************************************************/
int main(int argc, char **argv, char **envp)
{

    char quedan_inst;

    if (argc == 2) depura = 1;

    ini_sim();

    ini_cpu();

    /* cargamos la primera instruccion en etapa_Bin  */
    quedan_inst = get_instr(&etapa_Bin);

    while (quedan_inst != -1)
    {
	/* etapa Escritura en BR */
	/* nada que simular en esta etapa */
	etapa_Eout = etapa_Ein;
	carga_E = 1;
	
	/* etapa Memoria: si no hay problemas la instruccion pasa a E */
	/* nada que simular en esta etapa */	
	etapa_Mout = etapa_Min;
	carga_M = 1;
	
	/* etapa ALU: si no hay problemas la instruccion pasa a M */
	/* nada que simular en esta etapa */	
	etapa_Aout = etapa_Ain;
	carga_A = 1;

	/* etapa Decode: deteccion de riesgos y lectura en BR */
	/* si no hay problemas la instruccion pasa a A */
	if (etapa_Ain.co == LOAD && (etapa_Ain.rd == etapa_Din.rs1 || etapa_Ain.rd == etapa_Din.rs2))
	{
	    etapa_Dout = inula;
	    craw++;
	    carga_D = 0;
	}
	else
	{
	    etapa_Dout = etapa_Din;
	    carga_D = 1;
	}

	/*************************************
	Introducimos la busqueda de cortos
	*************************************/
	
	//En el caso del rs1
	if (!(etapa_Ain.co == LOAD && (etapa_Ain.rd == etapa_Din.rs1))){
		if(etapa_Ain.rd == etapa_Din.rs1){
			corto32 += 1;
		}else if(etapa_Min.rd == etapa_Din.rs1){
			corto42 += 1;
		}else if(etapa_Ein.rd == etapa_Din.rs1){
			corto52 += 1;
		}else{
			banco_registros += 1;
		}
	}else{
		//El dato existente en rs1 es el esperado en rd asi que no hacemos nada
	}

	//En el caso del rs2
	if (!(etapa_Ain.co == LOAD && (etapa_Ain.rd == etapa_Din.rs2))){
		/* Los datos existentes en la etapa no son los esperados
		 * y tenemos que aplicar cortos
		*/
		if(etapa_Ain.rd == etapa_Din.rs2){
			corto32 += 1;
		}else if(etapa_Min.rd == etapa_Din.rs2){
			corto42 += 1;
		}else if(etapa_Ein.rd == etapa_Din.rs2){
			corto52 += 1;
		}else{
			banco_registros += 1;
		}
	}else{
		//El dato existente en rs1 es el esperado en rd asi que no hacemos nada		
	}


	/* etapa Busqueda: si no hay problemas la instruccion pasa a D */
	/* nada que simular en esta etapa */	
	etapa_Bout = etapa_Bin;
	carga_B = carga_D;

	if (carga_B)
	{
	    ccpu++;
	    quedan_inst = get_instr(&etapa_Bin);
	    if (quedan_inst != -1)
	    {
		instrucciones++;
		if (etapa_Bin.co == NOP)
		    nulas++;
		else
		{
		    validas++;
		    switch (etapa_Bin.co)
		    {
		    	case ARITM:
			    aritm++;
			    break;

		    	case LOAD:
			    loads++;
			    break;

		    	case STORE:
			    stores++;
			    break;

		    	case BRCON:
		    	case BRINC:
			    saltos++;
			    break;

		    	case FLOAT:
			    fp++;
			    break;
		    }
		}
	    }
	}
	reloj();
    }

    fin_cpu();

    fin_sim();
}
