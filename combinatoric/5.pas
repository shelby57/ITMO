var
  p: boolean;
  i, v, n, k, j, m: integer;
  x, d: array[1..50] of integer;

begin
  readln(n, m);
  p := true;
  for i := 1 to n do 
  begin
    x[i] := 1;
    d[i] := 1;
  end;
  while p <> false do 
  begin
    i := n;
    while (i > 1) and (((d[i] = 1) and (x[i] = m)) or ((d[i] = -1) and (x[i] = 1))) do
      i := i - 1;
    if ((d[i] = 1) and (x[i] = m)) or ((d[i] = -1) and (x[i] = 1)) then p := false else
    begin
      p := true;
      for v := 1 to n do 
        write(x[v] - 1);
      writeln;
      x[i] := x[i] + d[i];
      for j := i + 1 to m do  
        d[j] := -d[j];
    end;
  end;
  for v := 1 to n do 
    write(x[v] - 1);
end.