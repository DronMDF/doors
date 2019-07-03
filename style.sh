#!/bin/sh

set -ue
set -x

cppcheck --enable=all --quiet .

cpplint `find ./ -name "*.cpp" -o -name "*.h"`

pycodestyle --config=pycodestyle.cfg .

# Scan sources for wrong pdd tokens
pdd > /dev/null

echo "Success"
