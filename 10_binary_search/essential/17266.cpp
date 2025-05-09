#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 최대 거리차 구하기 
int maxDistance(int &n, int &m, vector<int> &light){
    // 양끝은 거리가 2h가 아닌 h이상이여야 함 
    // 그러나 나중에 ceil(/2)로 h를 구할 것이므로 
    // 양 끝의 거리*2로 맞춰주자 
    int max_dist = 2 * max(light[0], n - light[m-1]);
    int dist = 0;

    // 가로등 사이 거리 
    for(int i = 0; i < m-1; i++){
        dist = light[i+1]-light[i];
        if(dist > max_dist){
            max_dist = dist;
        }
    }
    return max_dist; 
}

// 최소 높이 구하기 
int findH(int &n, int &m, vector<int> &light){
    int max_dist = maxDistance(n, m, light);
    return (max_dist + 1) / 2; // 홀수일 경우 올림하기 위해 +1
}

int main(){
    // 입력
    int n, m;
    cin >> n >> m;
    vector<int> light(m,0);
    for(int i=0; i < m; i++){
        cin >> light[i];
    }

    // 연산 & 출력 
    cout << findH(n, m, light);

    return 0;
}