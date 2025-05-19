// 아이디어
/*
배열에서 고정된 크기 만큼을 계속 확인하면서 이동하네?
=> 슬라이딩 윈도우 or 투포인터!
여기서 윈도우 크기 = k
스시 종류 배열을 만들고 선택된 접시 수 값으로 저장 (= 마치 방문배열처럼)
쿠폰 번호의 종류는 따로 확인해야겠지!
*/ 


#include <iostream>
#include <vector>

using namespace std;

int slidingWindow(int n, int d, int k, int c, vector<int> sushi){
    
    // 스시 종류 배열 - 인덱스=종류, 값 = 현재 선택된 해당 종류의 스시 개수 
    vector<int> choose(d+1,0); // 모두 0으로 초기화 , 1부터 d개 
    int max_kind = 0; // 최대 종류 가짓수
    int count = 0;
    
    // 1. 슬라이딩 윈도우 초기화 , 윈도우 크기 =k
    for(int i =0; i <k; i++){
        choose[sushi[i]]++;
        if(choose[sushi[i]]==1){ // 처음 추가된 종류라면 count증가
            count++;
        }
        max_kind = count;
    }
    
    // 2. 왼쪽으로 한 칸씩 이동 반복 
    int first, last;
    for(int j = 0; j < n; j++){
        first = j; // 제외되는 초밥- 기존 윈도우 중 첫번째 초밥
        last = (j+k) % n; // 추가되는 초밥 - 이때 연결된 밸트를 배열로 나타냈으므로 i+k로 하면 안됨 
        
        choose[sushi[first]]--; // 제외하는 초밥        
        // 제외한 초밥이 해당 종류의 유일 초밥이였다면 
        if(choose[sushi[first]]==0){ 
            count--; // 종류 수 감소
        }
        
        choose[sushi[last]]++; // 추가되는 초밥 
        // 처음 추가된 종류라면 
        if(choose[sushi[last]]==1){ 
            count++; // 종류 수 추가
        }

        int res = count; 
        // *선택된 초밥 중 쿠폰의 초밥이 없다면 
        if(choose[c]==0){ 
            res++; // 종류 수 추가(쿠폰의 초밥이 추가되므로)
        }

        // 최대 종류 수 업데이트 
        if(max_kind < res){
            max_kind = res; 
        }

    }

    return max_kind; 
    
}

int main() {
    // 입력
    int n, d, k, c; // 접시 수, 가짓수, 연속 접시 수, 쿠폰번호
    cin >> n >> d >> k >>c;
    vector<int> sushi(n); // 벨트 위 초밥 
    for(int i =0; i < n; i++){
        cin >> sushi[i]; // 초밥 종류를 저장 
    }
    
    // 연산 & 출력
    cout << slidingWindow(n, d, k, c, sushi); // 최대 가짓수 출력
    
    return 0;
}