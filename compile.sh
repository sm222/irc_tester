#!/bin/bash
fileDir='src'

compileLine="cc -Wall -Werror -Wextra -g $fileDir/main.c $fileDir/tools.c -o irc_tester"

echo $compileLine
$compileLine
