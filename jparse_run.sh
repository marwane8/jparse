#!/bin/bash

make clean && make
echo ' '
./bin/jparse ./sample.json 