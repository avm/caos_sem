#!/bin/bash -efx

touch test.in
echo Something > test.in
rm -f test.out
./ex1 cat test.in test.out
diff test.in test.out