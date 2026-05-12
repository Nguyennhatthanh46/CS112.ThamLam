/*
Cho một đồ thị đang được tô màu dang dở, hãy thực hiện việc chọn màu để tiếp tục tô cho đồ thị. 
Màu được sử dụng là hệ màu RGB 24 bit với tối đa hơn 16 triệu màu, các màu được đánh số từ 0 (màu đen #000000) đến 16777215 (màu trắng #FFFFFF).
Quy định là khi tô thì đỉnh không được trùng màu với các đỉnh lân cận của nó.
Khi chọn màu chỉ được sử dụng các màu đã tô trước đó, trừ khi những đỉnh lân cận với đỉnh cần tô đã chiếm hết những màu đã sử dụng trước thì mới được chọn màu mới. Khi tô màu dù là các màu đã có hay chọn màu mới, luôn chọn màu có thứ tự nhỏ nhất có thể chọn được.

INPUT:
Dòng đầu tiên chứa 03 số v, e, n đây lần lượt là số đỉnh, số cạnh của đồ thị và số lượng đỉnh cần xem xét.
Dòng tiếp theo chứa v chuỗi, mỗi chuỗi bao một hoặc nhiều ký tự hoa trong bảng chữ cái Tiếng Anh và cách nhau bởi khoảng trắng. Đây là danh sách tên các đỉnh của đồ thị.

e dòng tiếp theo, mỗi dòng chứa 02 chuỗi u và i (cách nhau bởi khoảng trắng), thể hiện việc có một cạnh nối giữa đỉnh u và đỉnh i trong đồ thị.
Dòng áp chót trong input chứa v số nguyên, đây tương ứng là màu của các đỉnh đã tô. Số nguyên đầu tiên là màu của đỉnh đầu tiên, đỉnh chưa tô màu sẽ có số tương ứng là -1
Dòng cuối cùng trong input chứa n chuỗi, đây là các đỉnh mà người chơi đang muốn xem xét để chọn màu.

OUTPUT:

Ứng với mỗi đỉnh cần xem xét thực hiện yêu cầu sau:
Nếu đỉnh đã có màu, kiểm tra màu đó có trùng với màu của các đỉnh lân cận hay không. Nếu không trùng xuất ra chuỗi TRUE trên một dòng
Nếu đỉnh chưa có màu hoặc đã có nhưng màu đó trùng với màu của một hoặc nhiều đỉnh lân cận thì chọn màu cho đỉnh theo đúng quy tắc và xuất ra màu đó trên một dòng.

Yêu cầu xem xét được thực hiện độc lập cho mỗi đỉnh. Kết quả xem xét các đỉnh trước hoàn toàn không ảnh hưởng gì đến các đỉnh sau. 

VÍ DỤ:

Input
8 5 4
Y N U L R I J F
R U
I L
Y R
N Y
F I
-1 2 1 1 1 -1 -1 2
Y R L L


Output
0
2
TRUE
TRUE

 Nên nhớ là khi chọn màu tô cho 1 đỉnh thì thử lại các màu đã tô. Ban đầu, chưa sử dụng màu 0, chỉ mới dùng màu 1 và 2.
Khi xét đỉnh Y hay R thì phải xét các màu đã dùng là 1, 2 trước. Chừng nào cả 2 màu này không được mới dùng màu mới. 
Với đỉnh Y thì màu 1, 2 không được nên chọn 0, Còn việc chọn màu 0 cho đỉnh Y không liên quan tới R, khi xét R mình vẫn xét trên đồ thị ban đầu. Theo cách hiểu này, Y=0, với R: thử tô màu 1 và không được (do kề U = 1) nên chọn màu 2.

*/
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Graph {
    int v, e;
    vector<string> vertexNames;
    map<string, int> nameToIndex;
    vector<vector<int>> adj;
    vector<int> initialColors;
    set<int> usedColorsPool; 
};

bool isFeasible(const Graph& g, int uIdx, int colorToTry, const vector<int>& currentColors) {
    for (int neighborIdx : g.adj[uIdx]) {
        if (currentColors[neighborIdx] == colorToTry) {
            return false;
        }
    }
    return true;
}

int findSpecialGreedyColor(const Graph& g, int uIdx) {
    for (int c : g.usedColorsPool) {
        if (isFeasible(g, uIdx, c, g.initialColors)) {
            return c;
        }
    }

    int c = 0;
    while (true) {
        if (g.usedColorsPool.find(c) == g.usedColorsPool.end()) {
            if (isFeasible(g, uIdx, c, g.initialColors)) {
                return c;
            }
        }
        c++;
    }
}

void solve() {
    int v, e, n;
    cin >> v >> e >> n;

    Graph g;
    g.adj.resize(v);
    g.initialColors.resize(v);

    for (int i = 0; i < v; i++) {
        string name; cin >> name;
        g.vertexNames.push_back(name);
        g.nameToIndex[name] = i;
    }

    for (int i = 0; i < e; i++) {
        string u, v_name; cin >> u >> v_name;
        int uIdx = g.nameToIndex[u];
        int vIdx = g.nameToIndex[v_name];
        g.adj[uIdx].push_back(vIdx);
        g.adj[vIdx].push_back(uIdx);
    }

    for (int i = 0; i < v; i++) {
        cin >> g.initialColors[i];
        if (g.initialColors[i] != -1) {
            g.usedColorsPool.insert(g.initialColors[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        string queryNode; cin >> queryNode;
        int uIdx = g.nameToIndex[queryNode];

        if (g.initialColors[uIdx] != -1 && isFeasible(g, uIdx, g.initialColors[uIdx], g.initialColors)) {
            cout << "TRUE" << endl;
        } else {
            cout << findSpecialGreedyColor(g, uIdx) << endl;
        }
    }
}

int main() {
    solve();
    return 0;
}
