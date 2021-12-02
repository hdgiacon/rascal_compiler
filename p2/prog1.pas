{ passar um intervalo fechado e somar os numeros pares }

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