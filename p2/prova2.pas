// verifica se um numero digitado é par 10 vezes

program prog1;
    var num, k, aux: integer;
begin
    k := 0;
    while(k <> 10) do
    begin
        read(num);

        aux := num div 2;
        
        if(num = aux * 2) then
            write(true)
        else
            write(false);
        k := k + 1;
    end;
end. 


// escolha entre a soma e a subtração de 2 numeros


program prog2;
    var num1, num2, res, op: integer;

    procedure soma(n1: integer; n2: integer);
    begin
        res := num1 + num2;
        write(res);
    end;

    procedure subtracao(n1: integer; n2: integer);
    begin
        res := num1 - num2;
        write(res);
    end;

begin
    read(op);

    read(num1);
    read(num2);

    if(op = 1) then
        soma(num1,num2)
    else 
        subtracao(num1,num2);
end. 


// prog1 alterado para função


program prog3;
    var num, k: integer;
    var res: boolean;

    function verifica_par(num: integer): boolean;
        var aux: integer;
    begin
        aux := num div 2;

        if(num = aux * 2) then
            verifica_par := true
        else
            verifica_par := false;
    end;
    
begin
    k := 0;
    while(k <> 10) do
    begin
        read(num);

        res := verifica_par(num);
        write(res);
        
        k := k + 1;
    end;
end. 


// fibonacci recursivo

program prog4;
    var n, res: integer;

    function fibonacci(num: integer): integer;

    begin
        if((num = 1) or (num = 2)) then
            fibonacci := 1
        else
            fibonacci := fibonacci(num-1) + fibonacci(num-2);
    end;
begin
    read(n);

    res := fibonacci(n);
    write(res);
end.