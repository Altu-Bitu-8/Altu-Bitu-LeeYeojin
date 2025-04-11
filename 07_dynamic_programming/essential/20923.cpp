// 아이디어
/* 
덱(deque): 양쪽에서 삽입.삭제를 할 수 있는 큐
m번 반복 덱의 쌓인 카드 수가 더 많으면 win
상대방 카드가 없어져도 win

// 순서
한 명씩 번갈아 가며 m번 진행 
1. 한 명이 카드를 내려 놓음
2. 판단 후 종치기
   - 맨 위 한 카드의 수가 5 -> 도도
   - 둘 다 비어있지 않고 맨 위 숫자 합이 5 -> 수연
3. 종 친 사람이 카드 가져가기
종료 조건 체크

// 승리 조건
1. 진행 중 자신의 덱이 0이면 상대방 win
2. m번 진행 후 카드 개수 기준 

// 쌓여있는 모습 
도도덱  도도그라운드덱  -  수연그라운드덱  수연덱
front  |    back   |  -  |   back    |  front
 ...   |    ...    |  -  |    ...    |  ... 
back   |   front   |  -  |   front   |  back
*/

#include <iostream>
#include <deque>

using namespace std;

/* 카드 합치기 */ 
//to_q로 from_g_q의 내용들 빼서 합치기 (to_q <- from_q)
void mergeCard(deque<int> &to_q, deque<int> &from_g_q){
    while (!from_g_q.empty()) {
        to_q.push_back(from_g_q.front()); // from_g_q에서 맨 앞의 원소 빼서 to_q로 뒤에서 push
        from_g_q.pop_front(); // 넣은 원소 pop  
    }
}

/* 벨 누르기 */  
void ringTheBell(int winner, deque<int> &winner_q, deque<int> &dodo_g, deque<int> &su_g){
    if(winner == 0){ // 도도가 이긴 경우 
        mergeCard(winner_q, su_g); //  도도의 덱으로 수연의 그라운드 덱의 내용 넣기  
        mergeCard(winner_q, dodo_g); // 도도의 덱으로 도도의 그라운드 덱의 내용 넣기
    }
    else if(winner == 1){ // 수연이가 이긴 경우
        mergeCard(winner_q, dodo_g); //  수연의 덱으로 도도의 그라운드 덱의 내용 넣기  
        mergeCard(winner_q, su_g); // 수연의 덱으로 수연의 그라운드 덱의 내용 넣기
    }
}

/* 게임 진행 */
void halliGalli(int m, deque<int> &dodo, deque<int> &su, deque<int> &dodo_g, deque<int> &su_g){
    // 누구 차례인지 표시 
    bool turn = true; // true: dodo, false:su 

    // 그라운드에 놓여진 맨 위 카드
    int df = 0, sf = 0;

    // m번 동안 진행 - 한 사람이 카드 내려놓는게 1번임!  
    while(m--){
        df = 0, sf = 0;  // 다시 초기화
        if(!dodo_g.empty()){ df = dodo_g.back(); }
        if(!su_g.empty()){ sf = su_g.back(); }
        
        if(turn){ // 도도 턴
             // 1. 맨 윗장 카드를 그라운드에 내려놓기 
            df = dodo.front(); // 도도 덱의 맨 위카드 = 그라운드 맨 위(back)카드  
            dodo.pop_front();  // 카드 들기 
            dodo_g.push_back(df);  // 내려놓기  

            // 2. 도도의 덱이 비었는지 확인  
            if(dodo.empty()){
                break;
            }

            // 3. 벨 울림 
            if((df == 5) || (sf == 5)){ // 맨 위 한 카드의 수가 5 -> 도도 
                ringTheBell(0, dodo, dodo_g, su_g);
            }
            else if((df!=0 && sf!=0) && (df + sf == 5)){ // 두 그라운드가 비어있지 않고 맨 위 숫자 합이 5 -> 수연
                ringTheBell(1, su, dodo_g, su_g);
            }

            // 4. turn 바꾸기기
            turn = false;
        }
        else{ // 수연 턴  
            // 1. 맨 윗장 카드를 그라운드에 내려놓기 
            sf = su.front(); // 수연 덱의 맨 위카드 = 그라운드 맨 위(back)카드 
            su.pop_front();  // 카드 들기
            su_g.push_back(sf); // 내려놓기 

            // 2. 수연의 덱이 비었는지 확인  
            if(su.empty()){
                break;
            }

            // 3. 벨 울림 
            if((df == 5) || (sf == 5)){ // 맨 위 한 카드의 수가 5 -> 도도 
                ringTheBell(0, dodo, dodo_g, su_g);
            }
            else if((df!=0 && sf!=0) && (df + sf == 5)){ // 두 그라운드가 비어있지 않고 맨 위 숫자 합이 5 -> 수연
                ringTheBell(1, su, dodo_g, su_g);
            }

            // 4. turn 바꾸기  
            turn = true;
        }
    }
}
 

int main() {
    
    int n, m; 
    cin >> n >> m;  // 카드 개수 & 진행 횟수 
    deque<int> dodo; deque<int> su;  // 도도와 수연의 덱
    deque<int> dodo_g; deque<int> su_g; // 도도와 수연의 그라운드 덱 

    // 입력
    // 각각 초기 덱 세팅 - 맨 아래 카드부터 맨위 카드까지 주어짐    
    int a, b;
    for(int i = 0; i < n; i++){
        cin >> a >> b;
        dodo.push_front(a); 
        su.push_front(b);
    }

    // 연산 
    halliGalli(m, dodo, su, dodo_g, su_g); 

    // 출력 - 게임이 끝난 경우
    if(dodo.size() > su.size()){  // 도도 승 
        cout <<  "do";
    }
    else if(dodo.size() < su.size()){  // 수연 승  
        cout <<  "su";
    }
    else{  // 비김 
        cout <<  "dosu";
    }

    return 0;
}