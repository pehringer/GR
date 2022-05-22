# G-Code Reader (gcr)

### Functionality
Provides an interface to read in G-code commands from G-code files. Mainly targeted at reading in the subset G-code commands and syntax that 3d printer slicers produce.

### Syntax Definitions
Vaild G-code file syntax for the reader are defined below in Backus–Naur form. Any syntax that does not match these definitions will result in an error code and or undefined behavior. The definitions do not come from any one predefined standard, but rather results of my own research and experience with G-code.

###### Vaild Characters
```
<command-char>    ::= "G" | "M" | "g" | "m"
<comment-char>    ::= ";"
<digit-char>      ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<delimiter-char>  ::= "\n" | "\r"
<parameter-char>  ::= "E" | "F" | "I" | "P" | "R" | "S" | "T" | "X" | "Y" | "Z" | "e" | "f" | "i" | "p" | "r" | "s" | "t" | "x" | "y" | "z"
<point-char>      ::= "."
<sign-char>       ::= "-" | "+"
<text-char>       ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z" | "|" | " " | "!" | "#" | "$" | "%" | "&" | "(" | ")" | "*" | "+" | "," | "-" | "." | "/" | ":" | ";" | ">" | "=" | "<" | "?" | "@" | "[" | "\" | "]" | "^" | "_" | "`" | "{" | "}" | "~"
<whitespace-char> ::= " " | "\t"
```

###### Numbers
```
<whole-number>   ::= <digit> | <digit-char> <whole-number>
<fraction>       ::= "" | <point-char> | <point-char> <whole-number>
<sign>           ::= "" | <sign-char>
<integer-number> ::= "" | <sign> <whole-number>
<decimal-number> ::= "" | <sign> <whole-number> <fraction>
```

###### whitespace
```
<whitespace>     ::=  "" | <whitespace-char> <whitespace>
```

###### parameters
```
<parameters> ::= "" | <parameter-char> <whitespace-char> <decimal-number> <whitespace-char> <parameters>
```

###### Command 
```
<command> ::= "" | <comamnd-char> <whitespace> <whole-number> <whitespace> <parameters>
```

###### Comment
```
<text> ::= "" | <text-char> <text>
<comment> ::= "" | <comment-char> <text>
```

###### End of Line
```
<end-of-line> ::= <delimiter-char> | <delimiter-char> <mandatory-end-of-line>
```

###### Line
```
<whitespace> <command> <comment> <end-of-line>
```
