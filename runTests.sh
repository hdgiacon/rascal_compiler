#!/bin/bash

FILE=rascal

if test -f "$FILE"; then
    ./rascal tests/cmdAtrib.ras

    ./rascal tests/cmdif.ras

    ./rascal tests/cmdWhile.ras

    ./rascal tests/cmdWhileIf.ras

    ./rascal tests/funRec0.ras

    ./rascal tests/funRecRef.ras

    ./rascal tests/funSimples0.ras

    ./rascal tests/funSimples1.ras

    ./rascal tests/funSimples2.ras

    ./rascal tests/procRec0.ras

    ./rascal tests/procRec1.ras

    ./rascal tests/procRec2.ras

    ./rascal tests/procSimples.ras

    ./rascal tests/progDecVars.ras

    ./rascal tests/progSimples.ras
else
    echo "$FILE não existe, execute make para gerar o compilador!"
fi