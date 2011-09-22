#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "trace.h"

#define	MAXLINE	256

extern int depura;

static char
*textco[8] = {"NOP  ",
	      "LOAD ",
	      "STORE",
	      "ARITM",
	      "BRCON",
	      "BRINC",
	      "FLOAT",
	      "OTROS"};

/* tabla de load y store OP=3 */
static char
tabla_op3[64] =    {1,1,1,1, 2,2,2,2,	/* normal */
		    0,1,1,0, 0,1,0,1,
		    1,1,1,1, 2,2,2,2,	/* alternate space */
		    0,1,1,0, 0,1,0,1,
		    5,5,0,5, 5,5,5,5,	/* FPU */
		    0,0,0,0, 0,0,0,0,
		    6,6,0,6, 6,6,6,6,	/* COPRO */
		    0,0,0,0, 0,0,0,0
};

/* tabla de operandos para OP=2 */
static char
tabla_op2[64]=	   {0,0,0,0, 0,0,0,0,
		    0,4,0,0, 0,4,0,0,
		    0,0,0,0, 0,0,0,0,	/* 0:fuentes y destino	*/
		    0,4,0,0, 0,4,0,0,	/* 1:solo fuentes	*/
		    0,0,0,0, 0,0,0,0,	/* 2:solo destino	*/
		    2,4,4,4, 4,4,4,4,	/* 3:float no CMPF	*/
		    1,4,4,4, 3,5,4,4,	/* 4:no valida, priv. o copro*/
		    0,1,1,1, 0,0,4,4	/* 5:float CMPF		*/
};

static void
printir(IREG *ir, FILE *fp)
{
    fprintf(fp, "%5s", textco[(int) ir->co]);
    switch (ir->co)
    {
	case ARITM:
		IMPRIME(ir->rs1, ',');
		IMPRIME(ir->rs2, ',');
		IMPRIME(ir->rd , ' ');
		break;

	case LOAD:
		fprintf(fp,"(%2d,", ir->rs1);
		IMPRIME(ir->rs2, ')');
		fprintf(fp,"%2d ", ir->rd);
		break;

	case STORE:
		fprintf(fp,"%2d ",  ir->rd);
		fprintf(fp,"(%2d,", ir->rs1);
		IMPRIME(ir->rs2, ')');
		break;

/*	case BRINC: 
	case BRCON:
		if(ir->rd>=0)fprintf(fp," %2d,",ir->rd);
		else fprintf(fp," --,");
		if(ir->rs1>=0)fprintf(fp,"%2d,",ir->rs1);
		else fprintf(fp,"--,");
		if(ir->rs2>=0)fprintf(fp,"%2d  ",ir->rs2);
		else fprintf(fp,"--  ");
		break; */
	case BRINC: 
	case BRCON: 
	default:
		fprintf(fp,"          ");
		break;
    }
    /* fprintf(fp,"\n"); */
}


static void
decodifica(const char *line, IREG *ir)
{
    unsigned int pc, inst, ea;
    unsigned int auxop3, auxopf;
    int n;
    char an, rd = -1, rs1 = -1, rs2 = -1, co, nreg, taken;

    if (depura) fprintf(stdout, "%s", line);
    n = sscanf(line, "%x %x %x\n", &pc, &inst, &ea);
    /* fprintf(stdout, "pc: %x, inst: %x ", pc, inst); */

    ir->pc = pc;
    ir->ea = ea;
    /* ir->an = t->tr_annulled; */
    ir->iw = inst;
    ir->rd = getRD(ir->iw);
    ir->rs1 = getRS1(ir->iw);
    /* ir->taken = t->tr_taken; */

    if (getI(inst) != 0)
    {
	ir->nreg = 1;
	ir->rs2 =- 1;
    }
    else
    {
	ir->nreg = 2;
	ir->rs2 = getRS2(inst);
    }

    ir->co = ARITM;

    switch (getOP(inst))
    {
	case 1:		/* CALL */
	    ir->rd = ir->rs1 = ir->rs2 = -1;
	    ir->co = BRINC;
	    ir->taken = 1;
	    break;

	case 0:
	    if (getOP2(inst) != 4)
	    {	/* SALTO */
		ir->rd = -1;
		if (getCOND(inst) == 8)	ir->co = BRINC;
		else				ir->co = BRCON;
	    }
	    else
	    {	/* OP2 == 4 => SETHI */ 
		if (ir->rd == 0)
		    ir->co = NOP;
		else
		    ir->co = ARITM;  /* SETHI */

		ir->rs1 = ir->rs2 = -1;             
		if (getOP2(inst) == 6)
		    ir->co = BRCON;  /* JMPF, salto P.F. */
	    }
	    break;		

	case 2:
	    auxop3 = getOP3(inst);
	    switch (auxop3)
	    {
		case 0x38:
		    ir->co = BRINC;
		    ir->taken = 1;
		    ir->rd = -1;
		    break;

		case 0x3c:	/* SAVE */
		case 0x3d:	/* RESTORE */
		    ir->co = ARITM;
		    break;
	    }

	    switch(tabla_op2[auxop3])
	    {
		case 0:
		    break;

		case 1:
		    ir->rd = -1;
		    break;

		case 2:
		    ir->rs1 = ir->rs2 = -1;
		    break;

		case 3:
		    ir->co = FLOAT;
		    ir->rs1 += 32;
		    if (ir->rs2 != -1) ir->rs2 += 32;
		    if (ir->rd != -1)  ir->rd += 32;
		    break;

		case 5:
		    ir->co = FLOAT; 	/* CMPF */
		    ir->rs1 += 32;
		    if (ir->rs2 >= 0) ir->rs2 += 32;
		    break;

		default: ;
	    }
	    break;

	case 3:		/* LOAD, STORE instructions */
	    ir->co = tabla_op3[getOP3(inst)];
	    if (getOP3(inst)>31) ir->rd += 32; /* float */
	    break;

	default: ;
    }
    
    /* fprintf(stdout, "%x ", pc);
    printir(ir, stdout);
    
    fprintf(stdout, " (co: %02d", ir->co);
    fprintf(stdout, " rs1: %02d", ir->rs1);
    fprintf(stdout, " rs2: %02d", ir->rs2);
    fprintf(stdout, " rd: %02d", ir->rd);
    fprintf(stdout, " ea: %08x)\n\n", ir->ea); */
}

int
get_instr(IREG *ir)
{
  /* char buf[256]; */
  char linea[MAXLINE], *otra;

  otra = fgets(linea, MAXLINE, stdin);	   /* lectura de primera línea de la traza */
  if (otra != NULL)
  {
    decodifica(linea, ir);
    /* if (spix_sparc_dis32(buf, 256, spix_sparc_iop(SPIX_SPARC_V9, &atr[i].tr_i), &atr[i].tr_i, ir.pc) < 0) 
	printf("%llx %-25s\n",(long long) ir.pc, "???");
    else 
	printf("%llx %-25s\n",(long long) ir.pc, buf); */
    return(0);
  }
  else
  {
    return(-1);
  }
}
