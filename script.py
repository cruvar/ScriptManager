#!/usr/bin/python
# -*- coding: UTF-8 -*-

import subprocess
import sys
import locale

## command to run - tcp only ##
IP = '8.8.8.100'
ping_command = "ping " + IP 

process = subprocess.Popen(ping_command
                            , stdout=subprocess.PIPE
                            , stderr=subprocess.PIPE)

while True:
    out = process.stdout.read(1)
    if out == '' and process.poll() != None:
        break
    if out != '':
        sys.stdout.write(out.decode(encoding='windows-1251'))
        sys.stdout.flush()