// 화장실의 규칙 - 아이디어

// 1. m개의 큐?로 나누기
// 우선 순위 비교 순서 (최대 m명의 사람을 비교)
// - 근무 일수 큰 순서 대로 정렬
//    - 같은 경우 ⇒ 급한 정도가 높은 순서 대로 정렬
//        - 같은 경우 ⇒ 라인의 번호가 작은 순서대로
// pop한 것의 인덱스가 데카의 번호이면 stop하고 지금 몇번째 인지 반환

// priority_queue와 cmp 구조체를 사용해보자!

#include <iostream>
#include <queue>
#include <vector>

using namespace  std;

// worker 구조체 정의
struct worker {
    int order, line, d, t;
    worker(int num, int l, int d, int t) : order(num), line(l), d(d), t(t) {} // 생성자 정의
};

// 우선 순위 구조체  
struct cmp {
    bool operator()(const worker &a,const worker &b){ // true: a가 b보다 낮은 우선순위
        if(a.d != b.d){
            return a.d < b.d; // d가 큰 것이 우선순위 높음
        } 
        if(a.t != b.t){
            return a.t < b.t;  // t가 큰 것이 우선 순위 높음
        }
        return a.line > b.line; // line이 작은 것이 우선 순위 높음 
    }
};

// m개의 줄(큐) 만들기   
void makeLines(int n, int m, queue<worker> &worker_q, vector<queue<worker>> &lines_q){
    int line_num = 0;
    for(int j = 0; j < n; j++){
        worker temp = worker_q.front();
        worker_q.pop();
        temp.line = line_num; // 사원의 라인 번호 저장
        lines_q[line_num].push(temp); // 해당 라인 큐에 사원 추가  
        line_num = (line_num + 1) % m; // 다음 줄로 이동  
    }
}

// 선두들을 비교하며 화장실 이용
int nextPerson(int n, int m, int k,
                queue<worker> &worker_q, 
                vector<queue<worker>> &lines_q, 
                priority_queue<worker, vector<worker>, cmp> &front_people_q){

    // 1. 초기 - 각 라인 당 한 명씩 선두 큐에 push
    for(int l = 0; l < m; l++){
        if(!lines_q[l].empty()){  // 해당 라인에 사람이 있는 경우
            front_people_q.push(lines_q[l].front());  // 해당 라인의 선두를 선두 큐에 push 
            lines_q[l].pop();
        }
    }

    int count = 0; // 현재 화장실 이용한 사람 수 

    // 2. 선두 큐에서 pop 하고 pop한 사람의 라인(큐)에서 그 다음 선두 push
    while(!front_people_q.empty()){

        // 2.1 선두 큐에서 한 명 pop
        worker user = front_people_q.top(); 
        front_people_q.pop();  

        // 2.2 데카 차례인 경우  
        if(user.order == k){ 
            break;
        }

        count++; 

        // 2.3 pop한 사람과 같은 줄 큐에 다음번 사람이 있다면, 선두 큐에 push
        if(!lines_q[user.line].empty()) {
            front_people_q.push(lines_q[user.line].front());
            lines_q[user.line].pop();
        }
    }

    return count; 
}


int main(){
    // 빠르게
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 입력
    int n, m, k, d, t;
    cin >> n >> m >> k;

    queue<worker> worker_q; // 사원 큐: 도착순서대로   
    vector<queue<worker>> lines_q(m);  // 라인 큐: (라인번호, 사원 구조체) 
    priority_queue<worker, vector<worker>, cmp> front_people_q;  // 선두 큐: 선두에 있는 사람들  

    // 각 사원들의 D와 T값 저장 
    for(int i=0; i < n; i++){
        cin >> d >> t;
        worker_q.push(worker(i, 0 ,d, t));
    }
    
    // m개의 줄(큐) 만들기
    makeLines(n, m, worker_q, lines_q);

    // 선두들을 비교하며 화장실 이용
    int result = nextPerson(n, m, k, worker_q, lines_q, front_people_q);
 
    // 출력
    cout << result;

    return 0;
}