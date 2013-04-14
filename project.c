// Brandon Forster
// Michael Andacht
// CDA 3103 - Computer Logic and Organization
// 22 April 2013
// MySPIM
// A simple MIPS simulator

#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{

}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	//Check the proper part for the memory index
	unsigned MemoryIndex = PC >> 2;
    
	//Check if it in proper word-aligned format (multiple of 4)
    if (PC % 4 == 0) {     
           
           *instruction = Mem[MemoryIndex];
           
           return 0;
           
           }
	//If not Halt
    else 
    return 1; 
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
	//Switch for different Op codes to decode 
	//TODO get proper OP codes and proper values
	switch(op) {
	case 000: 
		break;
	case 001:
		break;
	case 010:
		break;
	case 011: 
		break;
	case 100:  
		break;
	case 101:  
		break;
	case 110: 
		break;
	case 111:  
		break;
	default:
		return 1;
	}
	return 0;
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
	//Not sure this is right
	*extended_value = offset; 
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
	//Possiblly right seems to simple.
	if (MemRead == 1) {
		*memdata = Mem[ALUresult];
    }

    if (MemWrite == 1) {
		Mem[ALUresult] = data2;
    }
                           
    return 0; 
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
	 // If Mem to Register
     if (MemtoReg == 1 && RegDst == 0) {
		Reg[r2] = memdata;
     }

	 //If Mem to Register but r3

	 else if(MemtoReg == 1 && RegDst == 1){
		 Reg[r3] = memdata;
	 }
     
	 // If Result to Register
     else if (MemtoReg == 0 && RegDst == 0) {
		Reg[r2] = ALUresult;
     }
                  
	 // If Result to Register but next value
     else if (MemtoReg == 0 && RegDst == 1){
		Reg[r3] = ALUresult;
     }
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

