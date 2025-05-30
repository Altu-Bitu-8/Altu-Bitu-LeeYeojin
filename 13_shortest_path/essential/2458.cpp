// 모든 정점 쌍에 대해 경로가 있는지 확인해야함 
// => 플로이드 워셜
// 여기선 최단 경로 대신 경로의 존재 여부(비교 가능여부)를 확인!

#include <iostream>
#include <vector>

using namespace std;

// 플로이드-워셜 알고리즘 함수
// i < k, k < j 이면 i < j 임을 이용 
void floydWarshall(int n, vector<vector<bool>> &graph) {
    for (int k = 1; k <= n; k++) {         // 중간 정점
        for (int i = 1; i <= n; i++) {     // 출발 정점
            for (int j = 1; j <= n; j++) { // 도착 정점 
                if (graph[i][k] && graph[k][j])  // 둘다 true이면 
                    graph[i][j] = true;          // 비교 가능
            }
        }
    }
}

int main() {
    // 입력
    int n, m;
    cin >> n >> m;  // 학생 수, 비교 횟수

    vector<vector<bool>> graph(n+1, vector<bool>(n+1, false)); // 비교 정보 그래프

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = true; // a < b
    }

    // 연산
    floydWarshall(n, graph);

    // 정확한 순서를 알 수 있는 학생 수 계산
    int result = 0;
    for (int i = 1; i <= n; i++) {
        int count = 0; // 비교 가능 학생 수 카운트 
        for (int j = 1; j <= n; j++) {
            if (graph[i][j] || graph[j][i]) // 자신보다 크거나 작은 학생
                count++;
        }
        if (count == n - 1) // 모든 학생과의 비교 가능
            result++;
    }

    // 출력 
    cout << result << '\n';
    
    return 0;
}
