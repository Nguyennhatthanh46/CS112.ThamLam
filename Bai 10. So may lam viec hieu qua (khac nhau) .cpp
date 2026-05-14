/*
Có n công việc, được phân công cho m máy khác nhau thực hiện đồng thời. 
Hãy viết chương trình dùng kỹ thuật THAM LAM  để  tìm một phương án phân công sao cho thời gian để các máy hoàn thành hết n công việc là ngắn nhất.

INPUT

Dòng đầu tiên chứa hai số n và m
m dòng tiếp theo, mỗi dòng chứa n số nguyên dương x0, x1, …, xn-1 Trong đó số xi ở dòng thứ j là thời gian cần thiết để máy thứ j hoàn thành công việc i.

OUTPUT
Xuất trên một dòng n số nguyên dương y0, y1, …,yn-1, giá trị mỗi số trong đoạn [0, m-1] trong đó giá trị của yi là số thứ tự của máy được phân công để thực hiện công việc i.
LƯU Ý: Vì dùng Tham lam  nên chấp nhận sai số, nếu chênh lệch thời gian không lớn (<10%) thì hệ thống sẽ vẫn chấp nhận. GV đưa ví dụ không phải là trường hợp tối ưu để nhấn mạnh điểm này.

VÍ DỤ
Input

8 3
79 1 80 59 75 51 7 29
49 71 44 55 22 61 31 88
59 28 9 19 18 60 54 68

Output
1 0 2 2 2 0 0 0
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<long long>> cost(m, vector<long long>(n));
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            cin >> cost[j][i];
        }
    }

    vector<long long> load(m, 0);
    vector<int> assignment(n);

    for (int i = 0; i < n; i++) {
        int best_m = 0;
        
        long long min_finish_time = load[0] + cost[0][i];

        for (int j = 1; j < m; j++) {
            long long current_finish_time = load[j] + cost[j][i];
            
            if (current_finish_time < min_finish_time) {
                min_finish_time = current_finish_time;
                best_m = j;
            }
        }

        assignment[i] = best_m;
        load[best_m] += cost[best_m][i];
    }

    for (int i = 0; i < n; i++) {
        cout << assignment[i] << " ";
    }
    cout << endl;

    return 0;
}
