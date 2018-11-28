PLANESPOTTER
============

[![Build Status](https://travis-ci.com/cmbahadir/PlaneSpotter.svg?branch=master)](https://travis-ci.com/cmbahadir/PlaneSpotter)
[![Coverage Status](https://coveralls.io/repos/github/cmbahadir/PlaneSpotter/badge.svg?branch=master)](https://coveralls.io/github/cmbahadir/PlaneSpotter?branch=master)

This project gets the data from 30003 port of dump1090 instance (https://github.com/antirez/dump1090) and publishes it to a messaging queue(still being implemented) for further analysis. You need to have a running dump1090 with --net argument.

FEATURES TO BE IMPLEMENTED
==========================

- Publish SBS Words to a AMQP Message Broker
- Analyze the task queue on RabbitMQ
- Cache the analyzed data on Redis 
- Try to predict the closest airport location.

