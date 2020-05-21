#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

//Se definen las constantes a utilizar
const long double G=6.693e-11;
const long double Rt=6.378e6;
const long double Mt= 5.9736e24;
const long double R= 287.06;
const long double L= 6.5e-3;
const long double go= 9.81;
const long double To= 288.15;
const long double Po=101325;
//Se definen rho y g, que se irán almacenando, lo hago de esta forma para no tener conflictos eventualmente entre métodos/funciones.
double rho;
double ge;
double Fa;
double ac;
double t;
class Cohete
{
    private: //Atributos de cada cohete
    double Eo,tsfc,cd,sa,mo,mfo,y,dydt;
   
    public: //Métodos de cada cohete
    Cohete(long double, long double, long double, long double, long double, long double, long double, long double); //Constructor
    long double tiempo();
    long double despegar(); 
    long double densidad();
    long double g();
    long double presion();
    long double caida();
    long double friccion();
    long double aceleracion();
    

};
//Se inicializa el constructor
Cohete::Cohete(long double _a, long double _b, long double _c, long double _d, long double _e, long double _f,  long double _g, long  double _h)
{
    Eo=_a;
    tsfc=_b;
    cd=_c;
    sa=_d;
    mo=_e;
    mfo=_f;
    y=_g;
    dydt=_h;
}


//Método para encontrar el tiempo, ojo, es fácil ver que la ecuación de la masa (combustible) se comporta de
//forma LINEAL CON PENDIENTE NEGATIVA, (si se resolviese la edo sería obvio), por lo tanto la función es facil de ver
long double Cohete::tiempo()
{   
    t=mfo/(tsfc*Eo);
    return t;
}


long double Cohete::despegar()
{   
    //Se crean los respectivos punteros encargados de generar los archivos de texto, en conjunto con los scripts que harán que salgan las gráficas.
    FILE *fp;
    FILE *wp;
    FILE *hp;
    char filename[64], noname[64],yesname[64];
    cout<<"Siga las instrucciones que se le solicitan por favor"<<endl;
    cout<<"Si está en el primer cohete anote los nombre de los archivos como 1.txt,2.txt,3.txt"<<endl;
    cout<<"Si está en el segundo cohete anote 4.txt,5.txt,6.txt"<<endl;
    cout<<"Si está en el tercer cohete anote 7.txt,8.txt,9.txt"<<endl;
    cout<<"Cada archivo seguido de un 'enter'"<<endl;
    cin>>filename;
    cin>>noname;
    cin>>yesname;
    fp=fopen(filename,"w");
    wp=fopen(noname,"w");
    hp=fopen(yesname,"w");
    //Se hace el método numérico para encontrar cada parte
    float ymax=0; //Encargado de la altura máxima
    float tiempo;
    float mc=mo+mfo;
    float delta=1;
    float tf=1800;
    friccion();
    //Método de euler para cada iteracion de tiempo
    for(int i=0;i<tf;i++)
    {   
        friccion(); //En cada iteracion se llama a la fricción 
        y=y+delta*dydt;
        dydt+=(Eo/mc)-(Fa/mc)-ge;
 
        if(mfo<=0) //Analiza el caso de la gasolina, si se acaba el empuje es 0.
        {
            mfo=0; 
            Eo=0;
        }
    
        else
        {
            mfo+=delta*(-tsfc*Eo); //Caso contrario se sigue iterando la mfo.
        
        }
        if(y>ymax) //Indicador de la altura máxima
        {
            ymax=y;
        }
   
        if(y>0) //Indicador para el tiempo de impacto
        {
            tiempo=i*delta;
        }
        mc=mo+mfo; //Se le recuerda el valor de mc
        fprintf(fp,"%.3f\t %.3f\n ",delta*i,y);
        fprintf(wp,"%.3f\t %.3f\n ",delta*i,dydt);
        fprintf(hp,"%.3f\t %.3f\n ",dydt,y);
          
    }
       // Esta sección se encarga de generar cada script encargado de hacer cada gráfica.
       fclose(fp);
       fclose(wp);
       fclose(hp);  
       fp=fopen("script1.gp","w");
       fprintf(fp," \n set title 'Gráfica de altura(m) versus tiempo(s) Cohete 1 '\n set xlabel 'Tiempo (s)'\n set ylabel 'altura (m)'\nplot '1.txt'\n set term png\n set output '1altvstiempo.png'\n replot\n set term x11");
       fclose(fp);
       fp=fopen("script2.gp","w");
       fprintf(fp," \n set title 'Gráfica de velocidad(m/s) versus tiempo(s)  Cohete 1'\n set xlabel 'Tiempo (s)'\n set ylabel 'velocidad (m/s)'\nplot '2.txt'\n set term png\n set output '1velvstiempo.png'\n replot\n set term x11");
       fclose(fp);
       fp=fopen("script3.gp","w");
       fprintf(fp," \n set title 'Gráfica de velocidad(m/s) versus altura(m) Cohete 2 '\n set xlabel 'altura (m)'\n set ylabel 'velocidad (m/s)'\nplot '3.txt'\n set term png\n set output '1velvsaltura.png'\n replot\n set term x11");
       fclose(fp);
       fp=fopen("script4.gp","w");
       fprintf(fp," \n set title 'Gráfica de altura(m/s) versus tiempo(s) Cohete 2'\n set xlabel 'tiempo (s)'\n set ylabel 'altura (m)'\nplot '4.txt'\n set term png\n set output '2altvstiempo.png'\n replot\n set term x11");
       fclose(fp);
       fp=fopen("script5.gp","w");
       fprintf(fp," \n set title 'Gráfica de velocidad(m/s) versus tiempo(s) Cohete 2'\n set xlabel 'tiempo (s)'\n set ylabel 'velocidad (m/s)'\nplot '5.txt'\n set term png\n set output '2velvstiempo.png'\n replot\n set term x11");
       fclose(fp);
       fp=fopen("script6.gp","w");
       fprintf(fp," \n set title 'Gráfica de velocidad(m/s) versus altura(m) Cohete 3'\n set xlabel 'altura (m)'\n set ylabel 'velocidad (m/s)'\nplot '6.txt'\n set term png\n set output '2velvsaltura.png'\n replot\n set term x11");
       fclose(fp);
       fp=fopen("script7.gp","w");
       fprintf(fp," \n set title 'Gráfica de altura(m) versus tiempo(s) Cohete 3'\n set xlabel 'tiempo (s)'\n set ylabel 'altura(m)'\nplot '7.txt'\n set term png\n set output '3altvstiempo.png'\n replot\n set term x11");
       fclose(fp);
       fp=fopen("script8.gp","w");
       fprintf(fp," \n set title 'Gráfica de velocidad(m/s) versus tiempo(s) Cohete 3'\n set xlabel 'tiempo(s)'\n set ylabel 'velocidad (m/s)'\nplot '8.txt'\n set term png\n set output '3velvstiempo.png'\n replot\n set term x11");
       fclose(fp);
       fp=fopen("script9.gp","w");
       fprintf(fp," \n set title 'Gráfica de velocidad(m/s) versus altura(m) Cohete 3'\n set xlabel 'altura (m)'\n set ylabel 'velocidad (m/s)'\nplot '9.txt'\n set term png\n set output '3velvsaltura.png'\n replot\n set term x11");
       fclose(fp);
       
       //Se imprimen los resultados de cada cohete en la consola
       cout<<"1.El tiempo de impacto es "<<tiempo<<"s"<<endl; //Se manda a imprimir los resultados.
       cout<<"2.Su altura maxima es: "<<ymax<<"m"<<endl;
       cout <<"3. El tiempo en que se queda sin combustible el cohete es: "<<t<<"s"<<endl;
}  

//Método encargado de encontrar la fricción 
long double Cohete::friccion()
{
    densidad(); //Llama a ambas funciones para tener los valores
    g(); 
    Fa=0.5*rho*cd*sa*dydt*abs(dydt);
    return Fa;
}

//Método para la densidad
long double Cohete::densidad()
{   
    if(y>(To/L)) //Condiciones para que funcione la densiadad según está dada.
    {
        rho=0;
    }
    else
    {
    rho =Po/(R*To)*pow((1-(L*y)/To),(go/(R*L)));
    }
  
    return rho;
}
//Método para g
long double Cohete::g()
{
    ge= (G*Mt)/(pow(Rt+y,2));
    return ge;
}


int main()
{
    Cohete c1(3e7,3.248e-4,61.27,201.06,1.1e5,1.5e6,0,0); //Se inicializa el primer cohete
    Cohete c2(2.7e7,2.248e-4,61.27,201.06,1.1e5,1.5e6,0,0);//Se inicializa el segundo cohete
    Cohete c3(2.5e7,2.248e-4,70.25,215.00,1.8e5,2.1e6,0,0);//Se inicializa el tercer cohete
    cout<<"\n \t Datos del cohete 1!"<<endl; 
    c1.tiempo();
    c1.despegar();
    cout<<"\n \t Datos del cohete 2!"<<endl;
    c2.tiempo();
    c2.despegar();
    cout<<"\n \t Datos del cohete 3!"<<endl;
    c3.tiempo();
    c3.despegar();
    //Se ejecturan los scripts en la consola de bash, seguido de eliminarlos.
    system("gnuplot -l 'script1.gp' 'script2.gp' 'script3.gp' 'script4.gp' 'script5.gp' 'script6.gp' 'script7.gp' 'script8.gp' 'script9.gp' ");
    system("rm script1.gp script2.gp script3.gp script4.gp script5.gp script6.gp script7.gp script8.gp script9.gp");  
        return 0;
}
