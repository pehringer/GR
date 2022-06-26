# G-Code Reader (gcr)

### Functionality
Provides an interface to read in G-code commands from G-code files. Mainly targeted at reading in the subset G-code commands and syntax that 3d printer slicers produce.

### G-Code Syntax Definitions
Vaild G-code file syntax for the reader are defined below in Backus–Naur form. Any syntax that does not match these definitions will result in an error code and or undefined behavior. The below definitions do not come from any one predefined standard, but rather results of my own research and experience with G-code.

###### Characters Used By Syntax
```
<digit-char> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<letter-char> ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z"
<symbol-char> ::=  "|" | " " | "!" | "#" | "$" | "%" | "&" | "(" | ")" | "*" | "+" | "," | "-" | "." | "/" | ":" | ";" | ">" | "=" | "<" | "?" | "@" | "[" | "\" | "]" | "^" | "_" | "`" | "{" | "}" | "~"
```

###### Number Syntax
```
<sign> ::= "-" | "+" | ""
<digits> ::= <digit-char> <digits> | <digit-char>
<rational-number> ::= <sign> <digits> | <sign> <digits> "." | <sign> "." <digits>| <sign> <digits> "." <digits> | ""
```

###### Whitespace Syntax
```
<whitespace> ::= " " <whitespace> | "\t" <whitespace> | ""
```

###### Line Number Syntax
```
<line-number> ::= "N" <digits> | "n" <digits> | ""
```

###### Argument Syntax
```
<argument> ::= <letter-char> <whitespace> <rational-number> | ""
```

###### Comment Syntax
```
<text> ::= <digit-char> <text> | <letter-char> <text> | <symbol-char> <text> | <whitespace> <text> | ""
<inline-comment> ::= "(" <text> ")" | ""
<end-of-line-comment> ::= ";" <text> | ""
```

###### End Of Line Syntax
```
<end-of-line> ::= "\n" <end-of-line> | "\r" <end-of-line> | "\n" | "\r"
```

###### Line Syntax
```
<contents> ::= <argument> <inline-comment> <whitespace> <contents> | ""
<line> ::= <line-number> <contents> <end-of-line-comment> <end-of-line>
```
