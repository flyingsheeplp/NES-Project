#ifndef _CPU_H_
#define _CPU_H_

/********************************************************************************************************************
sp:stack point
ip:program counter
acc:accumulator
x:general register
y:general register
The p_flag register contains the following one bit flags:
Negative (N)
	Set when the result of an operation leaves the high bit set. Cleared otherwise.
	Overflow (V)
	Set when there is a borrow or carry out of an operation.
	Break (B)
	Set when a 'BRK' instruction is encountered.
	Decimal (D)
	When set all arithmatic is BCD (ie. 09+01=10). When clear all arithmatic is binary 2s complement (ie. 09+01=0A).
	Interrupt Disable (I)
	When set no interrupts can occur.
	Zero (Z)
	Set when the result of an operation is zero. Cleared otherwise.
	Carry (C)
	Set when there is a carry. (more here)
	The bit's are arranged as follows (from 7 [highest] to 0 [lowest]): NV-BDIZC
*********************************************************************************************************************/

/*********************************************************************************************************************
	The 65C02 has a 16 bit address space (64K) arranged in 256 pages each of which is 256 bytes long.

	Page 0 ($0000-$00FF) has some special properties involving addressing modes and is very valuable memory.

	Page 1 ($0100-$01FF) is the stack.

	Bytes $FFFA-$FFFB are the NMIB interrupt vector.
	Bytes $FFFC-$FFFD are the reset vector.
	Bytes $FFFE-$FFFF are the IRQ/BRK vector.
*********************************************************************************************************************/
#define CPUMEM_SIZE 64x1024
#define MASKBIT(x) (1<<x)
typedef struct
{
	byte sp;
	byte p_flag;
	word ip;
	byte acc;
	byte x;
	byte y;
	cpu_mem[CPUMEM_SIZE];
}CPU

void init_6502();
void reset_6502();
void VBlank(); /*The VBlank interrupts can be enabled/disabled by writing 1/0 into 7th bit of $2000. */
void maskable_int();/*I don't how it works :(*/

#endif
