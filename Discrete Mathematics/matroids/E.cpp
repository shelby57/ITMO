#include <algorithm>
#include <fstream>
#include <set>
#include <vector>

using namespace std;
struct node {
    int w = 0;
    int ind = 0;
    node(int w, int ind) : w(w), ind(ind){};
    node() = default;
};

bool comp1(const node &x, const node &y) {
    return x.ind < y.ind;
}

bool comp2(const node &x, const node &y) {
    return x.w > y.w;
}

int main() {
    ifstream fin("cycles.in");
    ofstream fout("cycles.out");
    int n, m;
    fin >> n >> m;
    vector<node> vertex(n);
    for (int i = 0; i < n; ++i) {
        fin >> vertex[i].w;
        vertex[i].ind = i;
    }
    stable_sort(vertex.begin(), vertex.end(), comp2);
    int len;
    vector<set<int>> cycles(m);
    for (int i = 0; i < m; ++i) {
        fin >> len;
        int p;
        for (int j = 0; j < len; ++j) {
            fin >> p;
            cycles[i].insert(p - 1);
        }
    }
    fin.close();
    vector<int> base;
    for (const auto &i: vertex) {
        base.push_back(i.ind);
        bool ok = true;
        for (const auto &cycle: cycles) {
            if (cycle.size() > base.size()) {
            }
            int count = 0;
            for (int b: base) {
                if (cycle.find(b) != cycle.end()) {
                    count++;
                }
            }
            if (count == cycle.size()) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            base.pop_back();
        }
    }
    sort(vertex.begin(), vertex.end(), comp1);
    int result = 0;
    for (int b: base) {
        result += vertex[b].w;
    }
    fout << result << endl;
    fout.close();
    return 0;
}