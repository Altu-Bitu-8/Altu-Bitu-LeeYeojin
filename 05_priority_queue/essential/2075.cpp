// n번째 큰 수 - 아이디어

// 메모리를 생각해야하는 문제
// 큐에는 큰 수 딱 n개만 저장되도록 하면 됨!
// min-heap으로 만들고 n개까지 채운 다음, 하나 push하면 다시 가장 작은 top을 pop()하기 
// 다 입력 받으면 큐에 딱 n개만 있을 것이고 pop하면 n번째로 큰 수!!

#include <iostream>
#include <queue>

using namespace std;

int main() {
    // 빠르게
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 입력
    int n, x;
    priority_queue<int> num_q;
    cin >> n;

    // 연산
    // 첫 줄 입력 큐에 push
    for(int i = 0; i < n; i++){
        cin >> x;
        num_q.push(-x); // min-heap을 만들기 위해 음수 입력  
    }

    // 그 다음 분턴 하나 push하면 하나 pop 
    for(int m = 1; m < n; m++){
        for(int j = 0; j < n; j++){
            cin >> x;
            num_q.push(-x); 
            num_q.pop();
        }
    }

    // 출력
    cout << -(num_q.top());  // -붙여서 다시 원래대로  

    return 0;
}
