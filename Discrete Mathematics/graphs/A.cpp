#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;
bool f(vector <string> &base, int p1, int p2) {
    if(p1 > p2) {
        swap(p1, p2);
    }
    return base[p1][p2] == '1';
}
int main() {
    ios ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    string s;
    vector <vector <bool>> base(n, vector <bool> (n, false));
    vector <int> queue;
    for(int i = 0; i < n; ++i) {
        queue.push_back(i);
    }
    char x;
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < i; ++j) {
            cin >> x;
            base[i][j] = (x == '1');
            base[j][i] = (x == '1');
        }
    }
    int pos = 0;
    for(int k = 0; k < n * (n - 1); ++k) {
        if (!base[queue[pos]][queue[pos + 1]]) {
            int i = pos + 2;
            while (!base[queue[pos]][queue[i]] || !base[queue[pos + 1]][queue[i + 1]]) {
                ++i;
            }
            reverse(queue.begin() + pos + 1, queue.begin() + i + 1);
        }
        queue.push_back(queue[pos]);
        pos++;
    }
    for(int i = pos; i < queue.size(); ++i)
        cout << queue[i] + 1 << " ";
    return 0;
}
