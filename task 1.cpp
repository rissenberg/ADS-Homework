/* Во всех задачах необходимо использование битовых операций. 
Использование арифметических операций запрещено.
Входное число лежит в диапазоне 0..2^32 -1 и вводится в десятичном виде.
1.3 Если в числе содержится только один бит со значением 1, записать в выходной поток OK. Иначе записать FAIL 
*/

#include <iostream>

using namespace std;

string IsOneDigitEqualsOne(unsigned int input){
    if (input == 0) {
        return "FAIL";
    }
    bool flag = 0;
    while (input > 0) {
        if (input & 1 == 1) {
            if (flag == 1) {
                return "FAIL";
            }
            else {
                flag = 1;
            }
        }
        input = input >> 1;
    }
    return "OK";
};

int main() 
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    unsigned int input;
    cin >> input;

    cout << IsOneDigitEqualsOne(input) << endl;

    return 0;
}

// T(n)=O(log n), M(n)=O(1), где n - входное число
