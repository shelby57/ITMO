type
  mas = array[1..20] of integer;

var
  a, b: mas;
  n, k, i: integer;

procedure GetNext;
var
  i, j: integer;
begin
  for i := 1 to k do
    write(a[i],' ');
  writeln;
  i := k;
  while (a[i] + k - i + 1 > n) do
    i := i - 1;
  a[i] := a[i] + 1;
  for j := i + 1 to k do 
    a[j] := a[j - 1] + 1;
end;

begin
  readln(n, k);
  for i := 1 to k do  
  begin
    a[i] := i;
    b[i] := i + (n - k);
  end;
  while a <> b do 
    GetNext;
  for i := 1 to k do 
    write(b[i],' ');
end.