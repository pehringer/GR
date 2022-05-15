# G-Code Reader (gcr)

### Functionality
Provides and interface to read in G-code commands from G-code files. Mainly targeted at reading the subset G-code commands and syntax that 3d printer slicers produce.

### Syntax Definitions
Vaild G-code file syntax for the G-Code Reader (gcr) are defined below in Backus–Naur form. Any syntax that does not match these definitions will result in an error code and or undefined behavior. The definitions do not come from any one predefined standard, but rather results of my own research and experience with G-code.

### Backus–Naur Form Exmaple.
Backus–Naur form is a simple and precise way of expressing language syntax. For example a binary number can be defined in Backus–Naur form with the following:
```
<binary-number> ::= "0" | "1" | <binary-number> "0" | <binary-number> "1"
```
Where ```<binary-number> ::=``` defines that the tag ```binary-number``` is equivalent to the expression ```"0" | "1" | <binary-number> "0" | <binary-number> "1"```. Which expresses that a ```binary-number``` can equal the digit 0, OR can equal the digit 1, OR can equal another ```binary-number``` expression and the digit 0, OR can equal another ```binary-number``` expression and the digit 1. It is helpful to think of the plain symbols as functioning like a recursive functions base case, and the tags as functioning like a recursive functions recursive call. Backus–Naur form's simple OR and recursive operations allow for very complex definitions.

###### Vaild Characters
```
<command-char> ::= "G" | "M" | "g" | "m"

<digit-char> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"

<delimiter-char> ::= "\n" | "\r"

<parameter-char> ::= "E" | "F" | "I" | "P" | "R" | "S" | "T" | "X" | "Y" | "Z" | "e" | "f" | "i" | "p" | "r" | "s" | "t" | "x" | "y" | "z"

<point-char> ::= "."

<sign-char> ::= "-" | "+"

<whitespace-char> ::= " " | "\t"
```

###### whitespace
```
<whitespace> ::=  "" | <whitespace-char> | <whitespace> <whitespace-char>
```

###### End of Line
```
<end-of-line> ::= <delimiter-char> | <end-of-line> <delimiter-char>
```

###### Numbers
```
<sign> ::= "" | <sign-char>

<whole-number> ::= <digit-char> | <whole-number> <digit-char>

<decimal-point> ::= "" | <point-char>

<fractional-number> ::= "" | <fractional-number> <digit-char>

<integer> = <whitespace> <sign> <whole-number>

<floating-point> ::= <whitespace> <sign> <whole-number> <decimal-point> <fractional-number>
```

###### Parameter
```
<parameter> ::= "" | <parameter> <whitespace> <parameter-char> <floating-point>
```

###### Command
```
<command> ::= "" | <whitespace> <comamnd-char> <integer> <parameter>
```






