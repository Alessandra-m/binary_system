#include <iostream>
#include <math.h>

using namespace std;

void output(int *array, int n){
    for(int i = 0; i < n; i++)
        cout << array[i];
}

int Quantity(int num){
    int size = 0;
    while(num != 1){
        num /= 2;
        size++;
    }
    size++;
    return size;
}

int Binary(int num, int *bin){
    int N = Quantity(num);
    int mas[N], i = 0;
    for(int i = 0; i < N; i++)
        mas[i] = 0;

    while(num != 1){
        if(num%2 == 1){
            mas[i] = 1;
            num /= 2;
        }
        else num /= 2;
        i++;
    }
    mas[i] = num;
    output(mas, N);
    cout << endl;

    for(int i=1, j=N-1; i<N+1; i++, j--){
        cout << mas[j]<<endl;
        bin[i] = mas[j];
    }
    output(bin, 32);
}

int I_Binary(int num, int *bin){




}

int main()
{
    double current_num;
    cout << "Enter the number: ";
    cin >> current_num;

    int binary[32];
    for(int i = 0; i < 32; i++)
        binary[i] = 0;

    if(current_num < 0){
        binary[0] = 1;
        current_num *= -1;

    }

    int integer = floor(current_num);
    double fractional = current_num - integer;

    Binary(current_num, binary);



    return 0;
}
