/* Autor:F-Virtualbox  
Compilador: gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
Compilado: gcc Cuadrados.c -o cuad
Fecha: abr sab 25 10:30:00 CST 2020
librerias: <stdio.h> , <math.h>
Resúmen: Se crea un programa que utliza el método numérico de mínimos cuadrados para ver si un conjunto de datos se ajusta a éste 
Entradas: x,y, *fp.
Salidas: Datos.txt texto.gp .
*/

#include <stdio.h>
#include <math.h>
double minc(double x, double y);
int main()
{   //Se crea un puntero en donde se creará un 'mini-script' 
    FILE *fp;
    //Se almacenan los datos anteriormente dados
    double x[15]={2006,2007,2008,2009,2010,2011,2012,2013,2014,2015,2016,2017,2018,2019};
    double y[15]={1.003,0.961,0.928,0.913,0.880, 0.846, 0.807, 0.766, 0.734, 0.713, 0.692, 0.675, 0.656, 0.638};
    int i;
    //Número de datos
    int n = 14;
    //Variables a utilizar para el método de mínimos cuadrados
    double sumax,sumaxc,sumay,sumayc,sumaxy;
    //Variable de pendiente m y corte b (y intersecto)  
    double m,b;
    
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
    printf("\n //* La pendiente de los datos es: %.3f", m);    //Se iprime la misma
    
    b=((sumay-(m*sumax))/n); //Caso similar con el y-intersécto
    printf("\n     El corte de los datos es: %.3f", b); //Se imprime el mismo

      printf("\n     La ecuación de la recta por regresión lineal es: y = %.3f x  + %.3f *//\n ", m,b); //Se despliega la función ajustada
    
    //Se imprime el año en donde no valdrá nada el dólar (cuando y=0 y se despeja x.)
    printf("\n \t///El año en el que el dólar no valdrá nada será apróximadamente en %.0f ///\n", -b/m);

    //Uso del puntero inicalizandolo, acto seguido almacenando la función
    fp=fopen("texto.gp","w");//Se abre un documento en donde se escribirá
    fprintf(fp,"f(x)=%f*x+%.3f",m,b); //Se le imprime la función con la diferencia que estará con todas las cifras significativas posibles.
    fclose(fp); //Se cierra y termina de escribir
    
    fp=fopen("Datos.txt","w");//Se abre un documento en donde se escribirá
    for(int i=0;i<14;i++)
    {
      fprintf(fp,"%.0f   %.3f \n",x[i],y[i]); //Se le imprime la función con la diferencia que estará con todas las cifras significativas posibles.
       //Se cierra y termina de escribir
    }
    fclose(fp);
    return 0; 
    
}


