#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
NC="\033[0m"

mkdir -p report

# Generate compile_commands.json and clean the cache
cmake --fresh -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build

cppcheck --xml --enable=all --inconclusive --std=c++17 --language=c++ --project=build/compile_commands.json 2> report/result.xml

# If the report contains "cwe=xxx" then it is a CWE issue, exit with 1
if grep -q "cwe=" report/result.xml; then
# count the number of CWE issues
cwe_count=$(grep -o "cwe=" report/result.xml | wc -l)
echo -e "${RED}ATTENTION: ${cwe_count} CWE issue(s) found by cppcheck!${NC}"
exit 1
else
echo -e "${GREEN}cppcheck CWE check passed!${NC}"
fi
