 /*
  Testing DAC and EDMA on XmegaE5.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#if 0
const uint16_t sine[256] = {
	0x800,0x832,0x864,0x896,0x8c8,0x8fa,0x92c,0x95e,0x98f,0x9c0,0x9f1,0xa22,0xa52,0xa82,0xab1,0xae0,
	0xb0f,0xb3d,0xb6b,0xb98,0xbc5,0xbf1,0xc1c,0xc47,0xc71,0xc9a,0xcc3,0xceb,0xd12,0xd39,0xd5f,0xd83,
	0xda7,0xdca,0xded,0xe0e,0xe2e,0xe4e,0xe6c,0xe8a,0xea6,0xec1,0xedc,0xef5,0xf0d,0xf24,0xf3a,0xf4f,
	0xf63,0xf76,0xf87,0xf98,0xfa7,0xfb5,0xfc2,0xfcd,0xfd8,0xfe1,0xfe9,0xff0,0xff5,0xff9,0xffd,0xffe,
	0xfff,0xffe,0xffd,0xff9,0xff5,0xff0,0xfe9,0xfe1,0xfd8,0xfcd,0xfc2,0xfb5,0xfa7,0xf98,0xf87,0xf76,
	0xf63,0xf4f,0xf3a,0xf24,0xf0d,0xef5,0xedc,0xec1,0xea6,0xe8a,0xe6c,0xe4e,0xe2e,0xe0e,0xded,0xdca,
	0xda7,0xd83,0xd5f,0xd39,0xd12,0xceb,0xcc3,0xc9a,0xc71,0xc47,0xc1c,0xbf1,0xbc5,0xb98,0xb6b,0xb3d,
	0xb0f,0xae0,0xab1,0xa82,0xa52,0xa22,0x9f1,0x9c0,0x98f,0x95e,0x92c,0x8fa,0x8c8,0x896,0x864,0x832,
	0x800,0x7cd,0x79b,0x769,0x737,0x705,0x6d3,0x6a1,0x670,0x63f,0x60e,0x5dd,0x5ad,0x57d,0x54e,0x51f,
	0x4f0,0x4c2,0x494,0x467,0x43a,0x40e,0x3e3,0x3b8,0x38e,0x365,0x33c,0x314,0x2ed,0x2c6,0x2a0,0x27c,
	0x258,0x235,0x212,0x1f1,0x1d1,0x1b1,0x193,0x175,0x159,0x13e,0x123,0x10a,0xf2,0xdb,0xc5,0xb0,
	0x9c,0x89,0x78,0x67,0x58,0x4a,0x3d,0x32,0x27,0x1e,0x16,0xf,0xa,0x6,0x2,0x1,
	0x0,0x1,0x2,0x6,0xa,0xf,0x16,0x1e,0x27,0x32,0x3d,0x4a,0x58,0x67,0x78,0x89,
	0x9c,0xb0,0xc5,0xdb,0xf2,0x10a,0x123,0x13e,0x159,0x175,0x193,0x1b1,0x1d1,0x1f1,0x212,0x235,
	0x258,0x27c,0x2a0,0x2c6,0x2ed,0x314,0x33c,0x365,0x38e,0x3b8,0x3e3,0x40e,0x43a,0x467,0x494,0x4c2,
	0x4f0,0x51f,0x54e,0x57d,0x5ad,0x5dd,0x60e,0x63f,0x670,0x6a1,0x6d3,0x705,0x737,0x769,0x79b,0x7cd
};
#else
const uint8_t sine[256] = {
	0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,
	0x98,0x9b,0x9e,0xa2,0xa5,0xa7,0xaa,0xad,
	0xb0,0xb3,0xb6,0xb9,0xbc,0xbe,0xc1,0xc4,
	0xc6,0xc9,0xcb,0xce,0xd0,0xd3,0xd5,0xd7,
	0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,
	0xea,0xeb,0xed,0xee,0xf0,0xf1,0xf3,0xf4,
	0xf5,0xf6,0xf8,0xf9,0xfa,0xfa,0xfb,0xfc,
	0xfd,0xfd,0xfe,0xfe,0xfe,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xfe,0xfe,0xfe,0xfd,
	0xfd,0xfc,0xfb,0xfa,0xfa,0xf9,0xf8,0xf6,
	0xf5,0xf4,0xf3,0xf1,0xf0,0xee,0xed,0xeb,
	0xea,0xe8,0xe6,0xe4,0xe2,0xe0,0xde,0xdc,
	0xda,0xd7,0xd5,0xd3,0xd0,0xce,0xcb,0xc9,
	0xc6,0xc4,0xc1,0xbe,0xbc,0xb9,0xb6,0xb3,
	0xb0,0xad,0xaa,0xa7,0xa5,0xa2,0x9e,0x9b,
	0x98,0x95,0x92,0x8f,0x8c,0x89,0x86,0x83,
	0x80,0x7c,0x79,0x76,0x73,0x70,0x6d,0x6a,
	0x67,0x64,0x61,0x5d,0x5a,0x58,0x55,0x52,
	0x4f,0x4c,0x49,0x46,0x43,0x41,0x3e,0x3b,
	0x39,0x36,0x34,0x31,0x2f,0x2c,0x2a,0x28,
	0x25,0x23,0x21,0x1f,0x1d,0x1b,0x19,0x17,
	0x15,0x14,0x12,0x11,0xf,0xe,0xc,0xb,
	0xa,0x9,0x7,0x6,0x5,0x5,0x4,0x3,
	0x2,0x2,0x1,0x1,0x1,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x2,
	0x2,0x3,0x4,0x5,0x5,0x6,0x7,0x9,
	0xa,0xb,0xc,0xe,0xf,0x11,0x12,0x14,
	0x15,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x23,
	0x25,0x28,0x2a,0x2c,0x2f,0x31,0x34,0x36,
	0x39,0x3b,0x3e,0x41,0x43,0x46,0x49,0x4c,
	0x4f,0x52,0x55,0x58,0x5a,0x5d,0x61,0x64,
	0x67,0x6a,0x6d,0x70,0x73,0x76,0x79,0x7c
};
#endif

void clock_32MHz_RC(void)
{   
    OSC.CTRL |= OSC_RC32MEN_bm;
    while ((OSC.STATUS & OSC_RC32MRDY_bm) == 0);
    CCP = CCP_IOREG_gc;
    CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
    OSC.CTRL &= ~OSC_RC2MEN_bm;
}

int main(void)
{
    clock_32MHz_RC();

    // DACA channel 0
    PORTA.DIRSET = PIN2_bm;
    DACA.CTRLA = DAC_CH0EN_bm | DAC_ENABLE_bm;
    DACA.CTRLB = DAC_CHSEL_SINGLE_gc;
    DACA.CTRLC = DAC_REFSEL_AREFA_gc | DAC_LEFTADJ_bm;
    
    uint32_t phaseCounter = 0;
    uint32_t phaseIncrement = 10000000;

    while(1)
    {
    	phaseCounter += phaseIncrement;    	
		DACA.CH0DATAH = sine[phaseCounter >> 24];		
		while(!(DACA.STATUS & 1));
    }

    return 0;
}
