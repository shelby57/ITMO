/*
 На межрегиональной олимпиаде по программированию роботов соревнования проводятся в один тур и в необычном формате.
 Задачи участникам раздаются последовательно, а не все в самом начале тура, и каждая 𝑖 -я задача (1≤𝑖≤𝑛) становится доступной участникам в свой момент времени 𝑠𝑖.
 При поступлении очередной задачи каждый участник должен сразу определить, будет он ее решать или нет.
 В случае, если он выбирает для решения эту задачу, то у него есть 𝑡𝑖 минут на то, чтобы сдать ее решение на проверку,
 причем в течение этого времени он не может переключиться на решение другой задачи. Если же участник отказывается от решения этой задачи,
 то в будущем он не может к ней вернуться. В тот момент, когда закончилось время, отведенное на задачу, которую решает участник,
 он может начать решать другую задачу, ставшую доступной в этот же момент, если такая задача есть, или ждать появления другой залачи.
 При этом за правильное решение i-й задачи участник получает 𝑐𝑖 баллов.
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define int long long
using namespace std;
struct Event {
    int state = 0;
    int start = 0;
    int time = 0;
    int coins = 0;
    Event(int start, int time, int coins) : start(start), time(time), coins(coins){};
    explicit Event(int start) : start(start){};
    Event() = default;
    bool operator<(const Event &t) const {
        return start < t.start;
    }
};
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<Event> a;
    int s, t, c;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> s >> t >> c;
        a.emplace_back(s, t, c);
        mx = max(mx, s + t);
    }
    a.emplace_back(0, 0, 0);
    sort(a.begin(), a.end());
    a.emplace_back(mx, 0, 0);
    for (int i = 1; i < a.size(); i++) {
        size_t next = lower_bound(a.begin(), a.end(), Event(a[i].start + a[i].time)) - a.begin();
        a[i].state = max(a[i - 1].state, a[i].state);
        a[next].state = max(a[next].state, a[i].state + a[i].coins);
    }
    cout << a.back().state;
    return 0;
}