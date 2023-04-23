#/bin/bash

for((i = 0; i < 1000; i++)) {
    echo $i
    python3 gen.py > test.in
    ./a < test.in > a.out
    ./b < test.in > b.out
    diff -wq a.out b.out || break
}
