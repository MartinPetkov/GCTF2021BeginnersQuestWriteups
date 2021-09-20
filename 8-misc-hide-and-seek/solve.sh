#!/usr/bin/env bash

#pngcheck -tf hideandseek.png

exiv2 -pS hideandseek.png | grep 'eDIH' | awk '{print $7}' | perl -pe 'chomp' | base64 -d
