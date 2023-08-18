%:include <bits/stdc++.h>
using namespace std;

%:define MAXN 200001

long long N, result, rows<:MAXN:>, cols<:MAXN:>;
pair<long, long> stars<:MAXN:>;

int main() <%
    ifstream input("input.txt");
    ofstream output("output.txt");

    input >> N;
    for (int i = 0; i < N; i++) <%
        input >> stars<:i:>.first >> stars<:i:>.second;
        rows<:stars<:i:>.first:>++;
        cols<:stars<:i:>.second:>++;
    %>

    for (int i = 0; i < N; i++)
        result += (rows<:stars<:i:>.first:> - 1) * (cols<:stars<:i:>.second:> - 1);

    output << result << endl;
    return 0;
%>