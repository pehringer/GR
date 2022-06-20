#include<stdio.h>


/*
  Structures and Enumeration Below:
*/


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


#define DIGIT_MASK      0x01
#define EOL_MASK        0x02
#define LETTER_MASK     0x04
#define WHITESPACE_MASK 0x08


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
  0x08, //009 '\t'
  0x02, //010 '\n'
  0x00, //011
  0x00, //012
  0x02, //013 '\r'
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
  0x08, //032 ' '
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
  0x04, //065 'A'
  0x04, //066 'B'
  0x04, //067 'C'
  0x04, //068 'D'
  0x04, //069 'E'
  0x04, //070 'F'
  0x04, //071 'G'
  0x04, //072 'H'
  0x04, //073 'I'
  0x04, //074 'J'
  0x04, //075 'K'
  0x04, //076 'L'
  0x04, //077 'M'
  0x04, //078 'N'
  0x04, //079 'O'
  0x04, //080 'P'
  0x04, //081 'Q'
  0x04, //082 'R'
  0x04, //083 'S'
  0x04, //084 'T'
  0x04, //085 'U'
  0x04, //086 'V'
  0x04, //087 'W'
  0x04, //088 'X'
  0x04, //089 'Y'
  0x04, //090 'Z'
  0x00, //091
  0x00, //092
  0x00, //093
  0x00, //094
  0x00, //095
  0x00, //096
  0x04, //097 'a'
  0x04, //098 'b'
  0x04, //099 'c'
  0x04, //100 'd'
  0x04, //101 'e'
  0x04, //102 'f'
  0x04, //103 'g'
  0x04, //104 'h'
  0x04, //105 'i'
  0x04, //106 'j'
  0x04, //107 'k'
  0x04, //108 'l'
  0x04, //109 'm'
  0x04, //110 'n'
  0x04, //111 'o'
  0x04, //112 'p'
  0x04, //113 'q'
  0x04, //114 'r'
  0x04, //115 's'
  0x04, //116 't'
  0x04, //117 'u'
  0x04, //118 'v'
  0x04, //119 'w'
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
  Parsing Below:
*/


const char* getSignValue(double *value, const char *string)
{
  *value = 1.0; //Numbers are default positive.

  switch(*string)
  {
    case '-': *value = -1.0; //Number is negative.
    case '+': string++; //Iterate pass sign char.
  }

  return string;
}


const char* getDigitsValue(double *value, int fractional, const char *string)
{
  //Starting at most signicant digit of whole or fractional number.
  *value = 0.0;
  int digitPlace = 0;

  //Parse digits to value.
  while(charFlags[*string] & DIGIT_MASK)
    *value += (*(string)++ - '0') * tenToPowerOfNegative[++digitPlace];

  //Value is not fractional, shift value left of decimal point.
  if(!fractional)
    *value *= tenToPowerOfPositive[digitPlace];

  return string;
}


const char* getNumberValue(double *value, const char *string)
{
  //Parse out the numbers components.
  double sign;
  const char *afterSign = getSignValue(&sign, string);
  double whole;
  const char *afterWhole = getDigitsValue(&whole, 0, afterSign);
  const char *afterDecimal = *afterWhole == '.' ? afterWhole + 1 : afterWhole;
  double fraction;
  const char *afterFraction = getDigitsValue(&fraction, 1, afterDecimal);

  //Digit parsed, number parsed.
  if(afterWhole - afterSign || afterFraction - afterDecimal)
  {
    *value = sign * (whole + fraction);
    return afterFraction;
  }

  //No digits parsed, no number parsed.
  *value = 0.0;
  return string;
}


const char* getParameters(char *letters, double *numbers, const char *string);

const char* getCommand(char* letters, double *numbers, const char *string);

const char* getComment(char* comment, const char *string);


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
