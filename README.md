# jparse
Naive implementation of a JSON parser in C
Parse will be broken down into 3 steps:
1. Lexical - breaks down string into lexical tokens
2. Syntax - creates syntax tree based on structure
3. Datastructure - Dynamic data structure for storing json

Resources:

[Writing a simple json parser](https://notes.eatonphil.com/writing-a-simple-json-parser.html)
[Json Parser](https://www.computerenhance.com/p/initial-haversine-processor-code) - 15:00


## Run Instructions
1. to build and run:
`cd ./src`
`make`
`CMD + SHIFT + B`

## Debug mode
gcc -fdiagnostics-color=always -g -o parse json_parse.c svec.c

## Design Components

#### Lexical Component
example:
```
{ pair : ['x','y']} =>
[ '{',pair',':', '[','x',',', 'y', ']','}']
```
- Should remove comments and white space
- Should handle indefinite string length 
- Returns an array of objects


