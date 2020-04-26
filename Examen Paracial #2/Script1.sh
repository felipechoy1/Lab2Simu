#!/bin/bash
#Se compila el archivo de C, procediendo luego a ejecutarlo 
gcc Cuadrados.c -lm -o cuad
./cuad
#2. Se hacen los respectivos ajustes acorde a los datos entregados como el rango de años y títulos
printf "\n set xrange [2006:2019] \n set xlabel 'Años' \n set title 'Gráfica del valor del dólar ente el Euro con el paso de los años' \n set ylabel 'Valor del dólar ante el Euro' ">> texto.gp
#3 Se grafican ambos datos, siendo f(x) la del ajuste por mínimos cuadrados y 'Datos' el documento que los contiene.
printf "\n plot f(x)" >> texto.gp
printf "\n replot 'Datos.txt' " >> texto.gp
#4 Se le indica a gnuplot que lea el mini-script en donde se le indican las instrucciones anteriores.
gnuplot -p "texto.gp"
#5. Se remueve el 'mini-script' para no confundir al usuario.
rm texto.gp
rm Datos.txt