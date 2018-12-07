#!/bin/bash

process_id=$(pgrep dump1090 | sed 's/^[ \t]*//;s/[ \t]*$//')
echo $process_id

if [[ ! -z $process_id ]]
then
    echo "dump1090 already running with pid:" $process_id
    kill $process_id
fi

~/dump1090/dump1090 --net-only&
netcat localhost 30001 < test_data.txt