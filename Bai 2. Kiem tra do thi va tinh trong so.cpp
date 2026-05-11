/*
Với một cách hiểu đơn giản ta có thể hình dung một đường đi (walk) trên đồ thị là một danh sách có thứ tự các đỉnh trong đó phần tử đầu tiên và phần tử cuối cùng của danh sách là cùng một đỉnh và tồn tại một cạnh nối giữa hai phần tử liên tiếp trong danh sách.

Cho một đơn đồ thị hữu hướng với cạnh có trọng số, và một số đường đi, kiểm tra xem các đường đi đó có đúng là đường đi hợp lý trên đồ thị hay không và tính độ dài của đường đi đó

INPUT:

Dòng đầu tiên chứa 02 số e và n, đây là số cạnh của đồ thị và số đường đi cần kiểm tra

e dòng tiếp theo, mỗi dòng chứa 02 chuỗi u, i và số nguyên dương x (cách nhau bởi khoảng trắng), thể hiện việc có một cạnh với độ dài là x nối từ đỉnh u sang đỉnh i trong đồ thị. Tên của các đỉnh chỉ bao gồm các ký tự trong bảng chữ cái.

n dòng tiếp theo, mỗi dòng chứa một dánh sách các chuỗi cách nhau bởi khoảng trắng, danh sách kết thúc khi gặp dấu chấm câu (.) Đây là các đỉnh trên đường đi cần kiểm tra.

OUTPUT:

Ứng với mỗi đường đi, nếu đó đúng là một đường đi trên đồ thị, xuất ra màn hình độ dài của đường đi đó trên một dòng. Nếu đó không phải là đường đi hợp lý, xuất ra chuỗi FALSE

THAM KHẢO  VỀ CẤU TRÚC DỮ LIỆU (C++)

- Danh sách kề có trọng số: chọn 1 trong 2 cách sau

Cách 1: map<string, set<pair<string, int>>. VD: A -->{(B,3), (C, 7)}, tức B kề với A và cạnh (A,B) có trọng số là 3
Cách 2: map<string, map<string, int>>//OK hơn

VÍ DỤ:

Input

8 3

K F 151

F L 199

L K 338

H L 8

K H 491

F H 803

K L 579

H K 299

F L F .

L K H F L .

L K F L .

Output
FALSE

FALSE

688
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {

    int e, n;
    cin >> e >> n;

    map<string, map<string, int>> graph;

    for (int i = 0; i < e; ++i) {
        string u, v;
        int x;
        cin >> u >> v >> x;
        graph[u][v] = x; 
    }

    for (int i = 0; i < n; ++i) {
        vector<string> path;
        string vertex;
        
        while (cin >> vertex && vertex != ".") {
            path.push_back(vertex);
        }

        if (path.empty()) continue;

        bool is_valid = true;
        long long total_weight = 0;

        for (size_t j = 0; j < path.size() - 1; ++j) {
            string current_node = path[j];
            string next_node = path[j+1];

            if (graph.count(current_node) > 0 && graph[current_node].count(next_node) > 0) {
                total_weight += graph[current_node][next_node];
            } else {
                is_valid = false;
                break;
            }
        }

        if (is_valid) {
            cout << total_weight << "\n";
        } else {
            cout << "FALSE\n";
        }
    }

    return 0;
}
