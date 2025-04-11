// 아이디어
/* 
1번 컴퓨터로부터 접근 가능한 모든 노드(컴퓨터) 탐색
=> DFS or BFS! 
=> 접근만 가능하면 되니까 양방향 그래프! 
그리고 노드 방문할 때 마다 count!
*/

#include <iostream>

using namespace std;
#define START_COM 1 // 시작 컴퓨터 

int graph[101][101] = {0, };  // 간선 저장 배열 
bool visited[101] = {false, }; // 방문 기록 

// 깊이 탐색 함수 
void dfs(int n, int from, int &count){
    for(int i = 1; i <= n; i++){ // 노드가 1부터 시작하고 n까지 있음 주의!!! 
        if(graph[from][i] == 1 && !visited[i]){
            visited[i] = true;
            count++; 
            dfs(n, i, count); // 이 노드부터 다시 dfs! 
        }
    }
}

int main() {
    // 입력
    int n, m; 
    int count = 0; // 연결된 컴퓨터 수 
    cin >> n >> m;

    // 간선 저장 
    int a, b;
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        graph[a][b] = graph[b][a] = 1; // 양방향 그래프  
    }

    // 연산
    // 그래프 간선 저장
    visited[START_COM] = true; // 1번 컴퓨터 방문 처리 *잊지 말기
    dfs(n, START_COM, count); // 1번 컴퓨터부터 시작 

    // 출력
    cout << count;

    return 0;
}
