#include<stdio.h>


/*
  Structures and Enumeration Below:
*/


struct gCodeLine {
  char comment[64];
  char commandLetter[10];
  double commandNumbers[10];
};


/*
  Lookup Tables Below:
*/


static double tenToPowerOfNegative[] =
{
  1.0,
  0.1,
  0.01,
  0.001,
  0.0001,
  0.00001,
  0.000001,
  0.0000001,
  0.00000001,
  0.000000001,
  0.0000000001
};


static double tenToPowerOfPositive[] =
{
  1.0,
  10.0,
  100.0,
  1000.0,
  10000.0,
  100000.0,
  1000000.0,
  10000000.0,
  100000000.0,
  1000000000.0,
  10000000000.0
};


#define IS_DIGIT_MASK    0x01
#define IS_COMMAND_MASK  0x02
#define IS_PARAMETER_MASK 0x04


static char charFlags[] =
{
  0x00, //000
  0x00, //001
  0x00, //002
  0x00, //003
  0x00, //004
  0x00, //005
  0x00, //006
  0x00, //007
  0x00, //008
  0x00, //009 '\t'
  0x00, //010 '\n'
  0x00, //011
  0x00, //012
  0x00, //013 '\r'
  0x00, //014
  0x00, //015
  0x00, //016
  0x00, //017
  0x00, //018
  0x00, //019
  0x00, //020
  0x00, //021
  0x00, //022
  0x00, //023
  0x00, //024
  0x00, //025
  0x00, //026
  0x00, //027
  0x00, //028
  0x00, //029
  0x00, //030
  0x00, //031
  0x00, //032 ' '
  0x00, //033
  0x00, //034
  0x00, //035
  0x00, //036
  0x00, //037
  0x00, //038
  0x00, //039
  0x00, //040
  0x00, //041
  0x00, //042
  0x00, //043
  0x00, //044
  0x00, //045
  0x00, //046
  0x00, //047
  0x01, //048 '0'
  0x01, //049 '1'
  0x01, //050 '2'
  0x01, //051 '3'
  0x01, //052 '4'
  0x01, //053 '5'
  0x01, //054 '6'
  0x01, //055 '7'
  0x01, //056 '8'
  0x01, //057 '9'
  0x00, //058
  0x00, //059
  0x00, //060
  0x00, //061
  0x00, //062
  0x00, //063
  0x00, //064
  0x00, //065
  0x00, //066
  0x00, //067
  0x00, //068
  0x04, //069 'E'
  0x04, //070 'F'
  0x02, //071 'G'
  0x00, //072
  0x04, //073 'I'
  0x04, //074 'J'
  0x00, //075
  0x00, //076
  0x02, //077 'M'
  0x00, //078
  0x00, //079
  0x04, //080 'P'
  0x04, //081 'Q'
  0x04, //082 'R'
  0x04, //083 'S'
  0x04, //084 'T'
  0x00, //085
  0x00, //086
  0x00, //087
  0x04, //088 'X'
  0x04, //089 'Y'
  0x04, //090 'Z'
  0x00, //091
  0x00, //092
  0x00, //093
  0x00, //094
  0x00, //095
  0x00, //096
  0x00, //097
  0x00, //098
  0x00, //099
  0x00, //100
  0x04, //101 'e'
  0x04, //102 'f'
  0x02, //103 'g'
  0x00, //104
  0x04, //105 'i'
  0x04, //106 'j'
  0x00, //107
  0x00, //108
  0x02, //109 'm'
  0x00, //110
  0x00, //111
  0x04, //112 'p'
  0x04, //113 'q'
  0x04, //114 'r'
  0x04, //115 's'
  0x04, //116 't'
  0x00, //117
  0x00, //118
  0x00, //119
  0x04, //120 'x'
  0x04, //121 'y'
  0x04, //122 'z'
  0x00, //123
  0x00, //124
  0x00, //125
  0x00, //126
  0x00  //127
};


/*
  Number Parsing Below:
*/


const char* getWholeNumber(double *number, const char *string)
{
  //Setup for starting at most signicant digit.
  *number = 0.0;
  int digitPlace = 0;

  //Parse whole number.
  while(charFlags[*string] & IS_DIGIT_MASK)
    *number += (*(string++) - '0') * tenToPowerOfNegative[++digitPlace];
  *number *= tenToPowerOfPositive[digitPlace];

  return string;
}


const char* getFraction(double *number, const char *string)
{
  //Skip decimal point.
  if(*string == '.')
    string++;

  //Setup for starting at most signicant digit.
  *number = 0.0;
  int placeValue = 0;

  //Parse fraction.
  while(charFlags[*string] & IS_DIGIT_MASK)
    *number += (*(string++) - '0') * tenToPowerOfNegative[++placeValue];

  return string;
}


const char* getSign(double *sign, const char *string)
{
  *sign = 1.0; //Numbers without signs are positive.

  switch(*string)
  {
    case '-': *sign = -1.0; //Number is negative.
    case '+': string++; //Iterate pass sign char.
  }

  return string;
}


const char* getIntegerNumber(double *number, const char *string)
{
  //Get integer components.
  double sign;
  string = getSign(&sign, string);
  double wholeNumber;
  string = getWholeNumber(&wholeNumber, string);

  //Calculate integer with components and return position.
  *number = sign * wholeNumber;
  return string;
}


const char* getDecimalNumber(double *number, const char *string)
{
  //Get decimal components.
  double sign;
  string = getSign(&sign, string);
  double wholeNumber;
  string = getWholeNumber(&wholeNumber, string);
  double fraction;
  string = getFraction(&fraction, string);

  //Calculate decimal with components and return position.
  *number = sign * (wholeNumber + fraction);
  return string;
}


/*
  G-Code Parsing Below:
*/


const char* skipWhitespace(const char *string)
{
  while(*string == ' ' || *string == '\t')
    string++;
  return string;
}




int main()
{
  char character;
  double number;

  const char *remainingCommand = "M00002 t-24 x43.12";
  printf("Command: %s\n", remainingCommand);

  remainingCommand = getDecimalNumber(&number, remainingCommand+15);
  printf("[%lf]%s\n", number, remainingCommand);

  return 0;
}
