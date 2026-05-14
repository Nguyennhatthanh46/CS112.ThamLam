/*
Có n công việc, được phân công cho m máy như nhau thực hiện đồng thời. Hãy viết chương trình dùng kỹ thuật THAM LAM  để tìm một phương án phân công sao cho thời gian để các máy hoàn thành hết n công việc là ngắn nhất.
INPUT
Dòng đầu tiên chứa hai số nguyên không âm n và m, giá trị không quá 1 tỷ
Dòng thứ hai chứa n số nguyên dương x0, x1, …, xn-1 trong đó xi là thời gian cần thiết để một máy hoàn thành công việc i, giá trị không quá 1 tỷ

OUTPUT
Xuất trên một dòng n số nguyên dương y0, y1, …,yn-1, giá trị mỗi số trong đoạn [0, m-1] trong đó giá trị của yi là số thứ tự của máy được phân công để thực hiện công việc i.
LƯU Ý: Vì dùng Tham lam  nên chấp nhận sai số, nếu chênh lệch thời gian không lớn (<10%) thì hệ thống sẽ vẫn chấp nhận. GV đưa ví dụ không phải là trường hợp tối ưu để nhấn mạnh điểm này.

Input
8 3
79 1 80 59 75 51 7 29

Output
1 1 0 2 2 1 2 0
Một đáp án khác (theo kỹ thuật tham lam):
1 0 0 2 2 1 0 0
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> times(n);
    for (int i = 0; i < n; i++) cin >> times[i];

    vector<int> jobs(n);
    iota(jobs.begin(), jobs.end(), 0);
    sort(jobs.begin(), jobs.end(), [&](int a, int b) {
        return times[a] > times[b];
    });

    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    for (int k = 0; k < m; k++) pq.push({0, k});

    vector<int> assign(n);
    for (int idx : jobs) {
        auto [load, machine] = pq.top(); pq.pop();
        assign[idx] = machine;
        pq.push({load + times[idx], machine});
    }

    for (int i = 0; i < n; i++) {
        cout << assign[i] << ' ';
    }
    return 0;
}
