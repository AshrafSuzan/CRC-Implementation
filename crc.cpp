#include <iostream>
#include <cstdlib>
#include<time.h>
using namespace std;


string XOR(string a, string b) {


    string res;
    for(int i=0; i<a.length(); i++) {
        if(a[i] == b[i]) res += '0';
        else res += '1';
    }
    return res;


}

string encodeMessage(string message, string divisor) {

    int divisorLen = divisor.length();
    int messageLen = message.length();

    for (int i = 0; i < divisorLen -1; i++) {
        message += '0';
    }

    string tmp = message.substr(0, divisorLen);

    for(int i=0; i< messageLen+1; i++) {
        tmp = message.substr(i, divisorLen);

        if(tmp[0] == '1') {
            string xored = XOR(tmp,divisor);
            for(int j=0; j<divisorLen; j++){
                message[i+j] = xored[j];
            }
        }
    }
    return tmp;


}

string changRandomly(string message, int x){
    srand(time(0));
    for(int i =0; i<x; i++){
        int j = rand()% message.length();
        if (message[j] == '1') message[j] = '0';
        else message[j] = '1';
    }

    return message;
}

int main() {
	string message, divisor;
	cout << "Message: " ;
	cin >> message;
	cout << "Divisor: ";
	cin >> divisor;


	string remainder = encodeMessage(message, divisor);
	string encoded = message + remainder;
	cout << "Frame check sequence: " << remainder << endl;
	cout << "Frame: " << encoded << endl;

	string corrupted = changRandomly(encoded, 3);
	cout << "After randomly changing 3 bits: " << corrupted << endl;

	string corruptedRemainder = encodeMessage(corrupted, divisor);

	cout << "Remainder is " << corruptedRemainder << ". ";

	for(int i=0; i<corruptedRemainder.length(); i++){
        if(corruptedRemainder[i] == '1') {
            cout << "ERROR Detected." << endl;
            return 0;
        }
	}

	cout << "No ERROR Detected." << endl;

	return 0;
}

