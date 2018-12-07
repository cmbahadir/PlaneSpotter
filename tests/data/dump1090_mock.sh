#!/bin/bash
~/dump1090/dump1090 --net-only&
netcat localhost 30001 < test_data.txt