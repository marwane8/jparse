#!/bin/bash

export MallocStackLogging=1
make clean && make
leaks --list --atExit -- ./build/jparser ./out/sample.json 