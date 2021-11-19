#!/bin/bash

FILE=rascal

if test -f "$FILE"; then
    printf "\n"

    ./rascal tests/cmdAtrib.ras     

    printf "\n"

    ./rascal tests/cmdIf.ras        

    printf "\n"

    ./rascal tests/cmdWhile.ras     

    printf "\n"

    ./rascal tests/cmdWhileIf.ras   

    printf "\n"

    ./rascal tests/funRec0.ras      

    printf "\n"

    ./rascal tests/funRecRef.ras    

    printf "\n"

    ./rascal tests/funSimples0.ras  

    printf "\n"

    ./rascal tests/funSimples1.ras  

    printf "\n"

    ./rascal tests/funSimples2.ras  

    printf "\n"

    ./rascal tests/procRec0.ras     

    printf "\n"

    ./rascal tests/procRec1.ras     

    printf "\n"

    ./rascal tests/procRec2.ras     

    printf "\n"

    ./rascal tests/procSimples.ras  

    printf "\n"

    ./rascal tests/progDecVars.ras  

    printf "\n"

    ./rascal tests/progSimples.ras  

    printf "\n"
else
    echo -e "$FILE não existe, execute make para gerar o compilador!"
fi