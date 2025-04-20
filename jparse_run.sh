#!/bin/bash

make clean && make
echo ' '
# ./bin/jparse ./singles/data_100_flex.json
time ./bin/jparse ./singles/data_10000_flex.json