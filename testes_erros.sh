#!/bin/bash

FILE=rascal

declare -a progs=(cmdAtribE.ras procSimplesE.ras)

if test -f "$FILE"; then
    printf "\n"

    for i in "${progs[@]}"; do
        printf "teste $i: "

        ./rascal tests_errors/$i

        printf "\n \n"
    done
    
else
    echo -e "$FILE não existe, execute make para gerar o compilador!"
fi