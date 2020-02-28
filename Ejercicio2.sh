#!/bin/bash

#Establecemos las condiciones en los casos que se use la extensión .c
# y/o esté vació
echo "Nombre nuevo archivo: "
read nombre


#Se inician las condicionales:

if [ $nombre -z ]      #Condición en caso que el nombre este vacío
then 
echo "No es posible crear un archivo en blanco" 
else
if [ ${nombre:(-2)} == ".c" ]     #Condición en caso que el nombre termine con .c
then
echo "La extensión ya está incluida, ejectue denuevo"

else
#Condición cuando se escribe el nombre:

#Designamos variables para introducirlas próximamente al archivo de c. 
touch "$nombre".c         #Se crea el archivo
host=$(hostname)         #Se obtiene el nombre del host (equipo)
f=$(date)                # Fecha
ver=$(gcc --version|tee ver.txt) #Se usa gcc para la compilación de c y su versión#Seguidamente se copia en un archivo que se crea automáticamente llamado ver
#Se escribe  la información dentro del archivo .c demas de incluir las variables
echo "Escriba su resúmen: "
read resum
echo "Escriba las entradas: "
read entradas
echo "Escriba las salidas: "
read salidas

#Finalmente se asigna la escritura hacia el documento .c haciendo uso de lo anterior
echo "                
/* Autor:"$host"  
Compilador: $(head -1 ver.txt)
Compilado: gcc  "$nombre".c -o "$nombre"
Fecha: "$f"
librerias: <stdio.h>
Resúmen: $resum
Entradas: $entradas
Salida: $salidas 
*/

//Librerias
#include <stdio.h>
//numerar los pasos del pseudocodigo" >  "$nombre".c
rm ver.txt #Se elimina el archivo contenedor de la versión.
vim  "$nombre".c #Se abre el archivo desde vim.
fi
fi

	



