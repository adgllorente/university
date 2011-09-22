/*
 * Fichero: gauss.c
 * Version: 1.3 - Dic 2010
 *
 * Adaptación de gauss.c  (CS252, Spring 1994)
 *
 * Pablo Ibáñez
 * Jesús Alastruey
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <limits.h>
#include <math.h>

 /* No hay que cambiar MAXSIZE en cada ejecución (se define constante)
 *  por tanto, no es necesario recompilar para ejecutar
 * el programa con distintos tamaños de problema (matriz, vector)
 */
#define MAXSIZE		4104

double A[MAXSIZE][MAXSIZE];
double P[MAXSIZE];
double B[MAXSIZE];

int
main(int argc, char *argv[])
{
  int r, s, i, j, intervalos;
  int repeat, limit, m_size;
  struct tms time_info;
  clock_t user0, user1, sample_cpu, sample_elapsed;
  clock_t total = 0, total_sqrd = 0;
  clock_t tinicio, tfinal, ttotal = 0;
  clock_t etime0, etime1;
  float timer_resolution;
  float loop_mean, loop_var, test_mean, loop_std_ratio_c; 

  if (argc < 4) {
    printf("Uso:%s <tamaño-matriz> <numero-de-iteraciones> <numero-de-pruebas>\n", argv[0]);
    exit(-1);
  }

  m_size = atoi(argv[1]);
  if (m_size > MAXSIZE) {
      fprintf(stderr,"ERROR: el tamaño de la matriz (%d) debe ser menor que MAXSIZE (%d)\n", m_size, MAXSIZE);
      exit(1);
  }
   
  limit = atoi(argv[2]);
  repeat = atoi(argv[3]);
  if ((limit < 1) || (repeat < 1)) {
      fprintf(stderr,"ERROR: el número de iteraciones y el de pruebas debe ser mayor que 0\n");
      exit(1);
  }
  
  /* Inicializacion */
  for (i = 0; i < m_size ;i++) {
    B[i] = (double) i + 4.0;    
    P[i] = (double) i * 2.0;    
    for (j = 0; j < m_size ; j++) {
      A[i][j] = (double) i + (double) j;
    }
  }

  /*
   * timer_resolution = resolucion en microsegundos del temporizador del computador
   * (tiempo en milisegundos entre dos ticks del temporizador) 
   * Se calcula a partir del nº de intervalos que el temporizador cuenta cada segundo.
   * Para saber este nº de intervalos hay que usar la llamada sysconf(_SC_CLK_TCK).
   * El programa realiza esta llamada e inicializa la variable timer_resolution.
   */
  intervalos = sysconf(_SC_CLK_TCK);
  timer_resolution = 1000000.0/intervalos;
  
  printf ("\n******** Datos ********\n");
  printf("Resolucion del temporizador: %7.1f usg (%d intervalos/seg)\n", timer_resolution, intervalos);
  printf("Tamaño_matriz, limit, repeat:  %dx%d, %d, %d\n", m_size, m_size, limit, repeat);
  /*printf("Tamaño de float: %d\n", sizeof(float)); */
  printf("Ejecutando gauss v1.3.\n\n");
    
   /* Inicio del cálculo del tiempo de ejecución de todos los bucles */ 
  times(&time_info);	/* man -s2 times */
  tinicio = time_info.tms_utime;

  /* Ejecuta el experimento "repeat" veces */
  for (r = 0; r < repeat; r++)
  {
    /* Ponemos en marcha el cronometro */
    etime0 = times(&time_info);
    //user0 = time_info.tms_utime + time_info.tms_stime;
    user0 = time_info.tms_utime;

    for (s = 0; s < limit; s++)
    {
      /* Impide optimizaciones agresivas del compilador */
      A[0][0] = 0.0;

      /* Estos dos bucles anidados son que queremos medir: L/U  */
      for (i = 0; i < m_size; i++)
      {
	for (j = 0; j < m_size; j++)
	   A[i][j] = A[i][j] - P[i]*B[j];
      } /* Fin L/U */
    } /* Fin s */

    //sleep(1);

    /* Paramos el cronometro */
    etime1 = times(&time_info);
    //user1 = time_info.tms_utime + time_info.tms_stime;
    user1 = time_info.tms_utime;

    sample_cpu = user1 - user0;
    sample_elapsed = etime1 - etime0;

    printf("*** Test %02d = %8.3f usg (%8.3f)\n", r+1,
			sample_cpu*timer_resolution/limit,
			sample_elapsed*timer_resolution/limit);

    if (sample_cpu == 0)
      printf("AVISO: tiempo de ejecución menor que la resolución del reloj\n");
    else if (sample_cpu < 20)
    	printf("AVISO: tiempo de ejecución (%4.2f usg) menor que 20 ticks del reloj (%4.2f usg)\n", sample_cpu*timer_resolution, 20.0*timer_resolution);
    	
    total += sample_cpu;
    total_sqrd += (sample_cpu * sample_cpu);
  } /* fin repeat */

  /* Cálculo del tiempo de ejecución de todos los bucles */
  times(&time_info);
  tfinal = time_info.tms_utime;
  //tfinal = time_info.tms_utime + time_info.tms_stime;
  ttotal = tfinal - tinicio;
  
  /* Cálculo de la varianza y desviación estándar
   * de las medidas obtenidas por el bucle repeat */
  /* VAR[X] = E[X^2] - E[X]^2 */
  /* STD[X] = sqrt(VAR[X]) */
  loop_mean = (float) total / repeat;
  loop_var = ((float) total_sqrd / repeat) - (loop_mean * loop_mean);
  loop_std_ratio_c = loop_var / (loop_mean*loop_mean);
  if (loop_std_ratio_c > 0.0025)
	printf("AVISO: Varianza de las mediciones demasiado alta\n");

  test_mean = loop_mean / limit;
  printf("\n******** Resultados ********\n");
  printf("Tiempo medio de ejecución de L/U    = %8.3f usg\n", test_mean*timer_resolution);
  printf("Tiempo medio de ejecución de limit  = %8.0f usg\n", loop_mean*timer_resolution);
  printf("Tiempo total de ejecución de repeat = %8.0f usg\n\n", ttotal*timer_resolution);
  
  exit(0);
}
