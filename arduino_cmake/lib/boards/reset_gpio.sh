#!/bin/bash

# tristate SPI pins
gpio unexportall
for i in 7 8 9 10 11; do gpio -g mode $i in; done
for i in 7 8 9 10 11; do gpio -g mode $i tri; done
echo "unexport done"

# reset pin high to enable AVR
gpio -g mode 8 out
gpio -g write 8 1
echo "reset off"
