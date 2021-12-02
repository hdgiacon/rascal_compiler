{ fatorial iterativo }

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