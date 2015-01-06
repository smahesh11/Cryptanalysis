#include <string>
#include <bitset>
#include <iostream>
using namespace std;
int main()
{

string binary;
binary = "0111010001101000011001010010000001110000011100100110111101100111011100100110000101101101";

size_t idx=0, size=binary.size();

for (int i = 0; i < (size/8) ; i++, idx+=8)
{
//cout << bitset<8>(myString.c_str()[i]) << endl;
bitset<8> bitcode(binary);
char character = bitcode.to_ulong();

cout << character;

}
return 0;

}
