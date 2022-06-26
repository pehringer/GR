# G-Code Reader (gcr)

### Functionality
Provides an interface to read in G-code commands from G-code files. Mainly targeted at reading in the subset G-code commands and syntax that 3d printer slicers produce.

### G-Code Syntax Definitions
Vaild G-code file syntax for the reader are defined below in Backus–Naur form. Any syntax that does not match these definitions will result in an error code and or undefined behavior. The below definitions do not come from any one predefined standard, but rather results of my own research and experience with G-code.

###### Characters Used By Syntax
```
<argument-char> ::= "A" | "B" | "C" | "D" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "P" | "Q" | "R" | "S" | "T" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "p" | "q" | "r" | "s" | "t" | "x" | "y" | "z"
<digit-char> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```

###### Number Syntax
```
<sign> ::= "-" | "+" | ""
<digits> ::= <digit-char> <digits> | <digit-char> 
```

###### Line Number Syntax
```
<line-number> ::= "N" <digits> | "n" <digits> | ""
```

###### Whitespace Syntax
```
<whitespace> ::= " " <whitespace> | "\t" <whitespace> | ""
```

###### Argument Syntax
```
<argument> ::= <argument-char> | <argument-char> <sign> <digits> | <argument-char> <sign> <digits> "." | <argument-char><sign> "." <digits>| <argument-char> <sign> <digits> "." <digits> | ""
<argument-list> ::= <argument> <whitespace> <arguments> | <argument>
<arguments> = <argument-list> | ""
```

###### Checksum Syntax
```
<checksum> ::= "*" <digits> | ""
```

###### Comment Syntax
```
<text> ::= <text-char> <opt-text> | ""
<comment> ::= ";" <text> | ""
```

###### End Of Line Syntax
```
<end-of-line> ::= "\n" <end-of-line> | "\r" <end-of-line> | "\n" | "\r"
```
