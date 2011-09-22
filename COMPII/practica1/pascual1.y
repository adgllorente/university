%{
/**********************************************************************
 * fichero: pascual.y
 *          Analizador sint'actico de Pascual
 *          2011-03-21
 *             jfabra - Cambios en la gram'atica
 **********************************************************************/

/**********************************************************************
 * Nombre: Adrián Gómez Llorente
 * NIP: 605731
 * Asignatura: Compiladores 2
 * Año: 2011
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errores.h"
#include "listas.h"
#include "tabla.h"

TABLA_SIMBOLOS tabsim;
int nivel;
extern lineno;
int muestra;
FILE *fxml;
int xml;
int nErrores;
int tabs;
int dar_warnings;

void abrir_bloque();
void cerrar_bloque();
void ptabs(int i);

%}

%token tPROGRAMA tACCION 
%token <constante> tCONSTENTERA 
%token <car> tCONSTCHAR
%token tCONSTCAD tTRUE tFALSE tENTACAR tCARAENT tBOOLEANO
%token tIDENTIFICADOR tENTERO tCARACTER
%token tESCRIBIR tLEER tOPAS tPRINCIPIO tFIN
%token tAND tOR tNOT 
%token tMQ tFMQ
%token tMEI tMAI tNI tMOD tDIV
%token tSI tENT tSI_NO tFSI
%token tVAL tREF
%token tVECTOR tDE
%left '+' '-'
%left '*' '/' tDIV tMOD
%left tNOT
%nonassoc MENOSU

%union {
  int constante;
  char *cadena;
  char car;
  SIMBOLO *simbolo;
  LISTA lista;
  CLASE_PARAMETRO clase_parametro;
  
        struct{
                int extremo;
                TIPO_VARIABLE tipo;
        }indice_vector;
  
        struct{
                TIPO_VARIABLE tipo_var;
                SIMBOLO *simbolo;
                int valor;
				int es_componente;
				int tiene_valor;
        }expresion;
  
        struct{
                TIPO_VARIABLE tipo_variable; //Tipo de variable o tipo de las variables del Vector
                int es_vector; //0: No | 1: SI
                int extremo1, extremo2; //Extremos de los vectores izquierda y derecha respectivamente
                int tipo_extremo; // 1: ENTERO | 2: BOOLEANO | 3: CARACTER
        }control_tipo;
  
  //Estructura de tIDENTIFICADOR
  struct{
        char *nombre;
        
        SIMBOLO *simbolo;
  }identificador;
  
  //Estructura operador_multiplicativo operador_aditivo operador_relacional
        struct{
                TIPO_VARIABLE tipo;
                char *op;
        }operador;
        
        TIPO_VARIABLE tipo;
}

%type <identificador> tIDENTIFICADOR identificadores
%type <control_tipo> tipo_variables tipo_variable_vector
%type <indice_vector> indice_vector
%type <lista> identificadores_parametros declaracion_parametro parametros
%type <lista> parametros_formales lista_parametros
%type <lista> lista_expresiones argumentos
%type <expresion> factor expresion termino expresion_simple
%type <operador> operador_multiplicativo operador_aditivo operador_relacional

%start programa
%%

programa: 
    tPROGRAMA tIDENTIFICADOR ';'
    {
      nivel = 0;
          tabs = 0;
      inicializar_tabla (tabsim);
          
          //Insertamos el programa
          introducir_programa(tabsim, $2.nombre, lineno);
          if(xml) fprintf(fxml, "<Programa name=\"%s\">\n", $2.nombre);
          tabs++;
    }
    declaracion_variables
        {
                if(xml) ptabs(tabs);
                if(xml) fprintf(fxml, "<declaracion_acciones>\n");
                tabs++;
        }
    declaracion_acciones
        {
                tabs--;
                if(xml) ptabs(tabs);
                if(xml) fprintf(fxml, "</declaracion_acciones>\n");
        }
    bloque_instrucciones
    {
        if(muestra) mostrar_tabla(tabsim);
      eliminar_variables (tabsim, nivel);
      eliminar_acciones (tabsim, nivel);
      --nivel;
          if(xml) fprintf(fxml, "</Programa>\n");
    }
;

declaracion_variables:
|    
        {
                if(xml) ptabs(tabs);
                if(xml) fprintf(fxml, "<declaracion_variables>\n");
                tabs++;
        } lista_declaraciones ';'
        {
                tabs--;
                if(xml) ptabs(tabs);
                if(xml) fprintf(fxml, "</declaracion_variables>\n");
        }
;

lista_declaraciones:
     lista_declaraciones ';' declaracion
|    declaracion
;

//GRAMATICA VECTORES
declaracion:
     tipo_variables identificadores 
         | tipo_variable_vector identificadores
;


//GRAMATICA VECTORES
indice_vector:
        signo tCONSTENTERA
        {
                if($<constante>1 == 0)
                        $<indice_vector>$.extremo = -$<constante>2;
                else
                        $<indice_vector>$.extremo = $<constante>2;
                $<indice_vector>$.tipo = ENTERO;
        }
        | tTRUE 
        {
                $<indice_vector>$.extremo = 1;
                $<indice_vector>$.tipo = BOOLEANO;
        }
        | tFALSE 
        {
                $<indice_vector>$.extremo = 0;
                $<indice_vector>$.tipo = BOOLEANO;
        }
        | tCONSTCHAR 
        {
                $<indice_vector>$.extremo = (int)$<constante>1;
                $<indice_vector>$.tipo = CHAR;
        }
        ;
        
//GRAMATICA VECTORES    
signo:
        '-' {$<constante>$ = 0; }
        | /*VACIO*/ {$<constante>$ = 1;} 
        ;


//Subimos los tipos de las variables
tipo_variables:
     tENTERO 
         {
                $<control_tipo>$.tipo_variable = ENTERO;
                $<control_tipo>$.es_vector = 0;
        }
|    tBOOLEANO 
        {
                $<control_tipo>$.tipo_variable = BOOLEANO;
                $<control_tipo>$.es_vector = 0;
        }
|   tCARACTER 
        {
                $<control_tipo>$.tipo_variable = CHAR;
                $<control_tipo>$.es_vector = 0;
        }
;

//GRAMATICA VECTORES: Añadido el tipo
tipo_variable_vector:
        tVECTOR '[' indice_vector '.''.' indice_vector ']' tDE tipo_variables
        {
                if($<indice_vector>3.tipo != $<indice_vector>6.tipo){
                        error_semantico("Los índices son de distinto tipo");
                }
                if($<indice_vector>3.extremo >= $<indice_vector>6.extremo){
                        error_semantico("Los índices del vector deben declararse de menor a mayor");
                }
                if($<indice_vector>3.tipo == 3){
                        if($<indice_vector>3.extremo < 32 || $<indice_vector>6.extremo > 126){
                                error_semantico("Los índices del vector deben ser un caracter imprimible ASCII");
                        }
                }/*if($<indice_vector>3.tipo != $<control_tipo>9.tipo_variable){
                        error_semantico("Los índices y el tipo de las variables no coinciden");
                }*/
                $<control_tipo>$.es_vector = 1;
                $<control_tipo>$.extremo1 = $<indice_vector>3.extremo;
                $<control_tipo>$.extremo2 = $<indice_vector>6.extremo;
                $<control_tipo>$.tipo_extremo = $<indice_vector>3.tipo;
                $<control_tipo>$.tipo_variable = $<control_tipo>9.tipo_variable;
        }





        ;

identificadores:
     tIDENTIFICADOR 
         { 
                //INSERCIÓN DE LA VARIABLE
                
                if($1.simbolo == NULL || $1.simbolo->nivel != nivel){ //El símbolo no existe o el nivel es distinto
                        if($<control_tipo>0.es_vector == 0){
                                SIMBOLO *s = introducir_variable(tabsim, $1.nombre, $<control_tipo>0.tipo_variable, nivel, 0);
                                s->es_vector = 0;
                                s->asignado = 0;
                                if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<var nombre=\"%s\" tipo=\"%s\">\n", $1.nombre, $<control_tipo>0.tipo_variable == 1 ? "entero" : $<control_tipo>0.tipo_variable == 2 ? "booleano" : "caracter");
                        }else{ //Se trata de un vector
                                SIMBOLO *s = introducir_variable_vector(tabsim, $1.nombre, $<control_tipo>0.tipo_variable, nivel, 0, $<control_tipo>0.extremo1, $<control_tipo>0.extremo2, $<control_tipo>0.tipo_extremo);
                                s->es_vector = 1;
                                s->asignado = 1;
                                //s->componenteVector = 0;
                                if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<var nombre=\"%s\" tipo=\"vector\" valores=\"%s\" inf=\"%d\" sup=\"%d\">\n", $1.nombre, $<control_tipo>0.tipo_variable == 1 ? "entero" : $<control_tipo>0.tipo_variable == 2 ? "booleano" : "caracter", $<control_tipo>0.extremo1, $<control_tipo>0.extremo2);
                        }
                }
                else{
                        error_semantico("El simbolo ya se ha declarado en este nivel");
                }
         }
|    identificadores ',' tIDENTIFICADOR
        { 
                //INSERCIÓN DE LA VARIABLE
                if($3.simbolo == NULL || $3.simbolo->nivel != nivel){ //El símbolo no existe o el nivel es distinto
                        if($<control_tipo>0.es_vector == 0){
                                SIMBOLO *s = introducir_variable(tabsim, $3.nombre, $<control_tipo>0.tipo_variable, nivel, 0);
                                s->es_vector = 0;
                                s->asignado = 0;
                                if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<var nombre=\"%s\" tipo=\"%s\">\n", $3.nombre, $<control_tipo>0.tipo_variable == 1 ? "entero" : $<control_tipo>0.tipo_variable == 2 ? "booleano" : "caracter");
                        }else{ //Se trata de un vector
                                SIMBOLO *s = introducir_variable_vector(tabsim, $3.nombre, $<control_tipo>0.tipo_variable, nivel, 0, $<control_tipo>0.extremo1, $<control_tipo>0.extremo2, $<control_tipo>0.tipo_extremo);
                                s->es_vector = 1;
                                s->asignado = 1;
                                //s->componenteVector = 0;
                                if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<var nombre=\"%s\" tipo=\"vector\" valores=\"%s\" inf=\"%d\" sup=\"%d\">\n", $3.nombre, $<control_tipo>0.tipo_variable == 1 ? "entero" : $<control_tipo>0.tipo_variable == 2 ? "booleano" : "caracter", $<control_tipo>0.extremo1, $<control_tipo>0.extremo2);
                        }
                }
                else{
                        error_semantico("El simbolo ya se ha declarado en este nivel");
                }
        }
;

//Corregido error en declaracion_acciones
declaracion_acciones:
        declaracion_acciones declaracion_accion
        | /*vacio*/
        ;

declaracion_accion:
     cabecera_accion ';'
     declaracion_variables
     declaracion_acciones     
     bloque_instrucciones 
         //Disminuímos el nivel
         {
                cerrar_bloque();
                tabs--;
                if(xml) ptabs(tabs);
                if(xml) fprintf(fxml, "</accion>\n");
         }
;

//Inserción de acción
cabecera_accion:
     tACCION tIDENTIFICADOR 
         {
                if($2.simbolo == NULL){
                        if(($2.simbolo = introducir_accion(tabsim, $2.nombre, nivel, 0)) == NULL){
                                error_semantico("El identificador de la acción está duplicado");
                        }else{
                                if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<accion nombre=\"%s\">\n", $2.nombre);
                                tabs++;
                        }       
                }else{
                        error_semantico("El identificador de la acción está duplicado");
                }
                abrir_bloque();
         }
         /*
          * TODO: Añadir los parámetros. Podemos usar listas o la propia pila del compilador.
          * también tenemos que saber cuántos parámetros tiene una acción aunque en realidad
          * esta información está en la tabla así que podemos comprobarla allá. DECIDIR.
         */
     parametros_formales
         {
                if($2.simbolo != NULL){
                        $2.simbolo->parametros = $4;
                }
         }
;

parametros_formales:
        {
                crear_vacia(&$$);
        }
        |    '(' lista_parametros ')'
        {
                $$ = $2;
        }
;

//Revocada la correccion
lista_parametros:
        lista_parametros ';' parametros
        {
                concatenar(&$1, $3);
                $$ = $1;
        }
        | parametros
        {
                $$ = $1;
        }
        | /*VACIO*/
        {
                crear_vacia(&$$);
        }
        ;

//GRAMATICA PARAMETROS: Creamos la declaracion_parametro porque los parámetros no son
//como las declaraciones normales.
parametros:
     clase_parametros declaracion_parametro
         {
                $$ = $2;
         }
;

declaracion_parametro:
        tipo_variables identificadores_parametros
        {
                //Subimos la lista
                $$ = $2;
        }
        | tVECTOR tIDENTIFICADOR '[' indice_vector ']'
        {
        
        }
        //TODO: Añadir el parámetro de tipo VECTOR. Probablemente SOBRE.
        ;

//GRAMATICA PARAMETROS: Añadimos identificadores_parametros para diferenciarlo de la
// producción identificadores normales.
identificadores_parametros:
        tIDENTIFICADOR
        {
                //Vamos a crear una lista para controlar los parámetros
                crear_vacia(&$$);
                if($1.simbolo == NULL || $1.simbolo->nivel != nivel){
                        SIMBOLO *p = introducir_parametro(tabsim, $1.nombre, $<control_tipo>0.tipo_variable, $<clase_parametro>-1, nivel, 0);
                        p->es_vector = 0;
                        if(xml) ptabs(tabs);
                        if(xml) fprintf(fxml, "<parametro nombre=\"%s\" tipo=\"%s\" paso=\"%s\" />\n", $1.nombre, $<control_tipo>0.tipo_variable == ENTERO ? "entero" : $<control_tipo>0.tipo_variable == BOOLEANO ? "booleano" : "caracter", $<clase_parametro>-1 == VAL ? "val" : "ref");
                        
                        //Lo añadimos a la lista
                        anadir_derecha(p, &$$);
                }else{
                        error_semantico("El nombre del parámetro está duplicado");
                        if($1.simbolo->es_vector){
                                error_semantico("No se permite el paso de un vector como parámetro");
                        }else{
                                SIMBOLO *p = introducir_parametro(tabsim, $1.nombre, $<control_tipo>0.tipo_variable, $<clase_parametro>-1, nivel, 0);
                                p->es_vector = 0;
                                if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<parametro nombre=\"%s\" tipo=\"%s\" paso=\"%s\" />\n", $1.nombre, $<control_tipo>0.tipo_variable == ENTERO ? "entero" : $<control_tipo>0.tipo_variable == BOOLEANO ? "booleano" : "caracter", $<clase_parametro>-1 == VAL ? "val" : "ref");
                                anadir_derecha(p, &$$);
                        }
                }
        }
        | identificadores_parametros ',' tIDENTIFICADOR
        {
                //Parecido a la versión de un único identificador
                if($3.simbolo == NULL){
                        SIMBOLO *p = introducir_parametro(tabsim, $3.nombre, $<control_tipo>0.tipo_variable, $<clase_parametro>-1, nivel, 0);
                        if(xml) ptabs(tabs);
                        if(xml) fprintf(fxml, "<parametro nombre=\"%s\" tipo=\"%s\" paso=\"%s\" />\n", $3.nombre, $<control_tipo>0.tipo_variable == ENTERO ? "entero" : $<control_tipo>0.tipo_variable == BOOLEANO ? "booleano" : "caracter", $<clase_parametro>-1 == VAL ? "val" : "ref");
                        
                        //Lo añadimos a la lista
                        anadir_derecha(p, &$1);
                }else{
                        //El símbolo existe así que comprobamos el tipo
                        error_semantico("El nombre del parámetro está duplicado");
                        if($3.simbolo->es_vector){
                                error_semantico("No se permite el paso de un vector como parámetro");
                        }else{
                                SIMBOLO *p = introducir_parametro(tabsim, $3.nombre, $<control_tipo>0.tipo_variable, $<clase_parametro>-1, nivel, 0);
                                if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<parametro nombre=\"%s\" tipo=\"%s\" paso=\"%s\" />\n", $3.nombre, $<control_tipo>0.tipo_variable == ENTERO ? "entero" : $<control_tipo>0.tipo_variable == BOOLEANO ? "booleano" : "caracter", $<clase_parametro>-1 == VAL ? "val" : "ref");
                                anadir_derecha(p, &$1);
                        }
                }
                //Subimos la lista
                $$=$1;
        }
        ;
        
clase_parametros:
     tVAL
         {
                $<clase_parametro>$ = VAL;
         }
|    tREF
        {
                $<clase_parametro>$ = REF;
        }
;

bloque_instrucciones:
     tPRINCIPIO lista_instrucciones tFIN 
;

//Corregido error en lista_instrucciones. Errores S/R
lista_instrucciones:
        lista_instrucciones instruccion
        | /*vacio*/
        ;

//Añadida la asignación_vector aquí.
instruccion:
     leer
|    escribir
|    asignacion
|        asignacion_vector
|    seleccion
|    mientras_que
|    invocacion_accion
;

leer:
     tLEER 
     '(' lista_asignables ')' ';'
;

lista_asignables:
     tIDENTIFICADOR
         {
                if($1.simbolo == NULL){
                        error_semantico("El identificador no está declarado");
                }else if($1.simbolo->nivel > nivel){
                        error_semantico("El identificador no es accesible");
                }else if($1.simbolo->tipo != PARAMETRO && $1.simbolo->tipo != VARIABLE){
                        error_semantico("El identificador no es un parámetro o una variable");
                }else if($1.simbolo->tipo == PARAMETRO && $1.simbolo->parametro == VAL){
                        error_semantico("No se puede asignara un parámetro por VALOR");
                }
         }
|    lista_asignables ',' tIDENTIFICADOR
        {
                if($3.simbolo == NULL){
                        error_semantico("El identificador no está declarado");
                }else if($3.simbolo->nivel > nivel){
                        error_semantico("El identificador no es accesible");
                }else if($3.simbolo->tipo != PARAMETRO && $3.simbolo->tipo != VARIABLE){
                        error_semantico("El identificador no es un parámetro o una variable");
                }else if($3.simbolo->tipo == PARAMETRO && $3.simbolo->parametro == VAL){
                        error_semantico("No se puede asignara un parámetro por VALOR");
                }
        }
;        
;        
        
escribir:
     tESCRIBIR 
     '(' lista_escribibles ')' ';'
;

lista_escribibles:
    lista_escribibles ',' expresion
        {
                if($3.tipo_var == BOOLEANO){
                        error_semantico("No se puede escribir un BOOLEANO");
                }
        }
|   expresion
        {
                if($1.tipo_var == BOOLEANO){
                        error_semantico("No se puede escribir un BOOLEANO");
                }
        }
;


//GRAMÁTICA VECTORES
//Añadida la comprobación de asignación de expresiones
//Muevo la asignación_vector a la producción previa (instrucción). Es inutil ponerla aquí.
asignacion:
     tIDENTIFICADOR tOPAS expresion ';'
         {
                if($1.simbolo == NULL){
                        error_semantico("El identificador no está declarado");
                }else if($1.simbolo->nivel > nivel){
                        error_semantico("El identificador no es accesible");
                }else if($1.simbolo->tipo != VARIABLE && $1.simbolo->tipo != PARAMETRO){
                        error_semantico("El identificador no es una variable o un parámetro");
                }else if($1.simbolo->tipo == PARAMETRO && $1.simbolo->parametro == VAL){
                        error_semantico("No se puede asignar un valor a un parámetro pasado por VALOR");
                }else if($1.simbolo->variable != $3.tipo_var){
                        error_semantico("Los tipos asignados no coinciden");
                }else if($3.simbolo != NULL && $3.simbolo->es_vector == 1 && $1.simbolo->es_vector == 0){
					error_semantico("No se puede asignar un vector a un identificador");
				}else if($3.tipo_var == CADENA){ 
                        error_semantico("El tipo cadena no está permitido");
                }else if($1.simbolo->es_vector == 1){//Si el símbolo es vector la asignación del vector deberá ser completa
                        if($3.simbolo == NULL){
                                error_semantico("El identificador asignado no es válido");
                        }else if($1.simbolo->es_vector != $3.simbolo->es_vector){ 
                                error_semantico("Los identificadores asignados no son vectores");
                        }else if($3.simbolo == NULL){
                                error_semantico("La asignación del vector debe ser completa");
                        }else{
                                //Comprobamos el tamaño de los vectores asignados.
                                //Tiene que ser el mismo
                                int size1 = $1.simbolo->extremo2 - $1.simbolo->extremo1;
                                int size2 = $3.simbolo->extremo2 - $3.simbolo->extremo1;
                                if(size1 != size2){
                                        error_semantico("El tamaño de los vectores es distinto");
                                }
                        }
                }else{
                        $1.simbolo->valor = $3.valor;
                        $1.simbolo->asignado = 1;
                }
         }
;

//GRAMÁTICA VECTORES
//Añadida la comprobación de tipos en la asignación de vectores
asignacion_vector:
        tIDENTIFICADOR '[' expresion ']' tOPAS expresion ';'
        {
                if($1.simbolo == NULL){
                        error_semantico("El símbolo NO está declarado");
                }else if(!$1.simbolo->es_vector){
                        error_semantico("El tipo del símbolo NO es un vector");
                }else if($1.simbolo->nivel > nivel){
                        error_semantico("La símbolo no es accesible");
                }else if(!ES_VARIABLE(*$1.simbolo)){
                        error_semantico("El identificador debe ser una variable");
                }else if($6.tipo_var == CADENA){
                        error_semantico("El tipo CADENA no es válido");
                }else if($1.simbolo->variable != $6.tipo_var){
                        error_semantico("Los tipos asignados deben ser los mismos");
                }else if($1.simbolo->tipo_extremo != $3.tipo_var){
                        error_semantico("El tipo del índice no es válido");
                }else if($3.valor < $1.simbolo->extremo1 || $3.valor > $1.simbolo->extremo2){
                        if($3.tiene_valor == 1){
							error_semantico("Índice fuera de rango");
						}else{
							warning("El índice podría estar fuera de rango");
						}
                }
        }
        | tIDENTIFICADOR '[' expresion '.''.' expresion ']' tOPAS tIDENTIFICADOR '[' expresion '.''.' expresion ']' ';'
        {
                if($1.simbolo == NULL){ //Comprobación de tipos del 1º vector
                        error_semantico("El símbolo de la izquierda NO está declarado");
                }else if(!$1.simbolo->es_vector){
                        error_semantico("El tipo del símbolo de la izquierda NO es un vector");
                }else if($1.simbolo->nivel > nivel){
                        error_semantico("La símbolo de la izquierda no es accesible");
                }else if(!ES_VARIABLE(*$1.simbolo)){
                        error_semantico("El identificador de la izquierda debe ser una variable");
                }else if($6.tipo_var == CADENA){
                        error_semantico("El tipo CADENA no es válido");
                }else if($1.simbolo->tipo_extremo != $3.tipo_var || $1.simbolo->tipo_extremo != $6.tipo_var){
                        error_semantico("Los tipos de los índices y el vector de la izda deben ser los mismos");
                }if($9.simbolo == NULL){ //Comprobación de tipos del 2º vector
                        error_semantico("El símbolo de la derecha NO está declarado");
                }else if(!$9.simbolo->es_vector){
                        error_semantico("El tipo del símbolo de la derecha NO es un vector");
                }else if($9.simbolo->nivel > nivel){
                        error_semantico("La símbolo la derecha NO es accesible");
                }else if(!ES_VARIABLE(*$9.simbolo)){
                        error_semantico("El identificador la derecha debe ser una variable");
                }else if($6.tipo_var == CADENA){
                        error_semantico("El tipo CADENA no es válido");
                }else if($9.simbolo->tipo_extremo != $11.tipo_var || $9.simbolo->tipo_extremo != $14.tipo_var){
                        error_semantico("Los tipos de los índices y vector de la derecha deben ser los mismos");
                }else if($1.simbolo->variable != $9.simbolo->variable){ //Comprobando la asignación
                        error_semantico("Los tipos de los vectores asignados deben ser iguales");
                }else if($3.valor < $1.simbolo->extremo1 || $6.valor > $1.simbolo->extremo2){ //Comprobamos que accedemos a un conjunto correcto del vector
                        if($3.tiene_valor == 1 && $6.tiene_valor == 1){
							error_semantico("Índice fuera de rango");
						}else{
							warning("El índice podría estar fuera de rango");
						}
                }else if($11.valor < $9.simbolo->extremo1 || $14.valor > $9.simbolo->extremo2){ //Comprobamos que accedemos a un conjunto correcto del vector
                        if($11.tiene_valor == 1 && $14.tiene_valor == 1){
							error_semantico("Índice fuera de rango");
						}else{
							warning("El índice podría estar fuera de rango");
						}
                }else{
                        //Comprobando que el tamaño de los vectores asignados es el mismo
                        int size1 = $6.valor - $3.valor;
                        int size2 = $14.valor - $11.valor;
                        if(size1 != size2){
                                if($3.tiene_valor == 1 && $6.tiene_valor == 1 && $11.tiene_valor == 1 && $14.tiene_valor == 1){
									error_semantico("Los rangos asignados no tienen el mismo tamaño");
								}else{
									warning("Los rangos asignados podrían no tener el mismo tamaño");
								}
                        }
                }
        }
        ;
        
//Añadida la comprobación de tipo de la condición
mientras_que:
    tMQ 
    expresion 
        {
                if($2.tipo_var != BOOLEANO){
                        error_semantico("El tipo de la condición debe ser BOOLEANO");
                }
        }
    lista_instrucciones 
    tFMQ
;

//Añadida la comprobación de tipo de la condición   
seleccion:
    tSI 
    expresion
        {
                if($2.tipo_var != BOOLEANO){
                        error_semantico("El tipo de la condición debe ser BOOLEANO");
                }
        }
    tENT 
    lista_instrucciones 
    resto_seleccion
    tFSI
;

resto_seleccion:
|
    tSI_NO 
    lista_instrucciones
;

//Añado la comprobación de la acción
invocacion_accion:
     tIDENTIFICADOR argumentos ';'
         {
                if($1.simbolo == NULL){
                        error_semantico("La acción NO está declarada");
                }else if($1.simbolo->tipo != ACCION){
                        error_semantico("El símbolo no es una ACCIÓN");
                }else if($1.simbolo->nivel > nivel){
                        error_semantico("La acción no es accesible");
                }else{
                        //Comprobamos los parámetros de invocación
                        LISTA args_simbolo;
                        LISTA args;
                        args_simbolo = $1.simbolo->parametros;
                        args = $2;
                        
                        if(longitud_lista(args_simbolo) != longitud_lista(args)){
                                error_semantico("El número de argumentos no es correcto");
                        }else{
                                
                                SIMBOLO *param;
                                SIMBOLO *arg;
                                int i = 1;
                                while(longitud_lista(args_simbolo) >= i){
                                        
                                        //Obtenemos los símbolos
                                        arg = observar(args_simbolo, i);
                                        param = observar(args, i);
                                        
                                        if(param != NULL){ //Es un símbolo
												if(param == (void *)-1 || param == (void *)-2 || param == (void *)-3){
													if(param == (void *)-1 && arg->variable != ENTERO){
														error_semantico("El tipo del parámetro no es correcto");
													}else if(param == (void *)-2 && arg->variable != BOOLEANO){
														error_semantico("El tipo del parámetro no es correcto");
													}else if(param == (void *)-3 && arg->variable != CHAR){
														error_semantico("El tipo del parámetro no es correcto");
													}
												}else if(arg->variable != param->variable){
                                                        error_semantico("El tipo del parámetro no es correcto");
                                                }else if(param->es_vector){
                                                        error_semantico("No se permite el paso de un vector entero");
                                                }
                                        }else{ //Es una expresión
                                                if(arg->parametro == REF){
                                                        error_semantico("Se esperaba un parámetro por REFERENCIA");
                                                }
                                        }
                                        i++;
                                }
                        }
                }
         }
|    tIDENTIFICADOR
        {
                if($1.simbolo == NULL){
                        error_semantico("La acción NO está declarada");
                }else if($1.simbolo->tipo != ACCION){
                        error_semantico("El símbolo no es una ACCIÓN");
                }else if($1.simbolo->nivel > nivel){
                        error_semantico("La acción no es accesible");
                }else if(longitud_lista($1.simbolo->parametros) > 0){
					error_semantico("El número de parámetros no es correcto");
				}
        }
     ';'
;
                            
argumentos:
    '(' lista_expresiones ')'
        {
                $$ = $2;
        }
;

lista_expresiones:
     lista_expresiones ',' expresion
         {
			if($3.es_componente == 1){
				if($3.tipo_var == ENTERO){
					anadir_derecha((void *)-1, &$1);
				}else if($3.tipo_var == BOOLEANO){
					anadir_derecha((void *)-2, &$1);
				}else if($3.tipo_var == CHAR){
					anadir_derecha((void *)-3, &$1);
				}
				//Perdón porque no es la mejor solución
			}else{
                anadir_derecha($3.simbolo, &$1);
            }    
			$$ = $1;
         }
|    expresion
        {
                crear_vacia(&$$);
				if($1.es_componente == 1){
					if($1.tipo_var == ENTERO){
						anadir_derecha((void *)-1, &$$);
					}else if($1.tipo_var == BOOLEANO){
						anadir_derecha((void *)-2, &$$);
					}else if($1.tipo_var == CHAR){
						anadir_derecha((void *)-3, &$$);
					}
					//Perdón porque no es la mejor solución
				}else{
					anadir_derecha($1.simbolo, &$$);
				} 
                
        }
;

expresion:
     expresion_simple
         {
                $$.tipo_var = $1.tipo_var;
                $$.simbolo = $1.simbolo;
                $$.valor = $1.valor;
				$$.tiene_valor = $1.tiene_valor;
         }
|    expresion operador_relacional expresion_simple
        { //Tenemos que controlar los tipos. Similar a la acción operador_multiplicativo
                if($1.tipo_var != $3.tipo_var){ //Tipos distintos
                        error_semantico("Los tipos no son compatibles");
                }else if($1.tipo_var == CADENA){
                        error_semantico("Tipo CADENA no permitido");
                }else if($1.tipo_var == BOOLEANO && $<operador>2.tipo != BOOLEANO){
                        error_semantico("Operación no permitida con tipo BOOLEANO");
                }else{
                        $$.simbolo = NULL;
						$$.tipo_var = BOOLEANO;
                        
						if($1.tiene_valor == 1 && $3.tiene_valor == 1){
							$$.tiene_valor = 1;
							
							//Calculamos el resultado
							if(strcmp($<operador>2.op, "=") == 0){
									$$.valor = $1.valor == $3.valor;
									$$.tipo_var = BOOLEANO;
							}else if(strcmp($<operador>2.op, "<") == 0){
									$$.valor = $1.valor < $3.valor;
									$$.tipo_var = BOOLEANO;
							}else if(strcmp($<operador>2.op, ">") == 0){
									$$.valor = $1.valor > $3.valor;
									$$.tipo_var = BOOLEANO;
							}else if(strcmp($<operador>2.op, ">=") == 0){
									$$.valor = $1.valor >= $3.valor;
									$$.tipo_var = BOOLEANO;
							}else if(strcmp($<operador>2.op, "<=") == 0){
									$$.valor = $1.valor <= $3.valor;
									$$.tipo_var = BOOLEANO;
							}else if(strcmp($<operador>2.op, "!=") == 0){
									$$.valor = $1.valor != $3.valor;
									$$.tipo_var = BOOLEANO;
							}else{
									$$.valor = NULL;
									$$.tipo_var = NULL;
							}
						}else{
							$$.tiene_valor = 0;
						}
						
                        
                }
        }
;
        
operador_relacional:
     '='
        {
                $<operador>$.tipo = BOOLEANO;
                $<operador>$.op = "=";
        }
|    '<'
        {
                $<operador>$.tipo = ENTERO;
                $<operador>$.op = "<";
        }
|    '>'
        {
                $<operador>$.tipo = ENTERO;
                $<operador>$.op = ">";
        }
|    tMEI
        {
                $<operador>$.tipo = ENTERO;
                $<operador>$.op = "<=";
        }
|    tMAI
        {
                $<operador>$.tipo = ENTERO;
                $<operador>$.op = ">=";
        }
|    tNI
        {
                $<operador>$.tipo = BOOLEANO;
                $<operador>$.op = "!=";
        }
;

expresion_simple:
     termino
         {
                $$.tipo_var = $1.tipo_var;
                $$.simbolo = $1.simbolo;
                $$.valor = $1.valor;
				$$.tiene_valor = $1.tiene_valor;
         }
|    expresion_simple operador_aditivo termino
        { //Tenemos que controlar los tipos. Similar a la acción operador_multiplicativo
                if($1.tipo_var != $3.tipo_var){ //Tipos distintos
                        error_semantico("Los tipos no son compatibles");
                }else if($1.tipo_var == CHAR){
                        error_semantico("Tipo CHAR no permitido");
                }else if($1.tipo_var == CADENA){
                        error_semantico("Tipo CADENA no permitido");
                }else if($1.tipo_var == ENTERO && $<operador>2.tipo != ENTERO){
                        error_semantico("Operación no permitida con tipo ENTERO");
                }else if($1.tipo_var == BOOLEANO && $<operador>2.tipo != BOOLEANO){
                        error_semantico("Operación no permitida con tipo BOOLEANO");
                }else{
                        $$.tipo_var = $1.tipo_var;
                        $$.simbolo = NULL;
                        
						if($1.tiene_valor == 1 && $3.tiene_valor == 1){
							$$.tiene_valor = 1;
							//Calculamos el resultado
							if(strcmp($<operador>2.op, "+") == 0){
									$$.valor = $1.valor + $3.valor;
							}else if(strcmp($<operador>2.op, "-") == 0){
									$$.valor = $1.valor - $3.valor;
							}else if(strcmp($<operador>2.op, "or") == 0){
									$$.valor = $1.valor || $3.valor;
									$$.tipo_var = BOOLEANO;
							}else{
									$$.valor = NULL;
							}
						}else{
							$$.tiene_valor = 0;
						}
						
                        
                }
        }
;

operador_aditivo:
     '+'
        {
                $<operador>$.tipo = ENTERO;
                $<operador>$.op = "+";
        }
|    '-'
        {
                $<operador>$.tipo = ENTERO;
                $<operador>$.op = "-";
        }
|    tOR
        {
                $<operador>$.tipo = BOOLEANO;
                $<operador>$.op = "or";
        }
;
        
termino:
     factor
         { //Subimos los datos del factor
                $$.tipo_var = $1.tipo_var;
                $$.simbolo = $1.simbolo;
                $$.valor = $1.valor;
				$$.tiene_valor = $1.tiene_valor;
         }
|    termino operador_multiplicativo factor
        { //Tenemos que controlar los tipos
                if($1.tipo_var != $3.tipo_var){ //Tipos distintos
                        error_semantico("Los tipos no son compatibles");
                }else if($1.tipo_var == CHAR){
                        error_semantico("Tipo CHAR no permitido");
                }else if($1.tipo_var == CADENA){
                        error_semantico("Tipo CADENA no permitido");
                }else if($1.tipo_var == ENTERO && $<operador>2.tipo != ENTERO){
                        error_semantico("Operación no permitida con tipo ENTERO");
                }else if($1.tipo_var == BOOLEANO && $<operador>2.tipo != BOOLEANO){
                        error_semantico("Operación no permitida con tipo BOOLEANO");
                }else{
                        $$.tipo_var = $1.tipo_var;
                        $$.simbolo = NULL;
						
						if($1.tiene_valor == 1 && $3.tiene_valor == 1){
							$$.tiene_valor = 1;
							if(strcmp($<operador>2.op, "*") == 0){
                                $$.valor = $1.valor * $3.valor;
							}else if(strcmp($<operador>2.op, "div") == 0){
									$$.valor = $1.valor / $3.valor;
							}else if(strcmp($<operador>2.op, "mod") == 0){
									$$.valor = $1.valor % $3.valor;
							}else if(strcmp($<operador>2.op, "and") == 0){
									$$.valor = $1.valor && $3.valor;
							}else{
									$$.valor = NULL;
							}
						}else{
							$$.tiene_valor = 0;
						}
                        
                        //Calculamos el resultado
                        
                }
        }
;

operador_multiplicativo:
     '*'
         {
                $<operador>$.tipo = ENTERO;
                $<operador>$.op = "*";
         }
|    tDIV
        {
                $<operador>$.tipo = ENTERO;
                $<operador>$.op = "div";
        }
|    tMOD
        {
                $<operador>$.tipo = ENTERO;
                $<operador>$.op = "mod";
        }
|    tAND
        {
                $<operador>$.tipo = BOOLEANO;
                $<operador>$.op = "and";
        }
;

//GRAMATICA VECTORES: Añadido el vector
//TODO: Terminar las acciones de los vectores
factor:
     '-' factor %prec MENOSU
         {
                if($2.tipo_var != ENTERO){ //El tipo no es entero
                        error_semantico("El tipo no es válido. Se esperaba un ENTERO");
                        $$.tipo_var = DESCONOCIDO;
                        $$.simbolo = NULL;
                }else{
                        $$.tipo_var = ENTERO;
                        $$.simbolo = NULL;
                        $$.valor = -$2.valor;
						$$.tiene_valor = $2.tiene_valor;
                }
         }
|    tNOT factor
        {
                if($2.tipo_var != BOOLEANO){
                        error_semantico("El tipo no es válido. Se esperaba un BOOLEANO");
                        $$.tipo_var = DESCONOCIDO;
                        $$.simbolo = NULL;
                }else{
                        $$.tipo_var = BOOLEANO;
                        $$.simbolo = NULL;
                        $$.valor = $2.valor;
						$$.tiene_valor = $2.tiene_valor;
                }
        }
|    '(' expresion ')'
        {
                $$.tipo_var = $2.tipo_var;
                $$.simbolo = $2.simbolo;
                $$.valor = $2.valor;
				$$.tiene_valor = $2.tiene_valor;
        }
|    tENTACAR '(' expresion ')'
        {
                if($3.tipo_var != ENTERO){
                        error_semantico("El tipo no es válido. Se esperaba un ENTERO");
                        $$.tipo_var = DESCONOCIDO;
                        $$.simbolo = NULL;
                }else{
                        $$.tipo_var = CHAR;
                        $$.simbolo = NULL;
                        $$.valor = $3.valor;
						$$.tiene_valor = 1;
                }
        }
|    tCARAENT '(' expresion ')'
        {
                if($3.tipo_var != CHAR){
                        error_semantico("El tipo no es válido. Se esperaba un CHAR");
                        $$.tipo_var = DESCONOCIDO;
                        $$.simbolo = NULL;
                }else{
                        $$.tipo_var = ENTERO;
                        $$.simbolo = NULL;
                        $$.valor = $3.valor;
						$$.tiene_valor = 1;
                }
        }
|    tIDENTIFICADOR
        {
                if($1.simbolo == NULL){ //La variable no existe
                        error_semantico("La variable no está declarada");
                        $$.tipo_var = DESCONOCIDO;
                        $$.simbolo = NULL;
                }else if(nivel < $1.simbolo->nivel){ //La variable no es visible por el nivel
                        error_semantico("La variable no es accesible por el nivel");
                        $$.tipo_var = DESCONOCIDO;
                        $$.simbolo = NULL;
                }else{ //La variable está en el nivel correcto y existe
                        $$.tipo_var = $1.simbolo->variable;
                        $$.simbolo = $1.simbolo;
						$$.tiene_valor = 0;
                        if($1.simbolo->asignado == 1){
                                $$.valor = $1.simbolo->valor; //Actualizamos el valor
                        }else{
                                warning("El identificador podría no estar inicializado");
                                $$.valor = NULL;
                        }
                }
                
        }
|    tCONSTENTERA
        {
                $$.tipo_var = ENTERO;
                $$.simbolo = NULL;
                $$.valor = yylval.constante;
				$$.tiene_valor = 1;
        }
|    tCONSTCHAR
        {
                $$.tipo_var = CHAR;
                $$.simbolo = NULL;
                $$.valor = yylval.constante;
				$$.tiene_valor = 1;
        }
|    tCONSTCAD
        {
                $$.tipo_var = CADENA;
                $$.simbolo = NULL;
				$$.tiene_valor = 0;
        }
|    tTRUE
        {
                $$.tipo_var = BOOLEANO;
                $$.simbolo = NULL;
                $$.valor = 1;
				$$.tiene_valor = 1;
        }
|    tFALSE
        {
                $$.tipo_var = BOOLEANO;
                $$.simbolo = NULL;
                $$.valor = 0;
				$$.tiene_valor = 1;
        }
|       tIDENTIFICADOR '[' expresion ']' //Se trata de un vector haremos lo mismo que con tIDENFICADOR
        {
                if($1.simbolo == NULL){ //La variable no existe
                        error_semantico("La variable no está declarada");
                        $$.tipo_var = DESCONOCIDO;
                        $$.simbolo = NULL;

                }else if(nivel < $1.simbolo->nivel){ //La variable no es visible por el nivel
                        error_semantico("La variable no es accesible por el nivel");
                        $$.tipo_var = DESCONOCIDO;
                        $$.simbolo = NULL;
                }else if($1.simbolo->tipo_extremo != $3.tipo_var){ //La variable está en el nivel correcto y existe
                        error_semantico("El tipo del índice no es correcto");
                        $$.tipo_var = DESCONOCIDO;
                        $$.simbolo = NULL;
                }else if($3.valor < $1.simbolo->extremo1 || $3.valor > $1.simbolo->extremo2){
                        if($3.tiene_valor == 1){
							error_semantico("El índice está fuera de rango");
							$$.tipo_var = $1.simbolo->variable;
							$$.simbolo = NULL;
						}else{
							warning("El índice podría estar fuera de rango");
							$$.tipo_var = $1.simbolo->variable;
							$$.simbolo = NULL;
						}
                }else{
                        $$.tipo_var = $1.simbolo->variable;
                        //$1.simbolo->componenteVector = 1;
                        $$.simbolo = NULL;
						$$.es_componente = 1;
						$$.tiene_valor = 0;
                }
        }
;

%%

/**********************************************************************/
main(int argc, char *argv[])
/**********************************************************************/
{
    extern FILE *yyin;
    char namein[100], nameout[100];
        nErrores = 0;
        
        if(argc <= 0){
                fprintf(stderr, "Ejecución errónea de pascual.y");
                exit(1);
        }
        
        //Controlamos los warnings
        if(argc == 3){
                if(strcmp(argv[2], "-w") == 0)
                        dar_warnings = 1;
                else{
                        printf("Los parámetros no son correctos: ./pascual.y <fichero> [-w]");
                        exit(1);
                }
        }
        
        //Control de muestra de resultados
        muestra = 0;
        
        //INICIO: XML
        xml = 1;
        if(xml == 1){
                fxml = fopen("resultado.xml", "w");
                if(fxml == NULL){
                        fprintf(stderr, "El fichero resultado.xml no ha podido abrirse.\n");
                        exit (1);
                }
        }
        //FIN: XML      
        strcpy (namein, argv[1]);
        strcat (namein, ".pc");
        yyin = fopen (namein, "r");
        if (yyin == NULL) {
           fprintf (stderr, "Fichero %s no existe.\n", namein);
           exit (1);
        }

    yyparse ();

    fclose (yyin);
        fclose(fxml);
        
        //Controlamos si hay errores para borrar el XML
        if(nErrores > 0){
                remove("resultado.xml");
        }
}

/**********************************************************************/
void abrir_bloque()
/**********************************************************************/
{
        nivel++;
}

/**********************************************************************/
void cerrar_bloque()
/**********************************************************************/
{       
        //Añadidas las funciones necesarias para cerrar bloque
        eliminar_variables(tabsim,nivel);
        ocultar_parametros(tabsim,nivel);
        eliminar_acciones(tabsim,nivel);
        eliminar_parametros_ocultos(tabsim,nivel+1);
        nivel--;
}

void ptabs(int i){
        int n;
        for(n=0;n<i;n++)
                fprintf(fxml, "\t");
}