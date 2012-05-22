/***********************************************************************************
 *							CPU.C
 *		       implement cpu behaviors
 *			emulate the instructions run on our cpu structure
 *			author: Li PenG
 ***********************************************************************************/
#include "type.h"
#include "cpu.h"
#include "global.h"

#define SP cpu6502.sp
#define FP cpu6502.p_flag
#define IP cpu6502.ip
#define ACC cpu6502.acc
#define X cpu6502.x
#define Y cpu6502.y
#define MEM cpu6502.cpu_mem
#define INS_NUM 256

/*macros for flag register control*/
#define _SET_BIT(x) cpu6502.p_flag |= (1 << x)
#define SET_BIT(x) _SET_BIT(x)
#define _CLEAR_BIT(x) cpu6502.p_flag &= ~(1<<x)
#define CLEAR_BIT(x) _CLEAR_BIT(x)

byte value = 0; /*store operand value to exec because of addr mode*/

extern struct CPU cpu6502;
/*Jump table for instructions*/
typedef void (*instruction[INS_NUM])();
typedef void (*addressmode[INS_NUM])();
byte ticks[INS_NUM]={0};

void init_6502()
{	
	//1.set registers' value
	//2.init jump table,format follows
	//instruction[]= ;addressmode[]= ;ticks[]= ;
	
}

void reset_6502()
{
	//fuck..
}

void VBlank()
{
	//fuck..
}

/*Address Mode for 6502*/
/*Each mode have different num of opcodes,so our IP register need to calculatehow many byte we need to jump over,there are 11 addressing modes for 6502*/

void immediate()
{
	value = IP++;
}

void absolute()
{
	value = MEM[IP+1] + (MEM[IP+2] << 8);
	IP++;
	IP++;
}

void zero_absolute()
{
	value = MEM[IP+1];
	IP++;
	IP++;
}

void implied(){/*nothing to do*/}

void accumulator(){/*nothing*/}
void indexed_x()
{
	value = MEM[IP+1] + (MEM[IP+2]<<8)+X;
	IP++;
	IP++;
}
void indexed_y()
{
	value = MEM[IP+1] + (MEM[IP+2]<<8)+Y;
	IP++;
	IP++;
}
void zero_indexed(){}
void indirect(){}
void pre_indexed_indirect(){}
void post_indexed_indirect(){}
void relative(){}




/*INSTRUCTIONS...so many..*/
/*alphabetic sequence*/
///fuck.......fuck.............fuck...............

void adc(){}
void and(){}
void asl(){}
void bcc(){}
void bcs(){}
void beq(){}
void bit(){}
void BMI(){}
void BNE(){}
void BPL(){}
void brk(){}
void bvc(){}
void bvs(){}
void clc(){}
void cld(){}
void cli(){}
void clv(){}
void cmp(){}
void cpx(){}
void cpy(){}
void dec(){}
void dex(){}
void dey(){}
void eor(){}
void inc(){}
void inx(){}
void iny(){}
void jmp(){}
void jsr(){}
void lda(){}
void ldx(){}
void ldy(){}
void lsr(){}
void nop(){}
void ora(){}
void pha(){}
void php(){}
void pla(){}
void plp(){}
void rol(){}
void ror(){}
void rti(){}
void rts(){}
void sbc(){}
void sec(){}
void sed(){}
void sei(){}
void sta(){}
void stx(){}
void sty(){}
void tax(){}
void tay(){}
void tsx(){}
void txa(){}
void txs(){}
void tya(){}
/*end of instruction..fuck.*/
