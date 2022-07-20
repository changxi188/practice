

#include <iostream>
#include <string>

using namespace std;

bool Increment(string &number){
    bool isOverflow = false;
    // 这个是进位符
    int nTakeOver = 0;

    for (string::reverse_iterator it = number.rbegin();  it != number.rend(); ++it){
        int nSum = *it - '0' + nTakeOver;

        // 如果是个位的才会对nSum加1
        if (it == number.rbegin())
           nSum++;

        if (nSum >= 10){
            if(it == number.rend() - 1)
                isOverflow = true;
            else{
                nTakeOver = 1;
                nSum -=10;
                *it = '0' + nSum;
            }

        } else{
            *it = '0' + nSum;
            break;
        }
    }
    return isOverflow;
}

void PrintNumber(const string& number){
    bool isBeginning0 = true;
    for(auto it = number.begin(); it != number.end(); ++it){
        if(isBeginning0 && *it != '0')
            isBeginning0 = false;

        if (!isBeginning0){
            cout << *it;
        }
    }

    cout << "\t";
}

void Print1ToMaxOfNDigits_1(int n){

    if (n <= 0)
        return;

    string number(n, '0');

    while (!Increment(number)){
        PrintNumber(number);
    }



}

int main(){
    int n;
    cout << " 输入数字 : ";
    cin >> n;

    Print1ToMaxOfNDigits_1(n);


}