# G-code Reader (GR)

### Functionality
Provides an interface to read in G-code commands from G-code files. Mainly targeted at reading in the subset of G-code syntax that 3D printer slicers produce. The code is highly portable and designed to be runnable on small 8-bit microcontrollers.

### G-Code Syntax Definitions
Vaild G-code file syntax for the reader are defined below in Backus–Naur form. Any syntax that does not match these definitions will result in an error code and or undefined behavior. The below definitions do not come from any one predefined standard, but rather results of my own research and experience with G-code.

###### Syntax Equivalent Characters
```
<argumentChar> ::= "A" | "B" | "C" | "D" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "P" | "Q" | "R" | "S" | "T" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "p" | "q" | "r" | "s" | "t" | "x" | "y" | "z" | "*"
<digitChar> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<newlineChar> ::= "\n" | "\r"
<textChar> ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z" | "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "|" | "!" | "#" | "$" | "%" | "&" | "*" | "+" | "," | "-" | "." | "/" | ":" | ";" | ">" | "=" | "<" | "?" | "@" | "[" | "\" | "]" | "^" | "_" | "`" | "{" | "}" | "~" | " " | "\t"
<whitespaceChar> ::= " " | "\t"
```

###### Argument Syntax
```
<Sign> ::= "+" | "-" | ""
<Digits> ::= <digitChar> <Digits> | <digitChar>
<Number> ::= <Sign> <Digits> | <Sign> <Digits> "." | <Sign> <Digits> "." <Digits> | <Sign> "." <Digits> | ""
<Argument> ::= <argumentChar> <Number>
```

###### Comment Syntax
```
<Text> ::= <textChar> <Text> | ""
<InlineComment> ::= "(" <Text> ")"
<EndingComment> ::= ";" <Text> | ""
```

###### Newline Syntax
```
<Newline> ::= <newlineChar> <Newline> | <newlineChar>
```

###### Whitespace Syntax
```
<Whitespace> ::= <whitespaceChar> <whitespace> | <whitespaceChar>
```

###### Line Syntax
```
<Line> ::= <Argument> <Line> | <InlineComment> <Line> | <Whitespace> <Line> | <EndingComment> <Newline> | <Newline>
```
