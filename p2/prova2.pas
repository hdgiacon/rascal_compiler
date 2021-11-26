// passar um intervalo fechado e somar os numeros pares

program prog1;
    var sum, init, fim, aux: integer;
begin
    read(init);
    read(fim);

    sum := 0;

    while(init <= fim) do
    begin
        aux := init div 2;
        
        if(init = aux * 2) then
            sum := sum + init;

        init := init + 1;
    end;

    write(sum);
end. 



// escolha entre a soma e a subtração de 2 numeros

program prog2;
    var num1, num2, res, op: integer;

    procedure operacoes(op: integer; n1: integer; n2: integer);
    begin
        if (op = 1) then
            res := num1 + num2
        else
            res := num1 - num2;
    end;

begin
    read(op);

    read(num1);
    read(num2);

    operacoes(op,num1,num2);
    
    write(res);
end. 



// fatorial iterativo

program prog3;
    var num, res: integer;

    function fatorial(n: integer): integer;
        var aux: integer;
    begin
        aux := 1;
        while(n > 1) do
        begin
            aux := aux * n;
            n := n - 1;
        end;

        fatorial := aux
    end;
begin
    read(num);

    res := fatorial(num);

    write(res);

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
