#!/bin/bash

# Generate permutations.
permutations=($(python -c 'from itertools import permutations; print("\n".join(["".join(perm) for perm in permutations("35780")]))'))


# Try them out.
for perm in ${permutations[@]}; do
  echo -n "Checking ${perm}... "
  body="$(curl -s -X POST -F "v=${perm}" https://old-lock-web.2021.ctfcompetition.com/)"
  if echo -ne "${body}"| grep -q 'Hmm no'; then
    echo 'WRONG'
  else
    echo 'RIGHT'
    echo -ne "${body}" | grep -o 'CTF{.*}'
    exit 0
  fi
done

exit 1
