/*
Đơn đồ thị hữu hướng (simple complete dirgraph) đầy đủ là một đồ thị mà trong đó giữa hai đỉnh u, v bất kỳ sẽ được nối với nhau 
bởi  duy nhất một cặp cạnh (một cạnh có hướng từ u sang v và cạnh còn lại từ v sang u).

Cho một đồ thị hãy kiểm tra xem đồ thị đó có đầy đủ hay không

INPUT:

Dòng đầu tiên chứa số e, đây là độ dài của input, cho biết số cạnh có trong đồ thị

e dòng tiếp theo, mỗi dòng chứa 02 chuỗi u và i (cách nhau bởi khoảng trắng), thể hiện việc có một cạnh nối từ đỉnh u sang đỉnh i trong đồ thị. Do đây là đơn đồ thị nên nếu như có nhiều dòng cùng chứa hai chuỗi u, i giống nhau vẫn chỉ xem như có một cạnh nối từ u sang i.

 

OUTPUT:

Xuất ra màn hình chuỗi TRUE nếu đồ thị là đầy đủ. Nếu không xuất ra chuỗi FALSE

 

VÍ DỤ:
Input1
6

K I
O I
I K
K O
I O
O K

Output1
TRUE

Input2
6

K I
O I
I K
K O
I O
O I

Output2
FALSE

*/
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    long long Canh; 
    if (!(cin >> Canh)) return 0;

    set<string> tapHopDinh;       
    set<pair<string, string>> tapHopCanh; 

    for (int i = 0; i < Canh; i++) {
        string dinhXuatPhat, dinhDich; 
        cin >> dinhXuatPhat >> dinhDich; 

        if (dinhXuatPhat != dinhDich) {
            tapHopDinh.insert(dinhXuatPhat);
            tapHopDinh.insert(dinhDich);
            tapHopCanh.insert({dinhXuatPhat, dinhDich}); 
        }
    }

    long long soDinh = tapHopDinh.size();         
    long long soCanhHopLe = tapHopCanh.size();    
    
    long long soCanh = soDinh * (soDinh - 1); 

    if (soCanhHopLe == soCanh && soDinh > 0) {
        cout << "TRUE";
    } else {
        cout << "FALSE";
    }

    return 0;
}
