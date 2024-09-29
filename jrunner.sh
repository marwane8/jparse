#!/bin/bash

make clean && make
cat ./out/sample.json
./build/jparser ./out/sample.json 