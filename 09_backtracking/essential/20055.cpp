// 아이디어
/*
    컨베이어 벨트의 각 칸을 배열로 관리하고 이때 각 칸의 정보를 (내구도, 로봇 유무)쌍으로 관리
    순서대로 일어나는 과정을 각각의 함수로 작성하여 하나의 함수(conveyor())에서 호출 
    이때 반복문이 도는 횟수 카운트하다가, 마지막 4번 과정에서 종료 조건을 만족하는 경우 지금까지의 횟수 반환
    * n번자리에서 내리는데 우리는 0부터 시작할것이므로 n-1자리에서 내림에 주의!
*/
#include <iostream>
#include <vector>

using namespace std;

// 1. 한 칸 회전 함수
void rotateBelt(int n, vector<pair<int, bool>> &a) {
    pair<int, bool> last = a.back(); // 반복문에서 a[n-1]값 유실되니 저장해둠 
    for (int i = 2 * n - 1; i > 0; --i) {
        a[i] = a[i - 1]; // 다음 칸의 내구도와 로봇 유무에 이전 칸의 내구도와 로봇 유무 값 저장
    }
    a[0] = last; // 마지막 칸이 첫번째 칸 위치로 돌아오기 때문 
    
    // 로봇이 n-1 위치에 오면 내림
    if (a[n - 1].second) {
        a[n - 1].second = false; // 로봇 없음 
    }
}

// 2. 로봇 이동 함수
void moveRobot(int n, vector<pair<int, bool>> &a) {
    for (int i = n - 2; i >= 0; --i) { // 올라가는 위치부터 내리는 위치 전까지
        // 로봇이 있고, 다음 칸에 로봇이 없으면서 내구도가 1이상인 경우
        if (a[i].second && !a[i + 1].second && a[i + 1].first > 0) { 
            a[i].second = false; // 로봇 없음 표시
            a[i + 1].second = true; // 로봇 있음 표시 
            a[i + 1].first--; // 내구조 1 감소 

            // 이동 후 n-1 위치면 로봇 내려야 함
            if (i + 1 == n - 1) {
                a[i + 1].second = false; // 로봇 없음 
            }
        }
    }
}

// 3. 로봇 올리기 함수
void putRobot(vector<pair<int, bool>> &a){
    // 올리는 칸(a[0])의 내구도가 1이상이면 올림 
    if(a[0].first >= 1 && !a[0].second) {
        a[0].first--; // 내구도 1 감소 
        a[0].second = true; // 로봇 있음
    }
}

// 4. 내구도 체크 함수 
int checkDurability(int &n, vector<pair<int, bool>> &a){
    int num_zero = 0; // 내구도 0인 칸의 총 수 
    for(int i = 0; i < 2 * n; i++){
        if(a[i].first == 0){
            num_zero++; //내구도 0인 개수 1 증가 
        }
    }
    return num_zero; // 내구도 0인 칸의 총 수 반환 
}

// 컨베이어 벨트 작동 함수  
int conveyor(int &n, int &k, vector<pair<int, bool>> &a){
    int step = 0; // 단계 카운트 (반복문 돈 횟수) 
    while(true){
        step++; // 단계 카운트
        // 1. 한 칸 회전
        rotateBelt(n, a);
        // 2. 로봇 이동 
        moveRobot(n, a);
        // 3. 로봇 올리기
        putRobot(a);
        // 4. 내구도 체크 
        if(checkDurability(n, a) >= k){ // 내구도 0인 칸의 개수가 k이상이면 탈출 
            break;
        }
    }
    return step; // 종료된 시점의 단계 반환 
}


int main(){
    // 입력 
    int n, k; 
    cin >> n >> k;
    vector<pair<int, bool>> a(2*n); // 컨베이어 벨트의 각 칸 (칸 번호, 로봇 유무) 
    for(int i = 0; i < 2*n; i++){
        cin >> a[i].first; // 각 칸의 내구도 입력받아 저장 
        a[i].second = false;  // 로봇 없음으로 초기화 
    }

    // 연산 & 출력
    cout << conveyor(n, k, a);

    return 0;
}