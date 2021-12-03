{ escolha entre a soma e a subtração de 2 numeros }

program prog2;
    var num1, num2, res, op: integer;

    procedure operacoes(op: integer; n1: integer; n2: integer);
    begin
        if (op = 1) then
            res := n1 + n2
        else
            res := n1 - n2;
    end;

begin
    read(op);

    read(num1);
    read(num2);

    operacoes(op,num1,num2);
    
    write(res);
end. 