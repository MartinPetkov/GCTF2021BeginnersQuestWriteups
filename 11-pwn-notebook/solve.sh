#!/bin/bash

./gencommands.sh >commands.txt
./connect.sh <commands.txt | grep '^<.*>$' | grep -v 'nil' | tr -d '<>' >hexdump.txt
while read line; do
  echo "${line} -> $(echo ${line} | xxd -r -p)"
done <hexdump.txt

# You get this
# 0x696d655200000000 -> imeR
# 0x5443203a7265646e -> TC :redn
# 0x74616d726f667b46 -> tamrof{F
# 0x5f676e697274735f -> _gnirts_
# 0x5f6568745f726f66 -> _eht_rof
# 0x7d6e6977 -> }niw

