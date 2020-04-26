/* Autor:F-Virtualbox  
Compilador: gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
Compilado: gcc  Biseccion.c -o bisec
Fecha: abr sab 25 16:30:00 CST 2020
librerias: <stdio.h> , <math.h>
Resúmen: Se crea un programa que utliza el método numérico de bisección para hallar la raíz de una función
Entradas: a,b
Salida: h 
*/


//Se definen librerías
#include <stdio.h>
#include <math.h>

//Se definen funciones y variables a utilizar
double bisec(double a,double b);
double f(double x);
double h;

int main()
{
    //Se establecen los límites en donde se buscará una raíz (en ésta función hay una de 0  a 1)
    double a=0, b=1;
    
    //Se llama a la función de bisección.
    bisec(a,b);
    //Se imprime el valor almacenado que será, en éste caso la raíz.
    printf(" // Tras 50 iteraciones la raíz es = %.5lf //",h);
    return 0;
}
//Se define la función a utilizar
double f(double x)
{
    return 0.1*pow(x,2)+ x*log(x);
}

//Funciones para la bisección
double bisec(double a, double b)
{
    //Se hace un for loop para realizar las iteraciones de cada ciclo e ir cerrando cada vez mas y mas el intervalo
    for(int i=0;i<50;i++) //El número de iteraciones es arbitrario
        {
        h=(a+b)/2; //Se encuentra el punto medio entre los límites para ver si ahí es una raíz
        if(f(h)==0) //Se hace el caso en donde la iteración llega a dar con la raíz exacta, en ese caso devuelve h.
        {
            return h;
        }
        else if(f(h)*f(a)<0) //Si el producto entre la función valuada en la mitad y la cota inferior es menor que cero, se corre la cota superior en donde estaba la media.
        {
           b=h;
        }
        else 
        {
            a=h; //Caso contrario se corre la cote inferior al punto medio
        }
    }
    return h; //El medio se irá haciendo cada vez mas y mas estrecho dando un valor mucho mas aproximado a donde esté la raíz.
}