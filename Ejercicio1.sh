#!/bin/bash
x=$(curl wttr.in) #1 Designamos una variable correspondiente al clima 
echo "$x" > /home/felipe/Escritorio/aver.txt #2 Se copia el texto correspondiente al wttr (clima) y luego se pega en un nuevo  archivo de texto
head -7 aver.txt  # 3 Se despliegan las primeras 5 líneas del archivo puse 7 en el head solo porque sino lo da incompleto.
rm aver.txt  # 4 Finalmente se elimina el documento creado.


