// 아이디어
/*
두 사람 사이에 관계 -> 노드와 간선이 있는 그래프!
부모-자식 관계이지만 촌수는 간선 수와만 관련! -> 양방향 그래프!
7과 3의 촌수? => 7에서 출발해 3까지의 간선 수!
=> BFS 
*/

#include <iostream> 
#include <queue>

using namespace std;

// 전역 변수 
int graph[101][101] = {0, };
int visited[101] = {false, };
int result; // 주어진 두 대상의 촌수 값  

// bfs로 촌 수 탐색 함수 
void bfs(int n, int from, int target){
    queue<pair<int, int>> q; // 노드 큐 (노드, 현재 촌수) 
    q.push({from, 0}); // 시작 정점 
    visited[from] = true; // 시작 노드 방문 표시 

    int now;
    int relation; 
    while(!q.empty()){
        now = q.front().first; // 현재 노드 
        relation = q.front().second; // 현재 촌 수 
        q.pop();

        // *인접 노드가 target인 경우 
        if(now == target){
            result = relation; // 현재 촌 수가 결과값
            return;
        }

        for(int i = 1; i <= n; i++){
            if(graph[now][i] == 1 && !visited[i]){
                visited[i] = true; // 방문 표시 
                q.push({i, relation +1}); // 촌 수 1 증가  
            }
        }

    }

}

int main() {
    // 입력
    int n, m;
    int first, second; // 촌 수 계산 대상 
    cin >> n;
    cin >> first >> second;
    cin >> m;

    // 연산
    int temp1, temp2;
    for(int i = 0; i < m; i++){ // 간선 정보 저장   
        cin >> temp1 >> temp2;
        graph[temp1][temp2] = graph[temp2][temp1] = 1;
    }

    bfs(n, first, second);

    // 출력
    if(result == 0){
        cout << "-1";
    } else{
        cout << result;
    }

    return 0;
}
