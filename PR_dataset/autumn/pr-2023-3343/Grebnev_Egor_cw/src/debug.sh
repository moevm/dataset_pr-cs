#!/bin/bash

make
echo "----------------------"
./cw < tests/test-cyrillic
echo "----------------------"
make clean