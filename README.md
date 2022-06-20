# G-Code Reader (gcr)

### Functionality
Provides an interface to read in G-code commands from G-code files. Mainly targeted at reading in the subset G-code commands and syntax that 3d printer slicers produce.

### G-Code Syntax Definitions
Vaild G-code file syntax for the reader are defined below in Backus–Naur form. Any syntax that does not match these definitions will result in an error code and or undefined behavior. The below definitions do not come from any one predefined standard, but rather results of my own research and experience with G-code.

###### Characters Used By Syntax
```
<character> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z" | "|" | " " | "!" | "#" | "$" | "%" | "&" | "(" | ")" | "*" | "+" | "," | "-" | "." | "/" | ":" | ";" | ">" | "=" | "<" | "?" | "@" | "[" | "\" | "]" | "^" | "_" | "`" | "{" | "}" | "~"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<EOL>  ::= "\n" | "\r"
<letter> ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z"
<whitespace> ::= " " | "\t"
```

###### Number Syntax
```
<sign-value> ::= "" | "-" | "+"
<digits-value> ::= <digit> | <digit> <digits-value>
<number-value> ::= <sign-value> <digits-value> | <sign-value> <digits-value> "." | <sign-value> "." <digits-value>| <sign-value> <digits-value> "." <digits-value>
```

###### Spacing Syntax
```
<spacing> ::=  "" | <whitespace> <spacing>
```

###### Parameter Syntax
```
<parameters> ::= "" | <letter> <spacing> <parameters> | <letter> <spacing> <number-value> <spacing> <parameters>
```

###### Command Syntax
```
<command> ::= "" | <letter> <spacing> <number-value> <spacing> <parameters>
```

###### Comment Syntax
```
<text> ::= "" | <character> <text>
<comment> ::= "" | ";" <text>
```

###### Line Syntax
```
<line> ::= <spacing> <command> <comment> <EOL>
```
