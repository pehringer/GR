# G-Code Reader (gcr)

### Functionality
Provides and interface to read in g-code commands from g-code files. Mainly targeted at reading the subset g-code commands and syntax that 3d printer slicers produce.

### Syntax Definitions
The below syntax definitions are in Backus–Naur form (https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_formm)
Any syntax not specified is illegal and will cause an error.



### Allowed Characters
```
<decimal-point-character> ::= "."
<delimiter-character> ::= "\n" | "\r"
<digit-character> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<letter-characters> ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z"
<sign-characters> ::= "-" | "+"
<white-space-characters> ::= " " | "\t"
```

### White Space Syntax
```
<white-space> ::=  "" | <white-space-characters> | <white-space> <white-space-characters>
```

### End of Line Syntax
```
<end-of-line> ::= <delimiters> | <end-of-line> <delimiters>
```

### Number Syntax
```
<sign> ::= "" | <sign-characters>
<whole-number> ::= <digit-character> | <digits> <digit-character>
<decimal-point> ::= "" | <decimal-point-character>
<fractional-number> ::= "" | <digit-character> | <digits> <digit-character>
<integer> = <sign> <whole-number>
<floating-point> ::= <sign> <whole-number> <decimal-point> <fractional-number>
```

###

<line> ::= <end-of-line> | <comment> <end-of-line> | <command> <comment> <end-of-line>
```
