/*
Có một người đưa thư cần tìm đường đi qua tất cả các đỉnh trên đồ thị sao cho mỗi đỉnh chỉ đi duy nhất một lần và trở về vị xuất phát ban đầu.
Hãy viết chương trình tìm đường đi đáp ứng yêu cầu đó và có độ dài tối thiểu. YÊU CẦU: TÌM ĐƯỜNG ĐI TỐI ƯU THẬT SỰ, CHO KẾT QUẢ CHÍNH XÁC. 

INPUT:

Dòng đầu tiên chứa 2 số e và chuỗi s, đây là số cạnh của đồ thị và tên của đỉnh mà từ đó người đưa thư bắt đầu đi.

e dòng tiếp theo, mỗi dòng chứa 02 chuỗi u, i và số nguyên dương x (cách nhau bởi khoảng trắng), thể hiện việc có một cạnh với độ dài là x nối từ đỉnh u sang đỉnh i trong đồ thị. 
Tên của các đỉnh chỉ bao gồm các ký tự trong bảng chữ cái.

OUTPUT:

Xuất ra danh sách các đỉnh trên đường đi cách nhau bởi khoảng trắng.
VÍ DỤ:
Input
20 L

L P 780
T P 90
P L 76
M T 300
L H 218
L T 994
P H 851
M P 648
H T 591
H M 246
T M 194
T H 186
H L 328
P M 723
P T 65
H P 807
L M 706
T L 75
M L 133
M H 382

Output
L H M T P L
*/


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <climits>

using namespace std;

map<string, map<string, int>> graph;
map<string, bool> visited;
set<string> unique_nodes;

vector<string> current_path;
vector<string> best_path;
int min_total_cost = INT_MAX;
string start_node;
int n;

void Backtrack(string current_node, int step, int current_cost) {
    if (current_cost >= min_total_cost) return;

    if (step == n) {
        if (graph[current_node].count(start_node) > 0) {
            int total_cost = current_cost + graph[current_node][start_node];
            if (total_cost < min_total_cost) {
                min_total_cost = total_cost;
                best_path = current_path;
            }
        }
        return;
    }

    for (const string& next_node : unique_nodes) {
        if (!visited[next_node] && graph[current_node].count(next_node) > 0) {
            visited[next_node] = true;
            current_path.push_back(next_node);

            Backtrack(next_node, step + 1, current_cost + graph[current_node][next_node]);

            visited[next_node] = false;
            current_path.pop_back();
        }
    }
}

int main() {
    int e;
    cin >> e >> start_node;

    for (int i = 0; i < e; ++i) {
        string u, v;
        int weight;
        cin >> u >> v >> weight;
        graph[u][v] = weight;
        unique_nodes.insert(u);
        unique_nodes.insert(v);
    }

    n = unique_nodes.size();

    visited[start_node] = true;
    current_path.push_back(start_node);

    Backtrack(start_node, 1, 0);

    if (min_total_cost != INT_MAX) {
        best_path.push_back(start_node); 
        for (size_t i = 0; i < best_path.size(); ++i) {
            cout << best_path[i] <<  " ";
        }
        cout << "\n";
    }

    return 0;
}
