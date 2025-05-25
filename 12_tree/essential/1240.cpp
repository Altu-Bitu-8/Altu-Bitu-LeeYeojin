// 아이디어
/*
    노드가 연결되고 사이클X, 방향x =>트리, 양방향
    노드 간의 경로 찾기 => 탐색 
    깊게깊게 탐색하는 dfs로 풀어보자
    최대한 깊게 탐색 (다음 노드에서 dfs, 또 다음 노드에서 dfs)
    vector, 재귀함수로 구현 
*/
#include <iostream>
#include <vector>

using namespace std;

// ex) (2,1,2) -> tree[2] ={(1,2)}, tree[1] ={(2,2)}
vector<pair<int, int>> tree[1001]; // {연결된 노드, 거리}쌍들을 vector로 저장 
int result; // 결과 
bool found = false; 
 
// 깊이 탐색
void dfs(int now, int target, int dist, vector<bool> &visited){
    // 이미 찾은 경우라면 바로 리턴
    if (found) return;

    // 도달한 경우 
    if(now == target){
        result = dist;
        found = true;
        return;
    }

    // 아직 도달 못함, 다음 노드에서 다시 dfs
    visited[now] = true; // 방문 표시 
    for(int i =0; i < tree[now].size(); i++){ // 모든 연결된 노드에 대해 
        int next_node = tree[now][i].first; // 다음 노드
        int next_node_dis = tree[now][i].second; // 다음 노드와의 거리
        if(!visited[next_node]){ //방문하지 않은 노드에 대해
            dfs(next_node, target, dist + next_node_dis, visited); // 다음 노드에서 다시 dfs
        }
    }
}

int main() {
    //입력 
    int n, m; // 노드 개수, 구해야하는 노드 쌍 개수
    cin >> n >> m;
    
    for(int i=0; i< n-1; i++){
        int x, y, z;
        cin >> x >> y >>z;
        tree[x].push_back({y, z});
        tree[y].push_back({x, z}); // 무방향이므로 
    }

    for(int j =0; j < m; j++){
        result =0; //초기화
        found = false; // 초기화
        vector<bool> visited(1001, false); // 선언할 때 초기화됨
        int a, b;
        cin >> a >> b;
        dfs(a, b, 0, visited); // 연산 
        cout << result << "\n"; // 출력 
    }
    return 0;
}