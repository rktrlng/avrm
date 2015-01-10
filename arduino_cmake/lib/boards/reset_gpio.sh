#!/bin/bash

reset_spi()
{
	gpio unexportall
	for i in 7 8 9 10 11; do gpio -g mode $i in; done
	for i in 7 8 9 10 11; do gpio -g mode $i tri; done
	
	echo "tristate spi done"
}

reset_on()
{
	gpio -g mode 8 out
	gpio -g write 8 0
	echo "reset off -> AVR in reset"
}

reset_off()
{
	gpio -g mode 8 out
	gpio -g write 8 1
	echo "reset off -> AVR running"
}

reset_spi
reset_on
reset_off
