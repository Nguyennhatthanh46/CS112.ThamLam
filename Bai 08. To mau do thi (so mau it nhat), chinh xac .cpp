/*
Cho một đơn đồ thị vô hướng. Hãy tô màu cho đồ thị sao cho các đỉnh lân cận nhau không trùng màu với nhau và số màu phải dùng là tối thiểu.
Màu được sử dụng là hệ màu RGB 24 bit với tối đa hơn 16 triệu màu, các màu được đánh số từ 0 (màu đen #000000) đến 16777215 (màu trắng #FFFFFF).

INPUT:

Dòng đầu tiên chứa 02 số v, e, đây lần lượt là số đỉnh, số cạnh của đồ thị
Dòng tiếp theo chứa v chuỗi, mỗi chuỗi bao một hoặc nhiều ký tự hoa trong bảng chữ cái Tiếng Anh và cách nhau bởi khoảng trắng. 
Đây là danh sách tên các đỉnh của đồ thị.
e dòng tiếp theo, mỗi dòng chứa 02 chuỗi u và i (cách nhau bởi khoảng trắng), thể hiện việc có một cạnh nối giữa đỉnh u và đỉnh i trong đồ thị.

OUTPUT:

Xuất ra trên một dòng dãy v số nguyên, tương ứng là màu cho các đỉnh. 
Số đầu tiên tương ứng là màu cho đỉnh đầu tiên trong danh sách chuỗi các đỉnh ở dòng thứ 2 của input.

 
Ví dụ


Input
7 18
J R Q F L P I
L I
L F
F R
F J
L J
J R
J P
F Q
P L
F I
R P
I Q
Q L
F P
J I
I R
P Q
P I

Output
0 1 0 2 1 3 4
*/
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int v, e;
vector<vector<int>> adj;
vector<int> colors;

bool isSafe(int node, int c) {
    for (int neighbor : adj[node]) {
        if (colors[neighbor] == c) return false;
    }
    return true;
}

bool solve(int node, int m) {
    if (node == v) return true; 

    for (int c = 0; c < m; c++) { 
        if (isSafe(node, c)) {
            colors[node] = c;
            if (solve(node + 1, m)) return true;
            colors[node] = -1; 
        }
    }
    return false;
}

int main() {
    cin >> v >> e;
    vector<string> names(v);
    map<string, int> nameToIndex;
    for (int i = 0; i < v; i++) {
        cin >> names[i];
        nameToIndex[names[i]] = i;
    }
    adj.assign(v, vector<int>());
    for (int i = 0; i < e; i++) {
        string u, v_n; cin >> u >> v_n;
        adj[nameToIndex[u]].push_back(nameToIndex[v_n]);
        adj[nameToIndex[v_n]].push_back(nameToIndex[u]);
    }

    for (int m = 1; m <= v; m++) {
        colors.assign(v, -1);
        if (solve(0, m)) {
            for (int i = 0; i < v; i++) cout << colors[i] << " ";
            break;
        }
    }
    return 0;
}
