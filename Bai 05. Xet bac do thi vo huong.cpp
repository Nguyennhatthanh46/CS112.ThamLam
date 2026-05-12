/*
Cho một đơn đồ thị vô hướng, cho biết mỗi đỉnh trong đồ thị có bậc bao nhiêu.

 
INPUT:

Dòng đầu tiên chứa 02 số v, e, đây lần lượt là số đỉnh, số cạnh của đồ thị

Dòng tiếp theo chứa v chuỗi, mỗi chuỗi bao một hoặc nhiều ký tự hoa trong bảng chữ cái Tiếng Anh và cách nhau bởi khoảng trắng. Đây là danh sách tên các đỉnh của đồ thị.

e dòng tiếp theo, mỗi dòng chứa 02 chuỗi u và i (cách nhau bởi khoảng trắng), thể hiện việc có một cạnh nối giữa đỉnh u và đỉnh i trong đồ thị.

OUTPUT:

Xuất ra trên một dòng bậc của mỗi đỉnh, thứ tự các đỉnh ứng với thứ tự chúng xuất hiện trong dòng thứ 2 của input.

VÍ DỤ:
INPUT
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

OUTPUT
5 4 4 6 5 6 6
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    int v, e;
    cin >> v >> e;

    vector<string> vertices(v);
    unordered_map<string, int> degree;

    for (int i = 0; i < v; i++) {
        cin >> vertices[i];
        degree[vertices[i]] = 0;
    }

    for (int i = 0; i < e; i++) {
        string u, i_vertex;
        cin >> u >> i_vertex;
        degree[u]++;
        degree[i_vertex]++;
    }

    for (int i = 0; i < v; ++i) {
        cout << degree[vertices[i]]<<" ";
    }
    cout << "\n";

    return 0;
}
