#!/bin/bash

##./dump1090 --interactive

dump1090Path=/var/www/html/dump1090/

$dump1090Path/dump1090 --interactive --ifile $dump1090Path/testfiles/modes1.bin
