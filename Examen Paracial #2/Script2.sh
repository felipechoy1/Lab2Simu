#!/bin/bash
#Se compila el archivo de C, procediendo luego a ejecutarlo. 
gcc Biseccion.c -lm -o bisec 
./bisec
#2. Se hacen los respectivos ajustes acorde a los datos entregados como el rango de 0 a 1 en x como los labels
printf "\n set xrange [0:1] \n set xlabel 'x' \n set title 'Gráfica de la función y=0.1x²+xln(x)' \n set ylabel 'eje y' \n g(x)=0.1*x**2+x*log(x) ">> bistec.gp
#3 Se grafica la función enviándole el comando al mini-script.
printf "\n plot g(x)" >> bistec.gp
#4 Se ejecuta gnuplot con -p (que leerá nuestro mini-scritp)
gnuplot -p "bistec.gp"
#5. Se remueve el 'mini-script' para no confundir al usuario.
rm bistec.gp
