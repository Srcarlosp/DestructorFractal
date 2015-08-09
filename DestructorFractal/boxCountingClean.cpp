#include <cstdlib>
#include <iostream>
#include "unistd.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <vector>
#include "Constantes.h"

#define SNUM "0123456789"
#define AJUSTE 14
#define NITER 5
#define K0  0

using namespace std;

/* funciones definidas */
double countingbox(float **matriz,int puntos);
double minsqrFit(int n, double arx[], double ary[], double arw[],double *_lin_0, double *_lin_m);

int sort_compare0(const void *a, const void *b) {
 if( (*(float**)a)[0] > (*(float**)b)[0] ) return +1;
 if( (*(float**)a)[0] < (*(float**)b)[0] ) return -1;
 return 0;
 }
int sort_compare1(const void *a, const void *b) {
 if( (*(float**)a)[1] > (*(float**)b)[1] ) return +1;
 if( (*(float**)a)[1] < (*(float**)b)[1] ) return -1;
 return 0;
 }
void sort_fractal(float **fractal, int length, int dim) {
 switch(dim) {
 case 0: 
 default:
   qsort((void*)fractal,length,sizeof(fractal[0]), sort_compare0);
  break;
 case 1:
   qsort((void*)fractal,length,sizeof(fractal[0]), sort_compare1);
  }
 }
void find_sort_interval(float **fractal, int sz_fractal, int find_dim, float x_from, float x_to, int *i_from, int *i_to) {
 int ia, ib, i;
 if(x_from>fractal[sz_fractal-1][find_dim] || x_to<fractal[0][find_dim]) {
  *i_from=0; *i_to=-1;
  return;
  }
 
 i=ia=0;
 ib=sz_fractal-1;
 while(ib-ia > 1) {
  i=(ib+ia)/2;
  if( fractal[i][find_dim] < x_from ) ia=i+1;
  else                                ib=i;
  }
 *i_from=(ib+ia)/2;
  
 ia=i;
 i=ib=sz_fractal-1;
 while(ib-ia > 1) {
  i=ib-(2*ib-(ib+ia))/2;
  if( fractal[i][find_dim] >= x_to ) ib=i-1;
  else                              ia=i;
  } 
 *i_to=ib-(2*ib-(ia+ib))/2;
 
 return;
}

extern void createStateList(float ** espacio, vector<puntos>(*vec)[DIM]);

double boxCounting(int MAX_PUNTOS, vector<puntos>(*vec)[DIM])
{
	unsigned long int k;
	float **fract;// fractal con punteros

	/*asignamos memoria dinamica a la matriz de puntos del fractal*/
	fract = (float**)malloc(MAX_PUNTOS*sizeof(float));
	//comprobacion de asignacion de memoria
	if (fract == NULL){ printf("memoria insuficiente matriz"); exit(0); }
	//memoria para cada fila
	for (k = 0; k<MAX_PUNTOS; k++) fract[k] = (float*)malloc(2 * sizeof(float));
	//comprobacion de asignacion de memoria por filas
	for (k = 0; k<MAX_PUNTOS; k++)
		if (fract[k] == NULL){ printf("memoria insuficiente filas"); exit(0); }
	
	createStateList(fract, vec);
	return countingbox(fract, MAX_PUNTOS);
}

/* función de counting-box */
double countingbox(float **matriz,int puntos)
{
int k=0,c[AJUSTE],m,cn,kmax=AJUSTE; /*cambio 7 por  AJUSTE para obtener un punto más para el ajuste*/
    unsigned long int i,j,n;
	double pot,x[AJUSTE],y[AJUSTE],arw[AJUSTE],lin_0,lin_m;/*cambio 7 por 8 para obtener un punto más para el ajuste*/
	double *_lin_0=NULL,*_lin_m=NULL;
    FILE *resumen;	//fichero resumen de resultados

//#define K0  0    

	for(k=K0;k<kmax;k++){ /*cambio 7 por AJUSTE para obtener un punto más para el ajuste*/
        printf("k=%d de %d\n", k, kmax-1);
// inicilizo las matrices de conteo
		c[k]=0;
		pot=pow(2.0,k);
		cn=0;

        int m_i_from=0, m_i_to=0, m_j_from=0, m_j_to=0;

/* comienzo el bucle para contar donde hay puntos */
		for(i=0;i<pot;i++){
                double ixa=(double)i/pot, ixb=(double)(i+1)/pot;
                        
                sort_fractal(matriz, puntos, 0);//ordenar respecto de 1ªcoordenada 
                     
                find_sort_interval(matriz, puntos, 0, ixa, ixb, &m_i_from, &m_i_to);/*intervalo donde la 1ªcoordenada está entre ixa,ixb*/
                if( m_i_to<m_i_from )
                                continue;/*NO hay puntos, inicio el bloque con el siguiente valor de i*/

                sort_fractal(matriz+m_i_from,m_i_to-m_i_from+1, 1);/*ordena resp.2ªcoordenada los puntos con 1ªcoordenada entre ixa,ixb*/
                      
                        
		    for(j=0;j<pot;j++){
                    double jxa=(double)j/pot, jxb=(double)(j+1)/pot;
                            
                    find_sort_interval(matriz+m_i_from,m_i_to-m_i_from+1, 1, jxa, jxb, &m_j_from, &m_j_to);
                    if( m_j_to<m_j_from )
                                    continue;/*NO hay puntos, inicio el bloque con el siguiente valor de j*/
                                    
                    m_j_from+=m_i_from;
                    m_j_to+=m_i_from;
				    m=m_j_from;cn=0;
				    
			    	do{ /* ejecutamos mientras que hayamos encontrado un punto o hayamos pasado por todos ellos*/
					    if((matriz[m][0]<ixb)&&(matriz[m][0]>=ixa)&&(matriz[m][1]<jxb)&&(matriz[m][1]>=jxa))
				         {cn=1;}
					    else{m++;}
					}while(cn==0 && m<=m_j_to);
					/* sumamos los unos que tenemos en cn y lo controlamos en c */
                    if(cn==1){c[k]=c[k]+1;}	
				}}
		
        printf("c[%d]=%d\n", k, c[k]);
        if(k>4){
        if((log((float)c[k-1])-log((float)c[k-2]))/(log((float)c[k])-log((float)c[k-1]))>2){kmax=k;break;}}
        
                }
     	/*abrir el fichero resumen*/
 if((resumen=fopen("resumendim2.txt","a"))==NULL){printf("problemas de apertura del fichero resumendim2.txt");}  
       
 /* construimos los valores de x= log(2)*k,y=log(c(k)) para el ajuste*/
	for(k=K0;k<kmax;k++){x[k]=log(2.0)*k; /*cambio 7 por AJUSTE para obtener un punto más para el ajuste*/
					y[k]=log((double)c[k]);
					fprintf(resumen,"el valor de c(%d)=%d, x(%d)=%0.4f\t y(%d)=%0.4f\n",k,c[k],k,x[k],k,y[k]);
					}
/*ajustamos*/
minsqrFit(kmax-K0,x+K0,y+K0,arw,&lin_0,&lin_m);/*cambio 7 por AJUSTE para obtener un punto más para el ajuste*/

printf("dimension delta=2^(-(%d -1)) m=%0.4f\n",kmax, lin_m);
fprintf(resumen,"dimension delta=2^(-(%d -1)) m=%0.4f\n",kmax,lin_m);
   	/*cierro el fichero resumen*/
	fclose(resumen);

return	lin_m;

}

//programa de ajuste por mínimos cuadrados
double minsqrFit(int n, double arx[], double ary[], double arw[],
                 double *_lin_0, double *_lin_m) {
 double Sw, Sx, Sy, Sxx, Syy, Sxy;
 double chi2;
 int i, nit;
 double x,y,w;
 double lin_0, lin_m;

 chi2=1.0;
 for(i=0; i<n; i++)
  arw[i]=0.0;

 nit=0;
 do {

  Sw=0.0; Sx=0.0; Sy=0.0; Sxx=0.0; Syy=0.0; Sxy=0.0;
  for(i=0; i<n; i++) {
   x=arx[i]; y=ary[i];
   w=chi2/(chi2+arw[i]*arw[i]);
   Sw+=w;
   Sx+=w*x;
   Sy+=w*y;
   Sxx+=w*x*x;
   Sxy+=w*x*y;
   Syy+=w*y*y;
   }

  lin_0=(Sxx*Sy-Sx*Sxy)/(Sw*Sxx-Sx*Sx);
  lin_m=-(Sx*Sy-Sw*Sxy)/(Sw*Sxx-Sx*Sx);

  chi2=lin_0*lin_0+(Syy+2*lin_m*Sxy-2*lin_0*Sy+lin_m*lin_m*Sxx-2*lin_0*lin_m*Sx)/Sw;
  for(i=0; i<n; i++)
   arw[i]=ary[i]-lin_0-lin_m*arx[i];

  nit++;
  } while(nit<NITER);

 *_lin_0=lin_0;
 *_lin_m=lin_m;
 //printf(" dentro de la funcion pendiente de la recta m=%0.4f\n",lin_m);
 return chi2;
 }

