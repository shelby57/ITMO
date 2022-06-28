type
  mas = array[1..20] of integer;

var
  a, b: mas;
  i, n, v, m: integer;

procedure GetNext;
var
  i, j, x: integer;
begin
  v := v + 1;
  if(v = m) then
  begin
    for i := 1 to n do  
      write(a[i],' ');
    exit;
  end;
  i := n;
  while (i > 1) and (a[i] < a[i - 1]) do
    i := i - 1;
  j := n;
  while a[j] < a[i - 1] do
    j := j - 1;
  swap(a[i - 1], a[j]);
  for j := 0 to (n - i + 1) div 2 - 1 do
    swap(a[i + j], a[n - j]);
end;

begin
  readln(n, m);
  m := m + 1;
  for i := 1 to n do 
  begin
    a[i] := i;
    b[i] := n - i + 1;
  end;
  while a <> b do 
    GetNext;
  v := v + 1;
  if(v = m) then
    for i := 1 to n do
      write(b[i],' ');
end.