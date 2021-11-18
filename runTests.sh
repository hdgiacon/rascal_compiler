#!/bin/bash

FILE=rascal

if test -f "$FILE"; then
    printf "\n"

    ./rascal tests/cmdAtrib.ras     # foi

    printf "\n"

    ./rascal tests/cmdIf.ras        # foi

    printf "\n"

    ./rascal tests/cmdWhile.ras     # foi

    printf "\n"

    ./rascal tests/cmdWhileIf.ras   # foi

    printf "\n"

    ./rascal tests/funRec0.ras      # nao foi

    printf "\n"

    ./rascal tests/funRecRef.ras    # foi

    printf "\n"

    ./rascal tests/funSimples0.ras  # nao foi

    printf "\n"

    ./rascal tests/funSimples1.ras  # foi

    printf "\n"

    ./rascal tests/funSimples2.ras  # nao foi

    printf "\n"

    ./rascal tests/procRec0.ras     # nao foi

    printf "\n"

    ./rascal tests/procRec1.ras     # nao foi

    printf "\n"

    ./rascal tests/procRec2.ras     # foi

    printf "\n"

    ./rascal tests/procSimples.ras  # nao foi

    printf "\n"

    ./rascal tests/progDecVars.ras  # nao foi

    printf "\n"

    ./rascal tests/progSimples.ras  # foi

    printf "\n"
else
    echo -e "$FILE não existe, execute make para gerar o compilador!"
fi