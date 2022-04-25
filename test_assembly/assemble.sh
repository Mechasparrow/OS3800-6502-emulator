#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Invalid args, please supply assembly file name"
    exit 64
fi

programfilename=$(echo $1 | cut -d'.' -f 1)

../assembler/vasm6502_oldstyle -Fsrec -s19 -exec=program -o $programfilename.s19 $programfilename.asm