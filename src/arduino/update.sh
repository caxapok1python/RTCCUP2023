#!/bin/sh

git pull
arduino-cli compile -b arduino:avr:mega && arduino-cli upload -b arduino:avr:mega -p /dev/ttyUSB0