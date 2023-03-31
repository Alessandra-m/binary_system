#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

string Binary(int num, string bin){

    while(num != 1){
        if(num%2 == 1){
            bin += "1";
            num /= 2;
        }
        else{
            num /= 2;
            bin += "0";
        }
    }

    bin += to_string(num);
    reverse(bin.begin(), bin.end());
    bin += ".";
    return bin;
}

string Binary_I(double num, string bin){
    for(int i = 1; i < 23; i++){
        num = (num - floor(num))*2;
        int int_num = floor(num);
        bin += to_string(int_num);
    }
    return bin;
}


int main()
{
    double current_num;
    cout << "Enter the number: ";
    cin >> current_num;

    int integer = floor(current_num);
    double fractional = current_num - integer;

    string binary;
    binary = Binary(integer, binary);

    cout << Binary_I(fractional, binary);

    return 0;
}
