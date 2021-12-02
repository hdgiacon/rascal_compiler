{ Somatorio recursivo }

program prog4;
    var n,res: integer;
    function soma(num: integer): integer;
        begin
            if (num = 1) then
                soma := 1
            else
                soma := num + soma(num - 1);
        end;
begin
    read(n);
    res := soma(n);
    write(res);
end.