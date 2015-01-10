#!/bin/bash

reset_spi()
{
	# avrdude-6.1 already handles this nicely, so there should be no need for this
	gpio unexportall
	for i in 7 8 9 10 11; do gpio -g mode $i in; done
	for i in 7 8 9 10 11; do gpio -g mode $i tri; done

	echo "tristate spi done"
}

reset_on()
{
	gpio -g mode 8 out
	gpio -g write 8 0
	echo "reset on -> AVR in reset"
}

reset_off()
{
	gpio -g mode 8 out
	gpio -g write 8 1
	echo "reset off -> AVR running"
}

#reset_spi
reset_on
reset_off
