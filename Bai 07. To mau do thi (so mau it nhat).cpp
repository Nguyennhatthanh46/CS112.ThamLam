/*
Cho một đơn đồ thị vô hướng. Hãy tô màu cho đồ thị bằng PHƯƠNG PHÁP THAM LAM sao cho các đỉnh lân cận nhau không trùng màu với nhau và số màu phải dùng là nhỏ nhất có thể. Màu được sử dụng là hệ màu RGB 24 bit với tối đa hơn 16 triệu màu, các màu được đánh số từ 0 (màu đen #000000) đến 16777215 (màu trắng #FFFFFF).

INPUT:
Dòng đầu tiên chứa 02 số v, e, đây lần lượt là số đỉnh, số cạnh của đồ thị
Dòng tiếp theo chứa v chuỗi, mỗi chuỗi bao một hoặc nhiều ký tự hoa trong bảng chữ cái Tiếng Anh và cách nhau bởi khoảng trắng. Đây là danh sách tên các đỉnh của đồ thị.
e dòng tiếp theo, mỗi dòng chứa 02 chuỗi u và i (cách nhau bởi khoảng trắng), thể hiện việc có một cạnh nối giữa đỉnh u và đỉnh i trong đồ thị.

OUTPUT:
Xuất ra trên một dòng dãy v số nguyên, tương ứng là màu cho các đỉnh. 
Số đầu tiên tương ứng là màu cho đỉnh đầu tiên trong danh sách chuỗi các đỉnh ở dòng thứ 2 của input.


VÍ DỤ
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
#include <bits/stdc++.h>
using namespace std;

int main() {
    int v, e;
    cin >> v >> e;

    vector<string> vertexNames(v);
    map<string, int> nameToIndex;
    for (int i = 0; i < v; i++) {
        cin >> vertexNames[i];
        nameToIndex[vertexNames[i]] = i;
    }

    vector<vector<int>> adj(v);
    for (int i = 0; i < e; i++) {
        string uName, vName;
        cin >> uName >> vName;
        int u = nameToIndex[uName];
        int vIdx = nameToIndex[vName];
        adj[u].push_back(vIdx);
        adj[vIdx].push_back(u);
    }

    vector<int> resultColors(v, -1);

    for (int i = 0; i < v; i++) {
        set<int> neighborColors;
        for (int neighbor : adj[i]) {
            if (resultColors[neighbor] != -1) {
                neighborColors.insert(resultColors[neighbor]);
            }
        }

        int color = 0;
        while (neighborColors.count(color)) {
            color++;
        }
        resultColors[i] = color;
    }

    for (int i = 0; i < v; i++) {
        cout << resultColors[i] << " ";
    }
    cout << endl;
    return 0;
}
