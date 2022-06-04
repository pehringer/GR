#include<stdio.h>


static int isArgument(char character)
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


static int isCommand(char character)
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


static int isDigit(char character)
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


static int isEndOfLine(char character)
{
  switch(character)
  {
    case '\n':
    case '\r':
      return 1;
  }
  return 0;
}


static int isWhitespace(char character)
{
  switch(character)
  {
    case ' ':
    case '\t':
      return 1;
  }
  return 0;
}



const char* getWholeNumber(int *number, const char *string)
{
  //Setup for starting at most signicant digit.
  double numberValue = 0.0;
  double placeValue = 1.0;

  //Parse whole number.
  while(isDigit(*string))
    numberValue += (*(string++) - '0') * (placeValue /= 10);
  *number = numberValue / placeValue;

  return string;
}

const char* getFraction(double *number, const char *string)
{
  //Setup for starting at most signicant digit.
  double placeValue = 1.0;
  if(*string == '.')
    string++;

  //Parse fraction.
  while(isDigit(*string))
    *number += (*(string++) - '0') * (placeValue /= 10);

  return string;
}

const char* getSign(int *sign, const char *string)
{
  //Setup for starting at sign.
  *sign = 1;

  //Parse sign.
  if(*string == '+')
    string++;
  else if(*string == '-')
  {
    *sign = -1;
    string++;
  }

  return string;
}


const char* getIntegerNumber(int *number, const char *string)
{
  //Get integer components.
  int sign;
  string = getSign(&sign, string);
  int wholeNumber;
  string = getWholeNumber(&wholeNumber, string);

  //Calculate integer with components
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

  //Calculate decimal with components.
  *number = sign * (wholeNumber + fraction);

  return string;
}


int main()
{
  int number1;
  double number2;
  const char *command = "g-24.1 t-24 x43.12";
  printf("Command: %s\n", command);

  command = getDecimalNumber(&number2, command + 1);
  printf("[%lf]%s\n", number2, command);

  return 0;
}
