#include <iostream>

using namespace std;

pair<char, int> movePosition(char f, int s, string direc){
    // cf) RB는 R하고 B한 경우와 동일
    int len = direc.size(); // 1 또는 2
    char change;

    for(int i = 0 ; i < len; i++){
        change = direc[i]; // 한글자씩 받아서 이동
        switch(change){
            case 'R':
                f = f + 1;
                break;
            case 'L':
                f = f - 1;
                break;
            case 'B':
                s = s - 1;
                break;
            case 'T':
                s = s + 1;
                break;
        }
    }

    return {f, s};
}

void move(pair<char, int> &king, pair<char, int> &rock, string direc){
    
    char king_f = king.first;
    int king_s = king.second;
    char rock_f = rock.first;
    int rock_s = rock.second;

    // 1. king 위치 변경
    pair<char, int> new_king = movePosition(king_f, king_s, direc);

    pair<char, int> new_rock = rock; // 초기화
    // 2. 만약 움직인 king의 위치가 돌의 위치와 같다면 돌도 똑같이 움직이기
    if(new_king.first == rock_f && new_king.second == rock_s){
        new_rock = movePosition(rock_f, rock_s, direc); // 돌 위치 변경
    }

    // 3. first위치가 A보다 작거나 H보다 커지면 위치 변경 없이 return;
    if(new_king.first < 'A' || new_king.first > 'H' || new_rock.first < 'A' || new_rock.first > 'H'){
        return;
    }

    // 4. second위치가 1보다 작거나 8보다 커지면 위치 변경 없이 return; 
        if(new_king.second < 1 || new_king.second > 8 || new_rock.second < 1 || new_rock.second > 8){
        return;
    }

    king = new_king;
    rock = new_rock;
}

int main() {
    // 입력
    pair<char, int> king;
    pair<char, int> rock; 
    int N; // 움직인 횟수

    cin >> king.first >> king.second >> rock.first >> rock.second >> N;

    while(N--){
        string direction;
        cin >> direction;

        // 연산 
        move(king, rock, direction);
    }
    
    // 출력
    cout << king.first << king.second << "\n";
    cout << rock.first << rock.second << "\n";

    return 0;
}