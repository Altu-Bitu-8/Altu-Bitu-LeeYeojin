// 가중치와 시작점이 있는 최단 경로 => 다익스트라
// 시작점에서 해당 칸 까지의 거리를 담은 dist 배열을 0으로 초기화

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ci;
const int INF = 9*125*125; // 최소비용 최대값

// 방향: 북, 동, 남, 서
int dx[4] = {0, 1, 0, -1}; 
int dy[4] = {-1, 0, 1, 0};

// 다익스트라 
int lostRupee(int n, vector<vector<int>> &cave){
     vector<vector<int>> dist(n, vector<int>(n, INF)); // 거리 배열
    // 최소 비용을 위한 최소 힙 사용 
    priority_queue<pair<int, ci>, vector<pair<int, ci>>, greater<>> pq; // {비용, 위치}

    // 시작점 초기화 
    dist[0][0] = cave[0][0];
    pq.push({cave[0][0], {0, 0}});

    while (!pq.empty()) {
        int cost = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        if (cost > dist[x][y]) continue;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 갈 수 있는 모든 방향 체크 
            if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                int new_cost = cost + cave[nx][ny];
                if (new_cost < dist[nx][ny]) { // 새로운 최소비용 업데이트 
                    dist[nx][ny] = new_cost;
                    pq.push({new_cost, {nx, ny}});
                }
            }
        }
    }

    // 정점까지의 최소 비용 리턴 
    return dist[n - 1][n - 1];  
}

int main() {
    int n;
    int min_rupee = 0;
    int count = 0;

    while(true){
        cin >> n;
        if(n == 0){break;}
        count ++;
        
        vector<vector<int>> cave(n, vector<int>(n,0));
        
        for(int j = 0; j < n*n; j++){
            cin >> cave[j/n][j%n];
        }
         // 연산
        min_rupee = lostRupee(n, cave);
        cout << "Problem " << count << ": " << min_rupee << "\n";
    }
    return 0;
}