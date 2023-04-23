#!/bin/bash

for((i = 0; i < 1000; i++)) {
    echo $i
    python gen.py > test.in
    ./a < test.in > a.out
    ./c < a.out > c.out
    diff -wqw c.out g.out || break
}
