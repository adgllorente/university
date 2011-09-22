#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>

typedef struct {
  unsigned long long pc, ea;
  unsigned long iw;
  char an, rd, rs1, rs2, co, nreg, taken;
} IREG;

#define NOP	0       
#define LOAD	1      
#define STORE	2      
#define ARITM	3     
#define BRCON	4     /*  salto condicional  */
#define BRINC	5     /* salto incondicional */     
#define FLOAT	6
#define OTROS	7

typedef unsigned int uint32;
#define getI(x)		(((((uint32)(x)) << 18)) >> 31)
#define getOP(x)	(((((uint32)(x)))) >> 30)
#define getOP2(x)	(((((uint32)(x)) <<  7)) >> 29)
#define getOP3(x)	(((((uint32)(x)) <<  7)) >> 26)
#define getRD(x)	(((((uint32)(x)) <<  2)) >> 27)
#define getRS1(x)	(((((uint32)(x)) << 13)) >> 27)
#define getRS2(x)	(((((uint32)(x)) << 27)) >> 27)
#define getCOND(x)	(((((uint32)(x)) <<  3)) >> 28)

#define IMPRIME(reg, caract)			\
{						\
     if ((reg) >= 0)				\
	fprintf(fp," %2d%c", (reg), (caract));	\
    else					\
	fprintf(fp, " --%c", (caract));		\
}

#endif
