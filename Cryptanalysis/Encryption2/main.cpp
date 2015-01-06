#include<iostream>
#include<string>
#include<stdio.h>
#include<fstream>
#include<hash_map>
#include<sstream>
#include<string>
#include<vector>
#include<cstring>
#include<istream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>



using namespace std;

string GetBinaryStringFromHexString (string sHex);
std::string string_to_hex(const std::string&);
string XOR_Encryption(string , string);
int BinarySearch(string , vector<string>);
string GetHexFromBin(string sBinary);
string readKey();
char genRandom();
int hexCharToInt(char a);

static const char alphanum[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;


struct passwd *pw = getpwuid(getuid());
const char *homedir = pw->pw_dir;
std::string h = std::string(homedir);

std::string Cipher1Location = h + "/cipher000";
std::string Cipher2Location = h + "/cipher001";
std::string Cipher3Location = h + "/cipher002";
std::string Cipher4Location = h + "/cipher003";


int main()
{

     char msg1[256];
     char msg2[256];
     char msg3[256];
     char msg4[256];
     string sMsg1;
     string sMsg2;
     string sMsg3;
     string sMsg4;
     string hexMsg1;
     string hexMsg2;
     string hexMsg3;
     string hexMsg4;
     string cipher1;
     string cipher2;
     string cipher3;
     string cipher4;

     string hexKey;
     //code to generate random keys and write them to a file
     srand(time(0));

     ofstream Keys;
     Keys.open("Keys.txt");
     for(int i=0;i<100;i++)
     {
         for(int z=0; z < 21; z++)
         {

             Keys<<genRandom();

         }
        Keys<<'\n';
     }
     Keys.close();

     //get key from file
     string encryptionKey=readKey();

     //convert key to hex
     hexKey=  string_to_hex(encryptionKey);


     //code to take input messages from user
     cout<<"Enter the first message :"<<'\t';
     std::cin.getline(msg1,256);

     cout<<"Enter the second message :"<<'\t';
     std::cin.getline(msg2,256);

     cout<<"Enter the third message :"<<'\t';
     std::cin.getline(msg3,256);

     cout<<"Enter the four message :"<<'\t';
     std::cin.getline(msg4,256);


     sMsg1=msg1;
     sMsg2=msg2;
     sMsg3=msg3;
     sMsg4=msg4;

     cout<<'\n';
     cout<<"Message 1: "<<'\t'<<sMsg1<<'\n';
     cout<<"Message 2: "<<'\t'<<sMsg2<<'\n';
     cout<<"Message 1: "<<'\t'<<sMsg3<<'\n';
     cout<<"Message 2: "<<'\t'<<sMsg4<<'\n';

     //convert messages to hex
     hexMsg1= string_to_hex(msg1);
     hexMsg2= string_to_hex(msg2);
     hexMsg3= string_to_hex(msg3);
     hexMsg4= string_to_hex(msg4);

     cout<<'\n';
     cout<<"First msh in Hex: "<<'\t'<<hexMsg1<<'\n';
     cout<<"Second msh in Hex: "<<'\t'<<hexMsg2<<'\n';
     cout<<"Third msh in Hex: "<<'\t'<<hexMsg3<<'\n';
     cout<<"Fourth msh in Hex: "<<'\t'<<hexMsg4<<'\n';

     //encypt the messages
     cipher1= XOR_Encryption(hexMsg1,hexKey);
     cipher1=GetBinaryStringFromHexString(cipher1);
     cipher2= XOR_Encryption(hexMsg2,hexKey);
     cipher2=GetBinaryStringFromHexString(cipher2);
     cipher3= XOR_Encryption(hexMsg3,hexKey);
     cipher3=GetBinaryStringFromHexString(cipher3);
     cipher4= XOR_Encryption(hexMsg4,hexKey);
     cipher4=GetBinaryStringFromHexString(cipher4);

    // cout<< "Ciphet Text 1:"<< cipher1<<'\n';
    // cout<<" Cipher Text 2:"<<cipher2<<'\n';

     //code to write cipher text1 to a file
      ofstream cipherFile1;
      cipherFile1.open (Cipher1Location.c_str());
      cipherFile1 << cipher1;
      cipherFile1.close();
      cout<<"Cipher1 successfully written to file"<<'\n';

     //code to write cipher text2 to a file
     ofstream cipherFile2;
     cipherFile2.open (Cipher2Location.c_str());
     cipherFile2 << cipher2;
     cipherFile2.close();
     cout<<"Cipher2 successfully written to file"<<'\n';

     ofstream cipherFile3;
     cipherFile3.open (Cipher3Location.c_str());
     cipherFile3 << cipher3;
     cipherFile3.close();
     cout<<"Cipher1 successfully written to file"<<'\n';

    //code to write cipher text2 to a file
    ofstream cipherFile4;
    cipherFile4.open (Cipher4Location.c_str());
    cipherFile4 << cipher4;
    cipherFile4.close();
    cout<<"Cipher2 successfully written to file"<<'\n';

}


    //method to generate key
char genRandom()  // Random string generator function.
{

    return alphanum[rand() % stringLength];
    //cout<<alphanum[rand() % stringLength];
}


//method to convert string to hexadecimal form
std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    std::string output;
    output.reserve(2 * len);

        for (size_t i = 0; i < len; ++i)
        {
            const unsigned char c = input[i];
            output.push_back(lut[c >> 4]);
            output.push_back(lut[c & 15]);
        }
        return output;
}


//method to produce cipher texts
string XOR_Encryption(string str1, string str2)
{
    std::stringstream XORString;
       unsigned int minLength = str2.length();
       if(str1.length()<minLength)
           minLength=str1.length();
       for(int i=0;i<minLength;i++){
           XORString << hex << (hexCharToInt(str1[i])^hexCharToInt(str2[i]));
       }
       return XORString.str();
 }

int hexCharToInt(char a)
{
   if(a>='0' && a<='9')
       return(a-48);
   else if(a>='A' && a<='Z')
       return(a-55);
   else
       return(a-87);
}


//method to read a random key
string readKey()
{
   vector<string> keysvector;
   string key;
   ifstream readKey ("Keys.txt");
    if (readKey.is_open())
    {
    while ( getline (readKey,key) )
    {
    // cout << line << '\n';
     keysvector.push_back(key);

    }
    readKey.close();
    }

    int v1 = rand() % 100;         // v1 in the range 0 to 99
    return keysvector[v1];

}

//convert hex to binary
string GetBinaryStringFromHexString (string sHex)
{
      string sReturn = "";
      for (int i = 0; i < sHex.length (); ++i)
      {
          switch (sHex [i])
          {
                case '0': sReturn.append ("0000"); break;
                case '1': sReturn.append ("0001"); break;
                case '2': sReturn.append ("0010"); break;
                case '3': sReturn.append ("0011"); break;
                case '4': sReturn.append ("0100"); break;
                case '5': sReturn.append ("0101"); break;
                case '6': sReturn.append ("0110"); break;
                case '7': sReturn.append ("0111"); break;
                case '8': sReturn.append ("1000"); break;
                case '9': sReturn.append ("1001"); break;
                case 'a': sReturn.append ("1010"); break;
                case 'b': sReturn.append ("1011"); break;
                case 'c': sReturn.append ("1100"); break;
                case 'd': sReturn.append ("1101"); break;
                case 'e': sReturn.append ("1110"); break;
                case 'f': sReturn.append ("1111"); break;
            }
        }
    return sReturn;
}
