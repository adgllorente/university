#include <string.h>
#include <stdlib.h>
#define MIBUF 1024

char buf[MIBUF];
char *s0="Entrada\n";
char *s1="Salida\n";
int main(){
  write(2,s0,strlen(s0));
  read(0,buf,MIBUF);
  malloc(0x0001000);
  write(2,s1,strlen(s1));
  read(0,buf,MIBUF);
}