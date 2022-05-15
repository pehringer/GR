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

###### Allowed Characters
```
<decimal-point-character> ::= "."
<delimiter-character> ::= "\n" | "\r"
<digit-character> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<letter-characters> ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z"
<sign-characters> ::= "-" | "+"
<white-space-characters> ::= " " | "\t"
```

###### White Space Syntax
```
<white-space> ::=  "" | <white-space-characters> | <white-space> <white-space-characters>
```

###### End of Line Syntax
```
<end-of-line> ::= <delimiters> | <end-of-line> <delimiters>
```

###### Number Syntax
```
<sign> ::= "" | <sign-characters>
<whole-number> ::= <digit-character> | <digits> <digit-character>
<decimal-point> ::= "" | <decimal-point-character>
<fractional-number> ::= "" | <digit-character> | <digits> <digit-character>
<integer> = <sign> <whole-number>
<floating-point> ::= <sign> <whole-number> <decimal-point> <fractional-number>
```
