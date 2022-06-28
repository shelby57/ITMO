#include<bits/stdc++.h>
using namespace std;
main() {
    vector <string> s(101);
    s[0] = "((A0|B0)|(A0|B0))";
    for(int i = 1; i < 101; ++i) {
        string a_i = "A" + to_string(i);
        string b_i = "B" + to_string(i);
        string p1 = "((" + a_i + "|" + a_i + ")" + "|" +  "(" + b_i + "|" + b_i + "))";
        s[i] =  "((" + s[i - 1] + "|" + p1 + ")" + "|" + "(" + a_i + "|" + b_i + "))";
    }
    int n; 
    cin >> n;
    cout << s[n - 1];
}
