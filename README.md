# G-Code Reader (gcr)

### Functionality
Provides an interface to read in G-code commands from G-code files. Mainly targeted at reading in the subset G-code commands and syntax that 3d printer slicers produce.

### G-Code Syntax Definitions
Vaild G-code file syntax for the reader are defined below in Backus–Naur form. Any syntax that does not match these definitions will result in an error code and or undefined behavior. The below definitions do not come from any one predefined standard, but rather results of my own research and experience with G-code.

###### Characters Used By Syntax
```
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<EOL>  ::= "\n" | "\r"
<letter> ::= "A" | "B" | "C" | "D" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "P" | "Q" | "R" | "S" | "T" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "p" | "q" | "r" | "s" | "t" | "x" | "y" | "z"
```

###### Number Syntax
```
<sign> ::= "-" | "+" | ""
<digits> ::= <digit> | <digit> <digits>
<number> ::= <sign> <digits> | <sign> <digits> "." | <sign> "." <digits>| <sign> <digits> "." <digits> | ""
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
<argument> ::= <letter> <spacing> <number> | ""
```

###### Comment Syntax
```
<in-comment> ::= "(" <text> ")" | ""
<end-comment> ::= ";" <text> | ""
```

###### Line Syntax
```
<contents> ::= <argument> <spacing> <in-comment> <contents> | ""
<line> ::= <line-number> <contents> <end-comment> <EOL>
```
