/*
Có n công việc, được phân công cho m máy như nhau thực hiện đồng thời. Hãy viết chương trình tìm một phương án phân công sao cho thời gian để các máy hoàn thành hết n công việc là ngắn nhất. 
(Thời gian bắt buộc phải ngắn nhất, không chấp nhận sai số)

INPUT
Dòng đầu tiên chứa hai số n và m (0<n,m<50)
Dòng thứ hai chứa n số nguyên dương x0, x1, …, xn-1 trong đó xi là thời gian cần thiết để một máy hoàn thành công việc i.

OUTPUT
Xuất trên một dòng n số nguyên dương y0, y1, …,yn-1, giá trị mỗi số trong đoàn [0, m-1] trong đó giá trị của yi là số thứ tự của máy được phân công để thực hiện công việc i.

VÍ DỤ

Input

8 3
722 985 380 129 966 310 56 374

Output
1 2 1 1 0 2 1 0
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
long long jobs[50];
long long machine_load[50];
int best_assignment[50];
int current_assignment[50];
long long min_makespan = -1;

void backtrack(int job_idx, long long current_max) {
    if (min_makespan != -1 && current_max >= min_makespan) {
        return;
    }

    if (job_idx == n) {
        if (min_makespan == -1 || current_max < min_makespan) {
            min_makespan = current_max;
            for (int i = 0; i < n; i++) {
                best_assignment[i] = current_assignment[i];
            }
        }
        return;
    }

    for (int j = 0; j < m; j++) {
        if (j > 0 && machine_load[j] == 0 && machine_load[j-1] == 0) continue;

        machine_load[j] += jobs[job_idx];
        current_assignment[job_idx] = j;

        backtrack(job_idx + 1, max(current_max, machine_load[j]));

        machine_load[j] -= jobs[job_idx];
        
        if (machine_load[j] == 0) break;
    }
}

int main() {
    cin >> n >> m;

    vector<pair<long long, int>> sorted_jobs(n);
    for (int i = 0; i < n; i++) {
        cin >> sorted_jobs[i].first;
        sorted_jobs[i].second = i;
    }

    sort(sorted_jobs.rbegin(), sorted_jobs.rend());
    
    for(int i = 0; i < n; i++) {
        jobs[i] = sorted_jobs[i].first;
    }

    backtrack(0, 0);

    int final_res[50];
    for (int i = 0; i < n; i++) {
        final_res[sorted_jobs[i].second] = best_assignment[i];
    }

    for (int i = 0; i < n; i++) {
        cout << final_res[i] << " ";
    }
    return 0;
}
