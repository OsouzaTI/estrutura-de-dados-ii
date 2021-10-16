#include <iostream>
using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void sequenceNumbersSum(){
    int x, y;    
    while(true){
        cin >> x >> y;
        if(x < y) swap(x, y);
        if(x <= 0 || y <= 0)
            break;
        int sum = 0;
        for (int i = y; i <= x; i++){
            cout << i << " ";      
            sum += i;
        }
        cout << "Sum" << "=" << sum << endl;        
    }
}


int main(){
    
    sequenceNumbersSum();
    
    return 0;
}