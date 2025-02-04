#!/bin/bash
fileDir='src'

files=(
  'setting.c'
  'network.c'
  'tools.c'
  'main.c'
)

i=${#files[@]}
j=0

str=''

while [ $j -lt $i ]
  do
  str=$str$fileDir'/'${files[$j]}" "
  j=$((j + 1))
done

compileLine="cc -Wall -Werror -Wextra -g $str -o irc_tester"

echo $compileLine
$compileLine
