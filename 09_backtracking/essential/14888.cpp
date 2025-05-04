//  아이디어
/* 
n개의 숫자와 n-1개의 연산자 주어짐 
연산은 앞에서 부터 순서대로 
가능한 모든 식의 조합에서 max와 min찾기
-> n의 범위가 작으므로 브루트 포스
-> max와 min업데이트 해가면서 찾기 
* 연산자 개수 2101 -> ++-% 이런식으로 연산자 배열로 만들어 저장 
*/

#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> num; // 수 저장 
vector<char> oper;  // 연산자 저장 
int min_res=1e9, max_res=-1e9; 

void update_min_max(vector<int> &choose_oper){
    int res = num[0];
    for(int i = 1; i < n; i++){
        switch(oper[choose_oper[i-1]]){
            case '+':
                res += num[i];
                break;
            case '-':
                res -= num[i];
                break;
            case 'x':
                res *= num[i];
                break;
            case '%':
                res /= num[i];
                break;
        }
    }
    if(res < min_res){
        min_res = res;
    }
    if(res > max_res){
        max_res = res;
    }
}

void backtracking(int idx, int k, vector<bool> &is_used, vector<int> &choose_oper){
    if (idx >= k){
        update_min_max(choose_oper); // min, max 업데이트 
        return;
    }

    int next_ope = -1;
    while(true){
        next_ope++;
        if(next_ope >= k){ // 인덱스 범위 벗어나면 break; 
            break;
        }
        if(is_used[next_ope]){
            continue;
        }
        choose_oper[idx] = next_ope;
        is_used[next_ope] = true;

        backtracking(idx + 1, k, is_used, choose_oper);

        // 반납
        is_used[next_ope] = false; 
    }
}

int main(){
    //입력
    cin >> n;
    vector<bool> is_used(n-1, false); // operator 사용여부 체크 배열 
    vector<int> choose_oper(n-1); // 선택한 operator 조합 배열  

    int a;
    for(int i = 0; i < n; i++){ // 수 저장
        cin >> a;
        num.push_back(a);
    }

    int b;
    for(int j = 0; j < 4; j++){ // 연산자 저장 
        char op[4] = {'+', '-', 'x', '%'};
        cin >> b;
        while(b > 0){
            oper.push_back(op[j]);
            b--;
        }
    }

    //연산 
    backtracking(0, n-1, is_used, choose_oper);

    //출력
    cout << max_res << '\n';
    cout << min_res << '\n'; 
    return 0;
}