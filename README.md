# G-Code Reader (gcr)

### Functionality
Provides an interface to read in G-code commands from G-code files. Mainly targeted at reading in the subset G-code commands and syntax that 3d printer slicers produce.

### G-Code Syntax Definitions
Vaild G-code file syntax for the reader are defined below in Backus–Naur form. Any syntax that does not match these definitions will result in an error code and or undefined behavior. The below definitions do not come from any one predefined standard, but rather results of my own research and experience with G-code.

###### Syntax Equivalent Characters
```
<argument-char> ::= "A" | "B" | "C" | "D" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "P" | "Q" | "R" | "S" | "T" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "p" | "q" | "r" | "s" | "t" | "x" | "y" | "z" | "*"
<digit-char> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<newline-char> ::= "\n" | "\r"
<text-char> ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z" | "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "|" | "!" | "#" | "$" | "%" | "&" | "*" | "+" | "," | "-" | "." | "/" | ":" | ";" | ">" | "=" | "<" | "?" | "@" | "[" | "\" | "]" | "^" | "_" | "`" | "{" | "}" | "~" | " " | "\t"
<whitespace-char> ::= " " | "\t"
```

###### Argument Syntax
```
<sign> ::= "+" | "-" | ""
<digits> ::= <digit-char> <digits> | <digit-char>
<number> ::= <sign> <digits> | <sign> <digits> "." | <sign> <digits> "." <digits> | <sign> "." <digits> | ""
<argument> ::= <argument-char> <number>
```

###### Comment Syntax
```
<text> ::= <text-char> <text> | ""
<inline-comment> ::= "(" <text> ")"
<ending-comment> ::= ";" <text> | ""
```

###### Newline Syntax
```
<newline> ::= <newline-char> <newline> | <newline-char>
```

###### Whitespace Syntax
```
<whitespace> ::= <whitespace-char> <whitespace> | <whitespace-char>
```

###### Line Syntax
```
<contents> ::= <argument> <contents> | <inline-comment> <contents> | <whitespace> <contents> | ""
<line> ::= <contents> <ending-comment> <newline>
```
