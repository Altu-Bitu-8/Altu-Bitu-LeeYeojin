// 추가 제출 
#include <iostream>
#include <deque>

using namespace std;

struct info { // 각 칸마다 내구도와 로봇 존재 여부 저장 구조체 
    int power; // 내구도 
    bool is_on = false; // 로봇의 유무 
};

// 1. 벨트를 한 칸 회전
void rotateBelt(deque<info> &belt, int n) {
    belt.push_front(belt.back()); // 벨트의 마지막 칸을 앞에 push
    belt.pop_back();              // 마지막 칸을 pop
    belt[n - 1].is_on = false;    // 로봇 내리기
}

// 2. 로봇을 움직일 수 있다면 한 칸 이동
void moveRobot(deque<info> &belt, int n) {
    for (int i = n - 2; i >= 0; i--) { // 배열 접근 가능 범위가 0~n-1인데 다음 칸과 비교하기 위해 0~n-2까지 반복
        // 현재 칸에 로봇이 존재하고, 다음 칸에 로봇이 없으며, 다음 칸에 내구도가 남아있을 때 이동 가능
        if (belt[i].is_on && !belt[i + 1].is_on && (belt[i + 1].power >= 1)) {
            belt[i].is_on = false; // 로봇 없음 표시
            belt[i + 1].is_on = true; // 로봇 있음 표시
            belt[i + 1].power--; // 내구도 1 감소 
        }
    }
    belt[n - 1].is_on = false; // 로봇 내리기
}

// 3. 올리는 칸에 로봇을 올릴 수 있다면 올리기
void putRobot(deque<info> &belt) {
    // 올리는 칸의 내구도가 남아 있으면
    if (belt[0].power >= 1) {
        belt[0].is_on = true; // 로봇 올리고 
        belt[0].power--; // 내구도 1 감소 
    }
}

// 4. 벨트의 내구도 체크
bool checkFinish(deque<info> &belt, int n, int k) {
    int cnt = 0; // 내구도 0인 칸의 개수
    for (int i = 0; i < 2 * n; i++) { // 전체 칸 확인 
        if (belt[i].power == 0) { // 각 칸의 내구도 확인 
            cnt++; // 내구도가 0인 경우 개수 1 증가  
        }
    }

    return cnt >= k; // 내구도가 0인 개수가 k보다 큰지 아닌지 bool값 반환 
}

int solution(deque<info> &belt, int n, int k) {
    // 1단계부터 시작
    int step = 1;
    while (true) {
        // 1. 벨트 한 칸 회전
        rotateBelt(belt, n);

        // 2. 로봇 이동
        moveRobot(belt, n);

        // 3. 로봇 올리기
        putRobot(belt);

        // 4. 내구도가 0인 칸의 개수가 k개 이상인지 체크
        if (checkFinish(belt, n, k)) {
            return step; // 종료조건 만족하는 경우 단계 반환 
        }
        step++; // 단계 1 증가 
    }
}

/**
 * [컨베이어 벨트 위의 로봇 문제]
 * 1. 벨트가 각 칸 위의 로봇과 함께 한 칸 회전
 * 2. 가장 먼저 벨트에 올라간 로봇부터, 벨트 회전 방향으로 한 칸 이동할 수 있다면 이동
 *    (이동가능: 이동하려는 칸에 로봇이 없고, 그 칸의 내구도가 1 이상이어야 함)
 * 3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇 올림
 * 4. 내구도가 0인 칸의 개수가 k개 이상이라면 과정 종료. 그렇지 않다면 1로 돌아감
 * -> 1 ~ 3까지가 1단계
 *
 * [문제 풀이]
 * 회전을 구현하기 위해, 양 끝에서 삽입과 삭제가 가능한 deque을 이용하여 풀이
 *
 * 1번 벨트 회전: 벨트의 마지막 원소를 벨트의 처음으로 이동
 * 2번 로봇 이동: 가장 먼저 올라간 로봇부터 고려해야 하므로 (내리는 위치 - 1)부터 (올리는 위치)까지 검사
 *               -> 로봇을 옮길 수 있으면 존재 여부 체크하고 내구도 감소
 * 3번 로봇 추가: 올리는 위치 칸의 내구도가 0이 아니라면 해당 칸의 로봇 존재 여부 체크 + 내구도 감소
 *
 * >> 주의: 칸 번호를 1번이 아닌 0번부터 시작하는 것으로 관리하고 있기 때문에, n번 칸이 아니라 n-1번 칸이 내리는 위치 <<
 */

int main()
{
    ios::sync_with_stdio(false); // 입출력 속도를 높이기 위함 
    cin.tie(NULL);
    cout.tie(NULL);

    // 입력
    int n, k; // 컨베이어 벨트의 길이, 내구도 0인 칸의 최대 개수
    cin >> n >> k; // 입력 받기 
    deque<info> belt(2 * n); // 컨베이어 벨트의 내구도와 로봇 존재 여부 저장

    // 벡트의 각 칸마다 내구도 입력, 로봇 존재 여부 초기화
    for (int i = 0; i < 2 * n; i++)
    {
        cin >> belt[i].power; // 내구도 저장 
    }

    // 연산 & 출력
    cout << solution(belt, n, k);
}

//-------------------------------------------------------------------------
// 다시 풀어본 풀이 
// 아이디어
/*
    컨베이어 벨트의 각 칸을 배열로 관리하고 이때 각 칸의 정보를 (내구도, 로봇 유무)쌍으로 관리
    순서대로 일어나는 과정을 각각의 함수로 작성하여 하나의 함수(conveyor())에서 호출 
    이때 반복문이 도는 횟수 카운트하다가, 마지막 4번 과정에서 종료 조건을 만족하는 경우 지금까지의 횟수 반환
    * n번자리에서 내리는데 우리는 0부터 시작할것이므로 n-1자리에서 내림에 주의!
*/
// #include <iostream>
// #include <vector>

// using namespace std;

// // 1. 한 칸 회전 함수
// void rotateBelt(int n, vector<pair<int, bool>> &a) {
//     pair<int, bool> last = a.back(); // 반복문에서 a[n-1]값 유실되니 저장해둠 
//     for (int i = 2 * n - 1; i > 0; --i) {
//         a[i] = a[i - 1]; // 다음 칸의 내구도와 로봇 유무에 이전 칸의 내구도와 로봇 유무 값 저장
//     }
//     a[0] = last; // 마지막 칸이 첫번째 칸 위치로 돌아오기 때문 
    
//     // 로봇이 n-1 위치에 오면 내림
//     if (a[n - 1].second) {
//         a[n - 1].second = false; // 로봇 없음 
//     }
// }

// // 2. 로봇 이동 함수
// void moveRobot(int n, vector<pair<int, bool>> &a) {
//     for (int i = n - 2; i >= 0; --i) { // 올라가는 위치부터 내리는 위치 전까지
//         // 로봇이 있고, 다음 칸에 로봇이 없으면서 내구도가 1이상인 경우
//         if (a[i].second && !a[i + 1].second && a[i + 1].first > 0) { 
//             a[i].second = false; // 로봇 없음 표시
//             a[i + 1].second = true; // 로봇 있음 표시 
//             a[i + 1].first--; // 내구조 1 감소 

//             // 이동 후 n-1 위치면 로봇 내려야 함
//             if (i + 1 == n - 1) {
//                 a[i + 1].second = false; // 로봇 없음 
//             }
//         }
//     }
// }

// // 3. 로봇 올리기 함수
// void putRobot(vector<pair<int, bool>> &a){
//     // 올리는 칸(a[0])의 내구도가 1이상이면 올림 
//     if(a[0].first >= 1 && !a[0].second) {
//         a[0].first--; // 내구도 1 감소 
//         a[0].second = true; // 로봇 있음
//     }
// }

// // 4. 내구도 체크 함수 
// int checkDurability(int &n, vector<pair<int, bool>> &a){
//     int num_zero = 0; // 내구도 0인 칸의 총 수 
//     for(int i = 0; i < 2 * n; i++){
//         if(a[i].first == 0){
//             num_zero++; //내구도 0인 개수 1 증가 
//         }
//     }
//     return num_zero; // 내구도 0인 칸의 총 수 반환 
// }

// // 컨베이어 벨트 작동 함수  
// int conveyor(int &n, int &k, vector<pair<int, bool>> &a){
//     int step = 0; // 단계 카운트 (반복문 돈 횟수) 
//     while(true){
//         step++; // 단계 카운트
//         // 1. 한 칸 회전
//         rotateBelt(n, a);
//         // 2. 로봇 이동 
//         moveRobot(n, a);
//         // 3. 로봇 올리기
//         putRobot(a);
//         // 4. 내구도 체크 
//         if(checkDurability(n, a) >= k){ // 내구도 0인 칸의 개수가 k이상이면 탈출 
//             break;
//         }
//     }
//     return step; // 종료된 시점의 단계 반환 
// }


// int main(){
//     // 입력 
//     int n, k; 
//     cin >> n >> k;
//     vector<pair<int, bool>> a(2*n); // 컨베이어 벨트의 각 칸 (칸 번호, 로봇 유무) 
//     for(int i = 0; i < 2*n; i++){
//         cin >> a[i].first; // 각 칸의 내구도 입력받아 저장 
//         a[i].second = false;  // 로봇 없음으로 초기화 
//     }

//     // 연산 & 출력
//     cout << conveyor(n, k, a);

//     return 0;
// }