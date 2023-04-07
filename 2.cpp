#include <iostream>
#include <bitset>
#include <math.h>
#include <map>

using namespace std;

bitset<32> toBinary(float current){
    int sign = current < 0 ? 1 : 0;
    current = abs(current);

    int exponent = 0;
    while (current >= 2) {
        current /= 2;
        exponent++;
    }
    while (current < 1) {
        current *= 2;
        exponent--;
    }

    exponent += 127;

    float fraction = current - 1;

    bitset<32> bits;
    bits[31] = sign;
    bits[30] = (exponent >> 7) & 1;
    bits[29] = (exponent >> 6) & 1;
    bits[28] = (exponent >> 5) & 1;
    bits[27] = (exponent >> 4) & 1;
    bits[26] = (exponent >> 3) & 1;
    bits[25] = (exponent >> 2) & 1;
    bits[24] = (exponent >> 1) & 1;
    bits[23] = exponent & 1;

    for (int i = 22; i >= 0; i--) {
        fraction *= 2;
        if (fraction >= 1) {
            bits[i] = 1;
            fraction -= 1;
        }
        else bits[i] = 0;
    }
    return bits;
}

string From10to2(string input)
{
    string output, integerToBinary, fractionalToBinary;
    int integer;
    float fractional;
    int index = input.find(',');
    if (input.find(',') == -1) {
        integer = stoi(input);
        fractional = 0;
    }else {
        integer = stoi(input.substr(0, input.find(',')));
        string rawfractional = input.substr(input.find(',') + 1, input.length());
        fractional = stof(rawfractional)/pow(10,(rawfractional.length()));
    }

    if(integer >= 0) output.insert(0,1,'0');
    else {
        output.insert(0, 1, '1');
        integer = abs(integer);
    }

    if ( integer != 0) {
        while (integer >= 1) {
            integerToBinary.insert(0, to_string(integer % 2));
            integer /= 2;
        }
    }
    else integerToBinary = '0';
    int bitcounter;
    if (integerToBinary == "0") {
        bitcounter = 0;
    }
    else bitcounter = integerToBinary.length();
    for (bitcounter; bitcounter <24; bitcounter++) {
        float buf;
        fractional = modff(fractional*2, &buf);
        fractionalToBinary.insert(fractionalToBinary.length(), to_string((int)buf));
    }

    int exponent;
    if (integerToBinary == "0"){
        index = fractionalToBinary.find('1');
        exponent = 126 - index;
        fractionalToBinary = fractionalToBinary.substr(index + 1, fractionalToBinary.length());
        bitcounter = fractionalToBinary.length();
        for (bitcounter; bitcounter <23; bitcounter++) {
            float buf;
            fractional = modff(fractional*2, &buf);
            fractionalToBinary.insert(fractionalToBinary.length(), to_string((int)buf));
        }
    }
    else exponent = (integerToBinary.length() - 1) + 127;
    string exponentString;
    bool flag = false;
    if (exponent < 127) flag = true;
    while(exponent >= 1){
        exponentString.insert(0, to_string(exponent%2));
        exponent /= 2;
    }
    if (flag) exponentString.insert(0, 1, '0');
    output.insert(output.length(),exponentString);
    output.insert(output.length(), integerToBinary.substr(1, integerToBinary.length()));
    output.insert(output.length(), fractionalToBinary.substr(0, fractionalToBinary.length()));
    return output;
}

string From2to16(string input)
{
    string outputBinary, output;
    map <string, char> lib = {{"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
                              {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
                              {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
                              {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}};
    map <string, char> :: iterator it;
    for (int i = 0; i < 8; i++)
    {
        it = lib.find(input.substr(4*i, 4));
        output.insert(output.length(), 1, it->second);
    }
    return output;
}

string From16to10(string input)
{
    string outputBinary, output;
    map <char, string> lib = {{'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
                              {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
                              {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
                              {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};
    map <char, string> :: iterator it;
    for (int i = 0; i < 8; i++){
        it = lib.find(input[i]);
        outputBinary.insert(outputBinary.length(), it->second);
    }
    if (outputBinary[0] == 1) output.insert(output.length(), 1, '-');
    string rawexp = outputBinary.substr(1, 8);
    int exp = 0;
    for(int i = 0; i < 8; i++)
        if (rawexp[7-i] == '1')
            exp += pow(2, i);
    exp -= 127;
    string rawinteger = "1";
    string rawfractional;
    int integer = 0;
    float fractional = 0;
    if(exp >= 0)
    {
        rawinteger.insert(rawinteger.length(), outputBinary.substr(9, exp));
        for(int i = 0; i < rawinteger.length(); i++)
        {
            if(rawinteger[i] == '1')
            {
                integer += pow(2, rawinteger.length() - 1 - i);
            }
        }

        rawfractional.insert(0, outputBinary.substr(9+exp));
        for(int i = 0; i < rawfractional.length(); i++)
        {
            if(rawfractional[i] == '1')
            {
                fractional += pow(2, -(i+1));
            }
        }
        float outputNumber = fractional + integer;
        if (outputBinary[0] == '1')
            outputNumber *= -1;
        output = to_string(outputNumber);
    }
    else {
        rawfractional.insert(0, abs(exp), '0');
        rawfractional.insert(rawfractional.length(), 1, '1');
        rawfractional.insert(rawfractional.length(), outputBinary.substr(9));
        for(int i = 0; i < rawfractional.length(); i++)
        {
            if(rawfractional[i] == '1')
            {
                fractional += pow(2, -i);
            }
        }
        if (outputBinary[0] == '1')
            fractional *= -1;
        output = to_string(fractional);
    }
    return output;
}

int main() {

    int exercise;
    cout << "Enter the task number: ";
    cin >> exercise;
    string number_str;
    if(exercise!=1){
        cin >> number_str;
    }
    switch (exercise)
    {
    case 1:
        float number;
        cout << "Enter a decimal number: ";
        cin >> number;
        cout << "Machine representation: " << toBinary(number) << endl;
        break;
    case 2:
        cout << "Machine representation: " << From10to2(number_str) << endl;
        break;
    case 3:
        cout << number_str <<" in decimal number system: " << From16to10(number_str) << endl;
        break;
    default:
        break;
    }

    return 0;
}
