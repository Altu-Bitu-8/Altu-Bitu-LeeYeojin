#include <iostream>
#include <queue>

using namespace std;

// front(삭제) 1 2 3 4 back(삽입)

int main(){
    int N;
    cin >> N;

    queue<int> q;

    // 큐 생성
    for (int i = 1 ; i < N+1 ; i++){
        q.push(i);
    }

    int front; // q.pop()은 반환 값이 없으므로 q.front() 사용
    while (q.size() > 1) {
        q.pop();
        front = q.front();
        q.pop();
        q.push(front);
    }

    cout << q.front() << "\n";
    return 0;
} 

