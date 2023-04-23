#!/bin/bash
for((i = 0; i < 1000; i++)) {
    echo $i
    python3 gen2.py > test.in
    ./a < test.in > a.out
}
