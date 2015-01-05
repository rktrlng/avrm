//
// Gertboard test
//
// SPI (ADC/DAC) control code
//
// This code is part of the Gertboard test suite
// These routines access the AD and DA chips
//
//
// Copyright (C) Gert Jan van Loo & Myra VanInwegen 2012
// No rights reserved
// You may treat this program as if it was in the public domain
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//
// Try to strike a balance between keep code simple for
// novice programmers but still have reasonable quality code
//

#include "common.h"
#include "spi.h"

//
// Set-up the SPI interface
//
// Speed depends on what you talk to
// In this case use 1MHz
//
void setup_spi()
{
  // Want to have 1 MHz SPI clock.
  // Assume 250 Mhz system clock
  // So divide 250MHz system clock by 250 to get 1MHz
  SPI0_CLKSPEED = 250;
  //SPI0_CLKSPEED = 125; // 2MHz
  //SPI0_CLKSPEED = 500; // 0.500MHz / 500KHz
  //SPI0_CLKSPEED = 333.33333; // 0.750MHz / 750KHz
  //SPI0_CLKSPEED = 2000; // 0.125MHz / 125KHz

  // clear FIFOs and all status bits
  SPI0_CNTLSTAT = SPI0_CS_CLRALL;
  SPI0_CNTLSTAT = SPI0_CS_DONE; // make sure done bit is cleared
}

//
// Write a series of bytes to the avrm
//
int counter=0;
void command_avrm(unsigned char a, unsigned char b, unsigned char c, unsigned char d) 
{
	unsigned int sleeptime = 25000;
	
	// Delay to have CS high for a short while
	short_wait();
	
	// Enable SPI: Use CS 1 and set activate bit
	SPI0_CNTLSTAT = SPI0_CS_CHIPSEL1|SPI0_CS_ACTIVATE;
	
	// send the values
	SPI0_FIFO = a;
	usleep(sleeptime); // give MCU the opportunity to handle the spi interrupt.
	SPI0_FIFO = b;
	usleep(sleeptime);
	SPI0_FIFO = c;
	usleep(sleeptime);
	SPI0_FIFO = d;
	usleep(sleeptime);
	
	printf("send: %d %d %d %d ", a, b, c, d);
	counter++;
	
	// wait for SPI to be ready
	// This will take about 16 micro seconds
	int status;
	do {
	 status = SPI0_CNTLSTAT;
	} while ((status & SPI0_CS_DONE)==0);
	SPI0_CNTLSTAT = SPI0_CS_DONE; // clear the done bit
	
	// For every transmit there is also data coming back
	// We MUST read that received data from the FIFO
	// even if we do not use it!
	unsigned char byte1, byte2, byte3, byte4;
	
	byte1 = SPI0_FIFO;
	byte2 = SPI0_FIFO;
	byte3 = SPI0_FIFO;
	byte4 = SPI0_FIFO;
	
	printf("received: %d %d %d %d\n", byte1, byte2, byte3, byte4);
}
