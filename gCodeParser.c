#include<stdio.h>


/*
  Structures and Enumeration Below:
*/





/*
  Lookup Tables Below:
*/


double tenToThePowerOfNegative[] =
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


double tenToThePowerOfPositive[] =
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


static int isCharArgument(char character)
{
  switch(character)
  {
    case 'E':
    case 'F':
    case 'I':
    case 'P':
    case 'R':
    case 'S':
    case 'T':
    case 'X':
    case 'Y':
    case 'Z':
    case 'e':
    case 'f':
    case 'i':
    case 'p':
    case 'r':
    case 's':
    case 't':
    case 'x':
    case 'y':
    case 'z':
      return 1;
  }
  return 0;
}


static int isCharCommand(char character)
{
  switch(character)
  {
    case 'G':
    case 'M':
    case 'g':
    case 'm':
      return 1;
  }
  return 0;
}


static int isCharDigit(char character)
{
  switch(character)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return 1;
  }
  return 0;
}


static int isCharEndOfLine(char character)
{
  switch(character)
  {
    case '\n':
    case '\r':
      return 1;
  }
  return 0;
}


static int isCharSign(char character)
{
  switch(character)
  {
    case '+':
      return 1;
    case '-':
      return -1;
  }
  return 0;
}


static int isCharWhitespace(char character)
{
  switch(character)
  {
    case ' ':
    case '\t':
      return 1;
  }
  return 0;
}


/*
  Number Parsing Below:
*/


const char* getWholeNumber(int *number, const char *string)
{
  //Setup for starting at most signicant digit.
  int placeValue = 0;
  double numberValue = 0.0;

  //Parse whole number.
  while(isCharDigit(*string))
    numberValue += (*(string++) - '0') * tenToThePowerOfNegative[++placeValue];
  numberValue *= tenToThePowerOfPositive[placeValue];

  //Return number and position.
  *number = (int) numberValue;
  return string;
}


const char* getFraction(double *number, const char *string)
{
  //Setup for starting at most signicant digit.
  int placeValue = 0;
  double numberValue = 0;
  if(*string == '.')
    string++;

  //Parse fraction.
  while(isCharDigit(*string))
    numberValue += (*(string++) - '0') * tenToThePowerOfNegative[++placeValue];

  //Return number and position.
  *number = numberValue;
  return string;
}


const char* getSign(int *sign, const char *string)
{
  //Setup for starting at sign.
  int signValue = isCharSign(*string);

  //Parse sign.
  if(signValue)
    string++;
  else
    signValue = 1;

  //Return sign and position.
  *sign = signValue;
  return string;
}


const char* getIntegerNumber(int *number, const char *string)
{
  //Get integer components.
  int sign;
  string = getSign(&sign, string);
  int wholeNumber;
  string = getWholeNumber(&wholeNumber, string);

  //Calculate integer with components and return position.
  *number = sign * wholeNumber;
  return string;
}


const char* getDecimalNumber(double *number, const char *string)
{
  //Get decimal components.
  int sign;
  string = getSign(&sign, string);
  int wholeNumber;
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


const char* getCommand(char *type, int *number, const char *string)
{
  *type = '\0';
  *number = 0;

  //No command type found.
  if(!isCharCommand(*string))
    return string;

  //No command number found.
  const char *afterNumber = getWholeNumber(number, string + 1);
  if(afterNumber == string + 1)
    return string;

  //Get command type.
  *type = *string;

  return afterNumber;
}






int main()
{
  char character;
  int integer;
  double decimal;

  const char *remainingCommand = "M02 t-24 x43.12";
  printf("Command: %s\n", remainingCommand);

  remainingCommand = getCommand(&character, &integer, remainingCommand);
  printf("[%c][%d]%s\n", character, integer, remainingCommand);

  return 0;
}
