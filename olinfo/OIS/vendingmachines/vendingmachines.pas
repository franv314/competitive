{ WARNING: this is a generic template, not specific to any task }

const
	MAXN = 100000;
	MAXQ = 100000;

{ input data }
var
    T, N, M, L, E, hacked, i : longint;
    P           		  : array[1..MAXN] of longint;

begin

    readln(T);
    for t := 1 to T do
    begin
		hacked := 0;
		E := 0;
		readln(N, M);
		for i := 1 to N do
		begin
			read(P[i]);
		end;
		for i := 0 to M - 1 do
		begin
			read(L);
			if L > 0 then
				E := E + L
			else
				E := E - P[-L];
			if E < 0 then
				hacked := 1;
		end;
		if hacked = 1 then writeln('HACKER') else writeln('OK');
    end;
end.