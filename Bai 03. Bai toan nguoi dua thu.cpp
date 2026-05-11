/*
VÍ DỤ Có một người đưa thư cần tìm đường đi qua tất cả các đỉnh trên đồ thị (đầy đủ) sao cho mỗi đỉnh chỉ đi duy nhất một lần và trở về vị xuất phát ban đầu. 
Hãy viết chương trình tìm đường đi đáp ứng yêu cầu đó và có độ dài càng ngắn càng tốt sử dụng thuật giải heuristic
Ý tưởng thuật giải heuristic: Hi vọng khi đi trên những đoạn đường ngắn nhất thì cuối cùng ta sẽ có một hành trình ngắn nhất. 

INPUT:
- Dòng đầu tiên chứa số e và chuỗi s, đây là số cạnh của đồ thị và tên của đỉnh mà từ đó người đưa thư bắt đầu đi.
- e dòng tiếp theo, mỗi dòng chứa 02 chuỗi u, i và số nguyên dương x (cách nhau bởi khoảng trắng), thể hiện việc có một cạnh với độ dài là x nối từ đỉnh u sang đỉnh i trong đồ thị. Tên của các đỉnh chỉ bao gồm các ký tự trong bảng chữ cái.

OUTPUT:
Xuất ra danh sách các đỉnh trên đường đi cách nhau bởi khoảng trắng.
LƯU Ý:  chấp nhận sai số, nếu chênh lệch thời gian không lớn (<10%) thì hệ thống sẽ vẫn chấp nhận. GV đưa ví dụ không phải là trường hợp tối ưu để nhấn mạnh điểm này.

VÍ DỤ
Input
20 N

L V 909
N R 117
L N 695
V N 76
R H 851
L R 34
V H 111
H N 152
V R 900
N L 554
R N 324
R V 250
H R 871
N H 603
L H 978
H V 581
N V 141
R L 415
V L 141
H L 496

Output

N L R V H N

Giai thích thêm
Nếu giải theo Greedy search (tham lam) như gợi ý trên lớp thì đáp án là :
N --117-->R -- 250 --> V --111-->H -- 496 -->L --695--> N, khi đó chiều dài đường đi là 1669
Còn đáp án trong ví dụ có chiều dài đường đi là 1101 (ngắn hơn bên trên)
*/
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <climits>

using namespace std;

map<string, map<string, int>> graph;

struct Solution {
    vector<string> path;
};

string SELECT(const set<string>& P, const string& current_node) {
    string best_next = "";
    int min_weight = INT_MAX;

    for (const string& candidate : P) {
        if (graph[current_node].count(candidate) > 0) {
            int weight = graph[current_node][candidate];
            if (weight < min_weight) {
                min_weight = weight;
                best_next = candidate;
            }
        }
    }
    return best_next;
}

bool FEASIBLE(const Solution& solution, const string& x) {
    return x != ""; 
}

void UNION_FUNC(Solution& solution, const string& x) {
    solution.path.push_back(x);
}

Solution GREEDY(set<string>& P, int n, string start_node) {
    Solution solution;
    
    string current_node = start_node;
    UNION_FUNC(solution, current_node);
    P.erase(current_node);
    
    for (int i = 1; i < n; i++) {
        string x = SELECT(P, current_node);
        
        P.erase(x);
        
        if (FEASIBLE(solution, x)) {
            UNION_FUNC(solution, x);
            current_node = x;
        }
    }
    
    UNION_FUNC(solution, start_node);
    
    return solution;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int e;
    string start_node;
    if (!(cin >> e >> start_node)) return 0;

    set<string> P;

    for (int i = 0; i < e; ++i) {
        string u, v;
        int weight;
        cin >> u >> v >> weight;
        graph[u][v] = weight;
        
        P.insert(u);
        P.insert(v);
    }

    int n = P.size();

    Solution ket_qua = GREEDY(P, n, start_node);

    for (size_t i = 0; i < ket_qua.path.size(); ++i) {
        cout << ket_qua.path[i] << (i == ket_qua.path.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
