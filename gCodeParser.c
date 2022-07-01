#include<stdio.h>


/*
  Lookup Tables Below:
*/


static const double TEN_TO_POWER_NEGATIVE[] =
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


static const double TEN_TO_POWER_POSITIVE[] =
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


/*
  Equivalent Characters
*/


//Bit flags for elements of CHAR_IS.
static const char IS_ARGUMENT_CHAR   = 0x01;
static const char IS_DIGIT_CHAR      = 0x02;
static const char IS_NEWLINE_CHAR    = 0x04;
static const char IS_TEXT_CHAR       = 0x08;
static const char IS_WHITESPACE_CHAR = 0x10;


//Indexes are mapped to corresponding char values.
//Each element holds a given chars bit flags.
static const char CHAR_IS[] =
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
  0x18, //009 '\t'
  0x0C, //010 '\n'
  0x00, //011
  0x00, //012
  0x0C, //013 '\r'
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
  0x18, //032 ' '
  0x08, //033 '!'
  0x00, //034 '"'
  0x08, //035 '#'
  0x08, //036 '$'
  0x08, //037 '%'
  0x08, //038 '&'
  0x00, //039 '''
  0x00, //040 '('
  0x00, //041 ')'
  0x09, //042 '*'
  0x08, //043 '+'
  0x08, //044 ','
  0x08, //045 '-'
  0x08, //046 '.'
  0x08, //047 '/'
  0x0A, //048 '0'
  0x0A, //049 '1'
  0x0A, //050 '2'
  0x0A, //051 '3'
  0x0A, //052 '4'
  0x0A, //053 '5'
  0x0A, //054 '6'
  0x0A, //055 '7'
  0x0A, //056 '8'
  0x0A, //057 '9'
  0x08, //058 ':'
  0x08, //059 ';'
  0x08, //060 '<'
  0x08, //061 '='
  0x08, //062 '>'
  0x08, //063 '?'
  0x08, //064 '@'
  0x09, //065 'A'
  0x09, //066 'B'
  0x09, //067 'C'
  0x09, //068 'D'
  0x08, //069 'E'
  0x09, //070 'F'
  0x09, //071 'G'
  0x09, //072 'H'
  0x09, //073 'I'
  0x09, //074 'J'
  0x09, //075 'K'
  0x09, //076 'L'
  0x09, //077 'M'
  0x09, //078 'N'
  0x08, //079 'O'
  0x09, //080 'P'
  0x09, //081 'Q'
  0x09, //082 'R'
  0x09, //083 'S'
  0x09, //084 'T'
  0x08, //085 'U'
  0x08, //086 'V'
  0x08, //087 'W'
  0x09, //088 'X'
  0x09, //089 'Y'
  0x09, //090 'Z'
  0x08, //091 '['
  0x08, //092 '\'
  0x08, //093 ']'
  0x08, //094 '^'
  0x08, //095 '_'
  0x08, //096 '`'
  0x09, //097 'a'
  0x09, //098 'b'
  0x09, //099 'c'
  0x09, //100 'd'
  0x08, //101 'e'
  0x09, //102 'f'
  0x09, //103 'g'
  0x09, //104 'h'
  0x09, //105 'i'
  0x09, //106 'j'
  0x09, //107 'k'
  0x09, //108 'l'
  0x09, //109 'm'
  0x09, //110 'n'
  0x08, //111 'o'
  0x09, //112 'p'
  0x09, //113 'q'
  0x09, //114 'r'
  0x09, //115 's'
  0x09, //116 't'
  0x08, //117 'u'
  0x08, //118 'v'
  0x08, //119 'w'
  0x09, //120 'x'
  0x09, //121 'y'
  0x09, //122 'z'
  0x08, //123 '{'
  0x08, //124 '|'
  0x08, //125 '}'
  0x08, //126 '~'
  0x00  //127
};


/*
  Argument Parsing:
*/


/*
  Returns: Given string pointer if no sign was parsed.
           Given string pointer offset to char after sign if parsed.
*/
static const char* parseSign(double *value, const char *string)
{
  *value = 1.0; //Numbers are default positive if no sign is present.

  switch(*string)
  {
    case '-': *value = -1.0; //Number is negative.
    case '+': string++; //Iterate pass sign char.
  }

  return string;
}


/*
  Returns: Given string pointer if no digits were parsed.
           Given string pointer offset to char after digits if parsed.
*/
static const char* parseDigits(double *value, int fractional, const char *string)
{
  //Starting at most signicant digit of whole or fractional number.
  *value = 0.0;
  int place = 0;

  //Parse digits to value.
  while(CHAR_IS[*string] & IS_DIGIT_CHAR)
    *value += (*(string++) - '0') * TEN_TO_POWER_NEGATIVE[++place];

  //Digits represent a whole number, not a fractional number. Shift entire
  //value left of the decimal point.
  if(!fractional)
    *value *= TEN_TO_POWER_POSITIVE[place];

  return string;
}


/*
  Returns: Given string pointer if no number was parsed.
           Given string pointer offset to char after number if parsed.
*/
static const char* parseNumber(double *value, const char *string)
{
  //Parse out the numbers components if present.
  double sign, whole, fraction;
  const char *afterSign = parseSign(&sign, string);
  const char *afterWhole = parseDigits(&whole, 0, afterSign);
  const char *afterDecimal = *afterWhole == '.' ? afterWhole + 1 : afterWhole;
  const char *afterFraction = parseDigits(&fraction, 1, afterDecimal);

  //Set default value in case number is not present.
  *value = 0.0;

  //One or more digits parsed, number is present, calculate its value.
  if(afterWhole - afterSign || afterFraction - afterDecimal)
  {
    *value = sign * (whole + fraction);
    string = afterFraction;
  }

  return string;
}


/*
  Returns: Given string pointer if no argument was parsed.
           Given string pointer offset to char after argument if parsed.
*/
static const char* parseArgument(char *argument, double *value, const char *string)
{
  //Set default values in case argument is not present.
  *argument = '\0';
  *value = 0.0;

  //Argument char is not present
  if(!(CHAR_IS[*string] & IS_ARGUMENT_CHAR))
    return string;

  //Parse argument and optional number.
  *argument = *(string++);
  return parseNumber(value, string);
}


/*
  Comment Parsing:
*/


static const char* parseText(char *text, const char *string);

static const char* parseInlineComment(char *text, const char *string);

static const char* parseEndingComment(char *text, const char *string);


int main()
{
  char letter;
  double number;
  char *command = "G01 x23.254";
  const char *after = parseArgument(&letter, &number, command + 4);
  if(after - (command + 4))
    printf("[%c]", letter);
  if(after - (command + 4) > 1)
    printf("[%lf]", number);
  printf("%s\n", after);

  return 0;
}
