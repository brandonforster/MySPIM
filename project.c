// Brandon Forster
// Michael Andacht
// CDA 3103 - Computer Logic and Organization
// 22 April 2013
// MySPIM
// A simple MIPS simulator
// Complete Git repository (with contributions and issue tracking) available at https://github.com/brandonforster/MySPIM

#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	// Switch to control which ALU control gets executed
	switch ((int) ALUControl)
	{
		// 000: Z = A + B
		case 000:
			*ALUresult = A + B;
			*Zero = (char)0;

		// 001: Z = A - B
		case 001:
			*ALUresult = A - B;
			*Zero = (char)0;

		// 010: if A < B, Z = 1; otherwise, Z = 0
		case 010:
			//@TODO this is the same as 011, I don't think it's supposed to be
			if (A < B)
			{
				*ALUresult = 1;
				*Zero = (char)0;
			}
			else
			{
				*ALUresult = 0;
				*Zero = (char)1;
			}

		// 011: if A < B, Z = 1; otherwise, Z = 0 (A and B are unsigned integers)
		case 011:
			//@TODO this is the same as 010, I don't think it's supposed to be
			if (A < B)
			{
				*ALUresult = 1;
				*Zero = (char)0;
			}
			else
			{
				*ALUresult = 0;
				*Zero = (char)1;
			}

		// 100: Z = A AND B
		case 100:
			//@TODO- using bitwise and, is this right?
			*ALUresult = A & B;

		// 101: Z = A OR B
		case 101:
			//@TODO- using bitwise or, is this right?
			*ALUresult = A | B;

		// 110: Shift left B by 16 bits
		case 110:
			B << 16;

		// 111: Z = NOT A
		case 111:
			*ALUresult = !A;

		// bad input, handle error?
		default:
			break;
	}
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{

}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

