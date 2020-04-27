/* Autor:F-Virtualbox  
Compilador: gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
Compilado: gcc Cuadrados.c -o cuad
Fecha: abr sab 25 10:30:00 CST 2020
librerias: <stdio.h> , <math.h>
Resúmen: Se crea un programa que utliza el método numérico de mínimos cuadrados para ver si un conjunto de datos se ajusta a éste 
Entradas: x,y, *fp
Salidas: Datos.txt texto.gp 
*//
//Se declararan librerías
#include <stdio.h>
#include <math.h>

//Se declaran funciones a usar
double minc(double x[], double y[]); //Función para mínimos cuadrados
double archivo(double x[], double y[], FILE *fp); //Función para crear archivos con datos y las funciones.

//Variables globales a usar
double sumax,sumaxc,sumay,sumayc,sumaxy,merr,berr,r,eps=0.1;
double m,b; //Variable de pendiente m y corte b (y intersecto) 
int i; //Iterador

int main()
{   //Se crea un puntero en donde se creará un 'mini-script' 
    FILE *fp;
    //Se almacenan los datos anteriormente dados
    double x[]={2006,2007,2008,2009,2010,2011,2012,2013,2014,2015,2016,2017,2018,2019};
    double y[]={1.003,0.961,0.928,0.913,0.880, 0.846, 0.807, 0.766, 0.734, 0.713, 0.692, 0.675, 0.656, 0.638};
    puts("\n A continuación se mostrará el comportamiento del valor del dólar con respecto del euro mediante el método de mínimos cuadrados\n");
    //Se llama a las 2 funciones principales
    minc(x,y);
    archivo(x,y,fp);
    
    //Imprimiendo la función y el el año en donde no valdrá nada (y=0)
    printf("\n\t ///*La ecuación de la recta por regresión lineal es: y = (%.3f +- 0.00)x  + (%.3f +- %.3f) \n ", m,b,berr); //Se despliega la función ajustada
    printf("\t     El año en el que el dólar no valdrá nada será apróximadamente en %.0f *///\n", -b/m);
    return 0; 
}

double minc(double x[], double y[])
{
    int n = 14; //Número de datos
    //Se crea un ciclo de iteraciones hasta el número de datos que se tienen.
    for(i=0;i<n;i++)
    {
      sumax+=x[i]; //Sumnatoria de x
      sumaxc= sumaxc + (x[i]*x[i]); //Sumatoria de x²
      sumay+=y[i]; //Sumatoria de y
      sumayc= sumayc + (y[i]*y[i]); //Sumatoria de y²
      sumaxy+=(x[i]*y[i]); //Sumatoria de xy
    }
     //Se imprime el resultado de cada sumatoria (por si el usuario necesita verificar o usar algun dato)
    printf("\n /* La suma de x es: %.3f",sumax);
    printf("\n    La suma de x² es: %.3f",sumaxc);
    printf("\n    La suma de y es: %.3f",sumay);
    printf("\n    La suma de y² es: %.3f",sumayc);
    printf("\n    La suma de xy es: %.3f */ \n",sumaxy);
    
    //Imprimiendo los datos importantes de la función
    m=(((n*sumaxy)-(sumax*sumay))/((n*sumaxc)-(sumax*sumax))); //Se utiliza la fórmula de pendiente para mínimos cuadrados.
    b=((sumay-(m*sumax))/n); //Caso similar con el y-intersécto  
    printf("La pendiente es : %.3f",m);
    printf("El corte de datos es: %.3f",b);
    //Imprimiendo sus errores
    merr=sqrt(n*eps/(sumaxc-(pow(sumax,2))));  //Error de la pendiente
    berr=eps/n; //Error del intersecto
    r=((n*sumaxy-sumax*sumay)/(sqrt(((n*sumaxc)-pow(sumax,2))*(n*sumayc-(pow(sumay,2)))))); //Coeficiente de correlación
    //Se imprimen los resultados
    printf("\n  //* El error en la pendiente es de %f",merr); 
    printf("\n      El error del intercepto es %f",berr);
    printf("\n      El coeficiente de correlación r es %f *//\n",r);


}

double archivo(double x[],double y[],FILE *fp)
{   
    //Escribiendo los datos leídos en un 1 mini-script y 1 documento de texto
    fp=fopen("texto.gp","w");//Se abre un documento en donde se escribirá
    fprintf(fp,"f(x)=%f*x+%.3f",m,b); //Se le imprime la función con la diferencia que estará con todas las cifras significativas posibles.
    fclose(fp); //Se cierra y termina de escribir
    
    fp=fopen("Datos.txt","w");//Se abre un documento en donde se escribirán los datos de los vectores en un documento de text
    for(int i=0;i<14;i++)
    {
      fprintf(fp,"%.0f   %.3f \n",x[i],y[i]); //Se le imprime la función con la diferencia que estará con todas las cifras significativas posibles.
    }
    fclose(fp);//Se cierra y termina de escribir
}


