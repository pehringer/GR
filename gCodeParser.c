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


static enum CharType {
  ARGUMENT   = 0x01,
  DIGIT      = 0x02,
  NEWLINE    = 0x04,
  TEXT       = 0x08,
  WHITESPACE = 0x10
} placeHolderForCompileError;


/*
  returns: Non zero if given type is equivalent to given character.
           Zero if given type is not equivalent to given character.
  type: Type of character.
  character: Character to compare against type.
*/
static int Equivalent(enum CharType type, char character)
{
  static const char uses[] =
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
    0x04, //010 '\n'
    0x00, //011
    0x00, //012
    0x04, //013 '\r'
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
    0x09, //069 'E'
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

  return uses[character] & type;
}


/*
  Parsing:
*/


/*
  returns: Pointer to char after sign.
  value: Always filled.
  string: Points to possible sign to parse.
*/
static const char* ParseSign(double *value, const char *string)
{
  //Numbers are default positive if no sign is present.
  *value = 1.0;
  //Check for sign.
  switch(*string)
  {
    case '-': *value = -1.0;
    case '+': string++;
  }
  return string;
}


/*
  returns: Given string if not parsed.
           Pointer to char after digits if parsed.
  value: Filled if (returned pointer > given string pointer).
  fractional: Non-zero if digits are right of the decimal point.
            Zero if digits are left of the decimal point.
  string: Points to possible digits to parse.
*/
static const char* ParseDigits(double *value, int fractional, const char *string)
{
  //Starting at most signicant digit of whole or fractional number.
  *value = 0.0;
  int place = 0;
  //Parse digits to value.
  while(Equivalent(DIGIT, *string))
    *value += (*(string++) - '0') * TEN_TO_POWER_NEGATIVE[++place];
  //Digits represent a whole number, not a fractional number. Shift entire
  //value left of the decimal point.
  if(!fractional)
    *value *= TEN_TO_POWER_POSITIVE[place];

  return string;
}


/*
  returns: Given string if not parsed.
           Pointer to char after number if parsed.
  value: Filled if (returned pointer > given string pointer).
  string: Points to possible number to parse.
*/
static const char* ParseNumber(double *value, const char *string)
{
  //Parse out the numbers components if present.
  double sign, whole, fraction;
  const char *afterSign = ParseSign(&sign, string);
  const char *afterWhole = ParseDigits(&whole, 0, afterSign);
  const char *afterDecimal = *afterWhole == '.' ? afterWhole + 1 : afterWhole;
  const char *afterFraction = ParseDigits(&fraction, 1, afterDecimal);
  //No digits parsed, no number.
  if( !((afterWhole - afterSign) + (afterFraction - afterDecimal)) )
    return string;
  //Calculate numbers value.
  *value = sign * (whole + fraction);
  return afterFraction;
}


/*
  returns: Given string if not parsed.
           Pointer to char after argument if parsed.
  letter: Filled if (returned pointer > given string pointer).
  value: Filled if (returned pointer > given string pointer + 1).
  string: Points to possible argument to parse.
*/
static const char* ParseArgument(char *letter, double *value, const char *string)
{
  //No argument.
  if(!Equivalent(ARGUMENT, *string))
    return string;
  //Parse argument and optional number.
  *letter = *string;
  return ParseNumber(value, ++string);
}


/*
  returns: Given string if not parsed.
           Pointer to char after chars of given type if parsed.
  string: Points to possible chars of given type to parse.
*/
static const char* Parse(enum CharType type, const char* string)
{
  //Skip chars of given type.
  while(Equivalent(type, *string))
    string++;
  return string;
}


/*
  returns: Given string if not parsed.
           Pointer to char after inline comment if parsed.
  string: Points to possible inline comment to parse.
*/
static const char* ParseInlineComment(const char *string)
{
  //No opening parenthesis.
  if(*string != '(')
    return string;
  //Parse Optional text.
  const char *afterText = Parse(TEXT, string + 1);
  //No closing parenthesis.
  if(*afterText != ')')
    return string;
  //Char after closing parenthesis.
  return ++afterText;
}


/*
  returns: Given string if not parsed.
           Pointer to char after ending comment if parsed.
  string: Points to possible ending comment to parse.
*/
static const char* ParseEndingComment(const char *string)
{
  //No starting semicolon.
  if(*string != ';')
    return string;
  //Parse Optional text.
  return Parse(TEXT, ++string);
}





int main()
{
  char *command = "G01 X10.44 (okay boomer)  Y0.031;\t \tlotta space\n\r"
                  "G42 X Y Z; all axes.\n"
                  ";End of g-code\n";
  char letter;
  double number;

  const char *after = ParseArgument(&letter, &number, (command+12));
  if(after - (command+12) > 0)
    printf("[%c]", letter);
  if(after - (command+12) > 1)
    printf("[%lf]", number);
  printf("%s\n", after);

  return 0;
}
