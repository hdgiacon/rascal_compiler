#!/bin/bash

FILE=rascal

declare -a progs=(cmdAtrib.ras cmdIf.ras cmdWhile.ras cmdWhileIf.ras funRec0.ras funRecRef.ras funSimples0.ras funSimples1.ras 
    funSimples2.ras procRec0.ras procRec1.ras procRec2.ras procSimples.ras progDecVars.ras progSimples.ras)

if test -f "$FILE"; then
    printf "\n"

    for i in "${progs[@]}"; do
        printf "teste $i: "

        ./rascal tests/$i

        printf "\n \n"
    done
    
else
    echo -e "$FILE não existe, execute make para gerar o compilador!"
fi