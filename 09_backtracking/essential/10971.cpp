//  아이디어
/* 
모든 도시를 방문(중복 불가) & n이 충분히 작음 => 백트래킹!
- 방문한 도시는 체크 필요 -> 체크배열 생성
- 비용이 0인 경우 가지치기
- 마지막 종점 = 출발지 
- min 업데이트
- [0][0] [0][1] ~ [1][0] ~ [n-1][n-1] 에서 출발하는 경우 차례대로 
*/

#include <iostream>
#include <vector>
#include <climits> // min 초기화 때문 

using namespace std;
int n;
int min_cost= INT_MAX;

void update_min_cost(vector<vector<int>> &w, vector<int> &choose){
    int cost = 0;
    // 마지막 도시-> 처음도시 로 가는 길이 있는지 확인
    if(w[choose[n-1]][choose[0]]==0){
        return; 
    }

    for(int i = 0; i < n; i++){
        cost += w[choose[i]][choose[i+1]];
    }
    if(cost < min_cost){
        min_cost = cost;
    }
}

void backtracking(int idx, vector<vector<int>> &w, vector<bool> &is_visited, vector<int> &choose){
    // 성공 조합이 만들어진 경우 min 업데이트
    if(idx >= n){
        choose[n] = choose[0]; // 마지막 종점 = 출발 도시
        update_min_cost(w, choose);
        return; 
    }

    for(int next_city = 0; next_city < n; next_city++){

        // 방문한 도시인지 체크  
        if(is_visited[next_city]){ 
            continue; 
        }
        // 길이 없는 도시인지 체크 
        if(idx >= 1 && w[choose[idx-1]][next_city]==0){
            continue; 
        }

        choose[idx] = next_city;
        is_visited[next_city] = true; 

        backtracking(idx + 1, w, is_visited, choose);
        is_visited[next_city] = false;  // 반환 
    }
}

int main(){
    //입력
    cin >> n;
    vector<vector<int>> w(n, vector<int>(n, 0));
    // 방문 도시 체크 배열
    vector<bool> is_visited(n, false);
    // 선택된 도시 방문 순서 조합 
    vector<int> choose(n+1, -1); // 마지막에 처음도시로 돌아와야 하므로 n+1 

    for(int i=0; i<n; i++){
        for(int j = 0; j < n; j++){
            cin >> w[i][j];
        }
    }

    //연산 
    // 출발 도시를 0으로 고정
    choose[0] = 0;
    is_visited[0] = true;
    backtracking(1, w, is_visited, choose);

    //출력
    cout << min_cost;

    return 0;
}