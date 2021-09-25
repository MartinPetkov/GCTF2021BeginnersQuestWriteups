#!/bin/bash

./dumpmemory.sh 2>/dev/null | grep -A5 -- '-> Remi' | cut -d' ' -f3- | tr -d '[:space:]' | grep -o 'CTF{.*}'
