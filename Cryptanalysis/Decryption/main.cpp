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

vector<string> readCribFromFile();
std::string string_to_hex(const std::string&);
string hex_to_string(string);
string XOR_Encryption(string str1, string str2);
int hexCharToInt(char);
int searchSubString(string );
char* subString(string );
int meaningfullString(string str,vector<string>);
vector<string> search(vector<string>, string);
int isReadable(string);
int BinarySearch(string , vector<string>);
//void recursiveCalls (string ,vector<string>);
int recursiveCalls(string,vector<string> ,string, string,int, string, string);
string GetHexFromBin(string sBinary);
string BinaryToString(string sBinary);


   struct passwd *pw = getpwuid(getuid());
   const char *homedir = pw->pw_dir;
   std::string h = std::string(homedir);

   std::string Cipher1Location = h + "/cipher000";
   std::string Cipher2Location = h + "/cipher001";
   std::string Cipher3Location = h + "/cipher002";
   std::string Cipher4Location = h + "/cipher003";
   std::string message1Location = h + "/msg000";
   std::string message2Location = h + "/msg001";
   std::string message3Location = h + "/msg002";
   std::string message4Location = h + "/msg003";
   std::string padLocation = h + "/pad.txt";
   std::string Words = h + "/words";



static int success=0;

int main()
{
    vector<string> words;
    string line;
    string cipher12;
    string cipher34;
    string cipher;
    string binCipher1;
    string binCipher2;
    string binCipher3;
    string binCipher4;
    string ccipher1;
    string ccipher2;
    string ccipher3;
    string ccipher4;
    string crib;
    string hexCrib;
    string cribXorCipher;
    string result;
    string fullCipher;
    string fullCipher12;
    string fullCipher34;
    string subcipher1;
    string subcipher2;
    string subcipher3;
    string subcipher4;

    int len;
    int halflen;
    vector<string> CribsVector;


    //Reading words dictionary and store in vector
    ifstream myfile (Words.c_str());

    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
         words.push_back(line);
        }
        myfile.close();

    }
    else cout << "Unable to open file";

    //Code to read cipher 1 from a file
   ifstream readCipher1 (Cipher1Location.c_str());

    if (readCipher1.is_open())
    {
    getline (readCipher1,binCipher1);
    }
    readCipher1.close();

    //Code to read cipher 2 from a file
  ifstream readCipher2 (Cipher2Location.c_str());

    if (readCipher2.is_open())
     {
     getline (readCipher2,binCipher2);
     }
    readCipher2.close();

    //Code to read cipher 3 from a file
    ifstream readCipher3 (Cipher3Location.c_str());
    if (readCipher3.is_open())
     {
     getline (readCipher3,binCipher3);
     }
    readCipher3.close();


    //Code to read cipher 4 from a file
  ifstream readCipher4 (Cipher4Location.c_str());
    if (readCipher4.is_open())
     {
     getline (readCipher4,binCipher4);
     }
    readCipher4.close();



    //convert binary ciphertext to hex

   string fulHexCipher1= GetHexFromBin(binCipher1);
   string fulHexCipher2= GetHexFromBin(binCipher2);
   string fulHexCipher3= GetHexFromBin(binCipher3);
   string fulHexCipher4= GetHexFromBin(binCipher4);

   ccipher1= fulHexCipher1.substr(3);
   ccipher2= fulHexCipher2.substr(3);
   ccipher3= fulHexCipher3.substr(3);
   ccipher4= fulHexCipher4.substr(3);

 //  ccipher1=string_to_hex(stringCipher1);
 //  ccipher2=string_to_hex(stringCipher2);

     cout<<"Cipher 1 in Hex: "<<'\t'<<ccipher1<<'\n';
     cout<<"Cipher 2 in Hex :"<<'\t'<<ccipher2<<'\n';
     cout<<"Cipher 3 in Hex: "<<'\t'<<ccipher3<<'\n';
     cout<<"Cipher 4 in Hex :"<<'\t'<<ccipher4<<'\n';

    //calling vector containing list of frequently used words
    CribsVector=readCribFromFile();

    for(int i=0;i<CribsVector.size();i++)
     //for(int i=0;i<3;i++)
    {
      if(success==1)
    {
           //crib=CribsVector[i];
       //  cout<<crib<<'\n';
          break;
    }
      else
     {
      crib=CribsVector[i];
      //crib="the";
      cout<<crib<<'\n';


    //convert crib to hex
    hexCrib= string_to_hex(crib);
    //cout<<"Crib : "<<'\t'<<crib<<'\t';
    //cout<<"Crib in Hex Form: "<<'\t'<<hexCrib<<'\n';

    int size=hexCrib.length();
    //cout<<"Size of hexCrib is: "<< size<<'\n';

    //trimming cipher texts
    subcipher1=ccipher1.substr(0,size);
    subcipher2=ccipher2.substr(0,size);
    subcipher3=ccipher3.substr(0,size);
    subcipher4=ccipher4.substr(0,size);

    //XOR of complete ciphers
    fullCipher12=XOR_Encryption(ccipher1,ccipher2);
    fullCipher34=XOR_Encryption(ccipher3,ccipher4);
    fullCipher=XOR_Encryption(fullCipher12,fullCipher34);

    //cout<<"Full Cipher : "<<fullCipher<<'\n';
    len=fullCipher12.length();

    halflen=len/2;

    //XOR on both trimmed cipher texts
    cipher12=XOR_Encryption(subcipher1,subcipher2);
    cipher34=XOR_Encryption(subcipher3,subcipher4);
    cipher=XOR_Encryption(cipher12,cipher34);


    //XOR Cipher and crib
    cribXorCipher= XOR_Encryption(cipher12,hexCrib);

    //Convert CribXorCipher to string
    result=hex_to_string(cribXorCipher);


   recursiveCalls(result,words,fullCipher12,ccipher2,halflen,subcipher3,subcipher4);
        }
   }

   return 0;
}


 vector<string> readCribFromFile()
{
    vector<string> Cribs;
    string crib1;

    //Code to read crib from a file
    ifstream ReadCrib (Words.c_str());
    if (ReadCrib.is_open())
    {
        //cout<<"File found"<<'\n';
        while ( getline (ReadCrib,crib1) )
        {
        //cout << line << '\n';
         if(isReadable(crib1)==1)
         Cribs.push_back(crib1);
        //key[]=;
        }

    }
    ReadCrib.close();

    return Cribs;
 }

//method to convert string to hex
 std::string string_to_hex(const std::string& input)
    {
        static const char* const lut = "0123456789ABCDEF";
        size_t len = input.length();
        std::string output="";
        output.reserve(2 * len);

        for (size_t i = 0; i < len; ++i)
        {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
        }
      return output;
    }


//method for XOR Encryption
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


//method for hex to string
string hex_to_string(string str)
{
   std::stringstream HexString;
   for(int i=0;i<str.length();i++)
   {
       char a = str.at(i++);
       char b = str.at(i);
       int x = hexCharToInt(a);
       int y = hexCharToInt(b);
       HexString << (char)((16*x)+y);
   }
   return HexString.str();
}


//method to get string from hex value
int hexCharToInt(char a)
{
    if(a>='0' && a<='9')
    return(a-48);
    else if(a>='A' && a<='Z')
    return(a-55);
    else
    return(a-87);
}


//method to search substring and return matching phrases
vector<string> search(vector<string> words, string searchString1)
{
//code to chk for spaces and select seachword
    string searchString2;
    int spaces=0;
    vector<string> vctr;
    string temp;
    string found;
    string foundSubString;
    vector<string> foundWords;

    for(int i=0;i<searchString1.length();i++)
    {
        if(searchString1.at(i)==' ')
        {
             spaces++;
            //code to split string by spaces
            stringstream s(searchString1);
            while(s>>temp)
            {
             vctr.push_back(temp);
             }
          }
    }

    if(spaces==0)
    {
         searchString2=searchString1;
         for(int i =0; i <words.size(); i++)
         {
             found = words[i];

             foundSubString = found.substr (0,searchString2.length());

              if(foundSubString ==searchString2)
              {

                 foundWords.push_back(found);
                 //foundWords.push_back(found);
             }

         }
    }

    else
    {
        searchString2=vctr[spaces];
        for(int i =0; i <words.size(); i++)
        {
            found = words[i];

            foundSubString = found.substr (0,searchString2.length());

                if(foundSubString ==searchString2)
                {
                 string phrase="";
                for(int j=0;j<vctr.size()-1;j++)
                {
                phrase.append(vctr[j]).append(" ");
                }
                 phrase.append(found);
                 foundWords.push_back(phrase);
           //foundWords.push_back(found);
       }

    }
    }

    return foundWords;

}


//method to search complete words
int BinarySearch(string X, vector<string> List)
{
    int Left, Right, MidPoint ;
    Left = 0 ;
    Right = List.size() - 1 ;
    MidPoint = (Left + Right) / 2 ;

    while(Left <= Right && List[MidPoint] != X)
    {
      if(X < List[MidPoint])
        {
        Right = MidPoint - 1 ;
        }
        else
        {
        Left = MidPoint + 1 ;
        }

        MidPoint = (Left + Right) / 2 ;
    }

        if(Left <= Right)
        {
        return MidPoint ;
        }
        else
        {
        return -1 ;
        }

}


//method to check if every word is meaningful
int meaningfullString(string str,  vector<string> words)
{
vector<string> vctr;
//cout<< "string" << '\n';

//isReadable(str);
   if(isReadable(str)==1)
   {
           int j=0;
       // cout<<"is readable"<<'\n';
       for(int i=0;i<str.length();i++)
       {
          // cout<<"in for loop";

           //code to split string by spaces
           if(str.at(i)==' ')
           {

           vctr.push_back(str.substr(j,i-j));
           j=i+1;

           }

        }

        vctr.push_back(str.substr(j,str.length()));


         bool flag;
       for(int k=0;k<vctr.size();k++)
       {
          flag=false;
          int x= BinarySearch(vctr[k],words);
          if(x==-1)
          {
               return 0;
          }
          else
              flag=true;

       }
      return 1;
   }
   else
   {
   return 0;
   }
}

 //method to check if a string is readable or not
int isReadable(string str)
{
    for(int i=0;i<str.length();i++)
    {
        if(!((str.at(i) >= 'A' && str.at(i) <= 'Z') || (str.at(i) >= 'a' && str.at(i) <= 'z') || (str.at(i)==' ') || (str.at(i)=='\'')))
     {
     return 0;
     }
}

return 1;
}


//Recursion for finding the exact word
int recursiveCalls(string result,vector<string> words,string fullCipher, string cipher, int halflen,string subcipher3,string subcipher4)
{

        vector<string> trimmedPhrase;
        vector<string> trimmedPhraseinHex;
        vector<string> trimmedPhraseInHexXORCipher;
        vector<string> newPhraseRecovered;
        vector<string> validStrings;
        vector<string> foundWords;
        string message1;
        string message2;
        string message3;
        string message4;

        if(success==1)
            return 0;

        //get the resultant phrases
        foundWords= search(words,result);


        //Trim resulted phrases and store in a new vector
        for(int i=0;i<foundWords.size();i++)
        {

            if(foundWords[i].length()<=halflen)
            {

                trimmedPhrase.push_back(foundWords[i]);
            }

         }

        for(int i=0;i<trimmedPhrase.size();i++)
          {

              string str=string_to_hex(trimmedPhrase[i]);
              trimmedPhraseinHex.push_back(str);
          }


        //convert trimmed phrase to hex
        for(int i=0;i<trimmedPhraseinHex.size();i++)
         {

             string str=XOR_Encryption(trimmedPhraseinHex[i],fullCipher);
             trimmedPhraseInHexXORCipher.push_back(str);
         }

             //recover message
        for(int i=0;i<trimmedPhraseInHexXORCipher.size();i++)
        {
            newPhraseRecovered.push_back(hex_to_string(trimmedPhraseInHexXORCipher[i]));
        }

       int max=0;
       for(int n=0;n<newPhraseRecovered.size();n++)
        {

           if(meaningfullString(newPhraseRecovered[n],words))
         {

            if(newPhraseRecovered[n].length()>max)
            {
            max=newPhraseRecovered[n].length();

            }

            validStrings.push_back(newPhraseRecovered[n]);
         }
       }

        bool flag=false;
        for(int n=1;n<newPhraseRecovered.size();n++)
        {
            newPhraseRecovered[0]="";
            trimmedPhrase[0]="";

            if(meaningfullString(newPhraseRecovered[n],words)&& meaningfullString(trimmedPhrase[n],words))
                {
                    flag=true;
                    result=newPhraseRecovered[n];
                    if(newPhraseRecovered[n].length()==halflen)
                    {
                        //recovering message1
                       if(newPhraseRecovered[n]!=newPhraseRecovered[n-1])
                       {   success=1;
                           message1=newPhraseRecovered[n];

                           ofstream message1file;
                           message1file.open (message1Location.c_str());
                           message1file << newPhraseRecovered[n];
                           message1file.close();

                         cout<<"'"<<newPhraseRecovered[n]<<"'"<<'\t'<<"successfully written to file"<<'\n';
                       }

                       //recovering message2
                        if(trimmedPhrase[n]!=trimmedPhrase[n-1])
                        {   success=1;
                            message2=trimmedPhrase[n];

                            ofstream message2file;
                            message2file.open (message2Location.c_str());
                            message2file << message2;
                            message2file.close();
                           cout<<"'"<<message2<<"'"<<'\t'<<"successfully written to file"<<'\n';
                            //code to retrieve key
                        }


                        //recovering key
                        string phraseHex=string_to_hex(message2);
                        string hexKey=XOR_Encryption(phraseHex,cipher);
                        string key=hex_to_string(hexKey);


                         //recovering message3
                         message3=hex_to_string(XOR_Encryption(hexKey,subcipher3));
                         ofstream message3file;
                         message3file.open (message3Location.c_str());
                         message3file << message3;
                         message3file.close();
                         cout<<"'"<<message3<<"'"<<'\t'<<"successfully written to file"<<'\n';

                         //recovering message3
                         message4=hex_to_string(XOR_Encryption(hexKey,subcipher4));
                         ofstream message4file;
                         message4file.open (message4Location.c_str());
                         message4file << message4;
                         message4file.close();
                         cout<<"'"<<message4<<"'"<<'\t'<<"successfully written to file"<<'\n';

                         cout<<"The key is";
                         cout<<"'"<<key<<"'"<<'\t'<<"successfully written to file"<<'\n';
                         //code to write key to file
                         ofstream keyFile;
                         keyFile.open (padLocation.c_str());
                         keyFile << key;
                         keyFile.close();
                    }

                  }
            }
        if(flag==false)
            return 0;

    recursiveCalls(result,words, fullCipher,cipher, halflen,subcipher3,subcipher4);

}


//method to convert binary to hexadecimal
 string GetHexFromBin(string sBinary)
{
    string rest("0x"),tmp,chr = "0000";
    int len = sBinary.length()/4;
    chr = chr.substr(0,len);
    sBinary = chr+sBinary;
    for (int i=0;i<sBinary.length();i+=4)
    {
        tmp = sBinary.substr(i,4);
        if (!tmp.compare("0000"))
        {
            rest = rest + "0";
        }
        else if (!tmp.compare("0001"))
        {
            rest = rest + "1";
        }
        else if (!tmp.compare("0010"))
        {
            rest = rest + "2";
        }
        else if (!tmp.compare("0011"))
        {
            rest = rest + "3";
        }
        else if (!tmp.compare("0100"))
        {
            rest = rest + "4";
        }
        else if (!tmp.compare("0101"))
        {
            rest = rest + "5";
        }
        else if (!tmp.compare("0110"))
        {
            rest = rest + "6";
        }
        else if (!tmp.compare("0111"))
        {
            rest = rest + "7";
        }
        else if (!tmp.compare("1000"))
        {
            rest = rest + "8";
        }
        else if (!tmp.compare("1001"))
        {
            rest = rest + "9";
        }
        else if (!tmp.compare("1010"))
        {
            rest = rest + "A";
        }
        else if (!tmp.compare("1011"))
        {
            rest = rest + "B";
        }
        else if (!tmp.compare("1100"))
        {
            rest = rest + "C";
        }
        else if (!tmp.compare("1101"))
        {
            rest = rest + "D";
        }
        else if (!tmp.compare("1110"))
        {
            rest = rest + "E";
        }
        else if (!tmp.compare("1111"))
        {
            rest = rest + "F";
        }
        else
        {
            continue;
        }
    }
    return rest;
}


//method to convert binary to string
 string BinaryToString(string sBinary)
{
    string rest(""),tmp;
    for (int i=0;i<sBinary.length();i+=8)
    {
        tmp = sBinary.substr(i,8);
        int decimal=0;

        for(int j=0;j<tmp.length();j++)
            decimal=2*decimal+((int)tmp[j]-48);

        rest=rest+(char)decimal;
           //rest.append((char)decimal+"");

    }
    return rest;
}




