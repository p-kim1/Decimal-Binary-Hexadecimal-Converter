//Conversions from binary work with strings with and without leading zeroes
//Conversions from hexadecimal work with strings with and without '0x'
#include <string>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

string dec2bin(string str)
{
  string result;
  int numStr = atoi(str.c_str());
  while(numStr > 0)
    {
      result.insert(0,to_string(numStr%2));
      numStr /= 2;
    }
  while(result.length()%4 > 0) //Add leading zeroes
    {
      result.insert(0,"0");
    }
  return result;
}

string dec2hex(string str)
{
  string result = "0x";
  int numStr = atoi(str.c_str());
  string letters[6] = {"A","B","C","D","E","F"};
  while(numStr > 0)
    {
      int digit = numStr%16;
      if(digit > 9) //Insert corresponding letter
	{
	  result.insert(2,letters[digit-10]);
	}
      else //Single digit value
	{
	  result.insert(2,to_string(digit));
	}
      numStr /= 16;
    }
  return result;
}

string bin2dec(string str)
{
  int result = 0;
  int strLen = str.length();
  for(int i = strLen-1; i > -1; i--)
    {
      result+= pow(2,abs(i-strLen+1))*int(str[i]-'0');
    }
  return to_string(result);
}

string bin2hex(string str)
{
  return dec2hex(bin2dec(str));
}

string hex2dec(string str)
{
  int result = 0;
  int strLen = str.length();
  int endpoint = -1;
  if(str[1] == 'x') //Check for '0x'
    {
      endpoint = 1;
    }
  for(int i = strLen-1; i > endpoint; i--)
    {
      int digit;
      if(int(str[i])-65 > -1) //str[i] is a letter
	{
	  digit = int(str[i])-55;
	}
      else //str[i] is a number
	{
	  digit = str[i]-'0';
	}
      result+= pow(16,abs(i-strLen+1))*digit;
    }
  return to_string(result);
}

string hex2bin(string str)
{
  return dec2bin(hex2dec(str));
}

int main(int argc, char** argv)
{
  string str = argv[1];
  string origBase = argv[2];
  string convertBase = argv[3];
  string result;
  if(origBase == "d")
    {
      if(convertBase == "b")
	{
	  result = dec2bin(str);
	}
      else if(convertBase == "h")
	{
	  result = dec2hex(str);
	}
    }
  else if(origBase == "b")
    {
      if(convertBase == "d")
	{
	  result = bin2dec(str);
	}
      else if(convertBase == "h")
	{
	  result = bin2hex(str);
	}
    }
  else if(origBase == "h")
    {
      if(convertBase == "d")
	{
	  result = hex2dec(str);
	}
      else if(convertBase == "b")
	{
	  result = hex2bin(str);
	}
    }
  cout << result << endl;
}
