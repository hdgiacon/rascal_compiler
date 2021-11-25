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


// 

program prog2;
    var num1, num2, res, op: integer;

    procedure soma(n1: integer; n2: integer);
    begin
        res := num1 + num2;
    end;

    procedure subtracao(n1: integer; n2: integer);
    begin
        res := num1 - num2;
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


//

program prog3;
    var num, k: integer;

    function verifica_par(num: integer): boolean;
        var aux: integer;
            ret: boolean;
    begin
        aux := num div 2;

        if(num = aux * 2) then
            ret := true
        else
            ret := false;
    end;
    
begin
    k := 0;
    while(k <> 10) do
    begin
        read(num);

        write(verifica_par(num))
        
        k := k + 1;
    end;
end. 