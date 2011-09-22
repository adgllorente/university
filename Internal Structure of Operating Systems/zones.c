#include <string.h>
#include <stdlib.h>
#define MIBUF 1024

char buf[MIBUF];
char *s0="Entrada\n";
char *s2="Malloc\n";
char *s3="Free 1\n";
char *s4="Free 2\n";
char *s1="Salida\n";
int main(){
  void *ptr1;
  void *ptr2;
  write(2,s0,strlen(s0));
  read(0,buf,MIBUF);

  ptr1 = malloc(5000000);
  ptr2 = malloc(5000000);
  write(2,s2,strlen(s2));
  read(0,buf,MIBUF);

  free(ptr1);
  write(2,s3,strlen(s3));
  read(0,buf,MIBUF);

  free(ptr2);
  write(2,s4,strlen(s4));
  read(0,buf,MIBUF);

  write(2,s1,strlen(s1));
}