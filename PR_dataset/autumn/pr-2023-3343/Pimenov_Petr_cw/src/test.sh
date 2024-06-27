#!/bin/bash

testsCount=$(ls ./test/in | wc -l)
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[1;33m"
NC="\033[0m"
make clean
make
for ((i = 1; i <= testsCount; i++)); do
    output=$(./cw <./test/in/test$i)
    expectedOutput=$(<./test/out/test$i)
    if [ "$output" = "$expectedOutput" ]; then
        echo -e "${GREEN}Test $i passed!${NC}"
    else
        echo -e "${RED}Test $i failed!${NC}"
        echo -e "${YELLOW}Actual output:${NC}"
        echo "$output"
        echo -e "${YELLOW}Expected output:${NC}"
        echo "$expectedOutput"
        echo ""
        echo ""
    fi
done
