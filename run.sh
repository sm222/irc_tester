#!/bin/bash

ip=""
port="6667"

cc -Wall -Werror -Wextra testSpam.c -o 'irc_tester'

./irc_tester files/test1.txt | nc $ip $port -CN