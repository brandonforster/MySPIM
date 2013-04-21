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
		break;

		// 001: Z = A - B
	case 001:
		*ALUresult = A - B;
		*Zero = (char)0;
		break;

		// 010: if A < B, Z = 1; otherwise, Z = 0
	case 010:
		if ((signed)A < (signed)B)
		{
			*ALUresult = 1;
			*Zero = (char)0;
		}
		else
		{
			*ALUresult = 0;
			*Zero = (char)1;
		}
		break;

		// 011: if A < B, Z = 1; otherwise, Z = 0 (A and B are unsigned integers)
	case 011:
		if ((unsigned)A < (unsigned)B)
		{
			*ALUresult = 1;
			*Zero = (char)0;
		}
		else
		{
			*ALUresult = 0;
			*Zero = (char)1;
		}
		break;

		// 100: Z = A AND B
	case 100:
		//@TODO- using bitwise and, is this right?
		*ALUresult = A & B;
		break;

		// 101: Z = A OR B
	case 101:
		//@TODO- using bitwise or, is this right?
		*ALUresult = A | B;
		break;

		// 110: Shift left B by 16 bits
	case 110:
		B << 16;
		break;

		// 111: Z = NOT A
	case 111:
		*ALUresult = !A;
		break;

		// bad input, handle error?
	default:
		break;
	}
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
	// we will use these masks to only change values we want
	unsigned opMask		= 0x7e000000;	// instruction [31-26]
	unsigned r1Mask		= 0x1f000000;	// instruction [25-21]
	unsigned r2Mask		= 0x000f8000;	// instruction [20-16]
	unsigned r3Mask		= 0x00007c00;	// instruction [15-11]
	unsigned functMask	= 0x0000003f;	// instruction [5-0]
	unsigned offsetMask	= 0x0000ffff;	// instruction [15-0]
	unsigned jsecMask	= 0x01ffffff;	// instruction [25-0]

	// apply masks
	*op		= instruction & opMask;
	*r1		= instruction & r1Mask;
	*r2		= instruction & r2Mask;
	*r3		= instruction & r3Mask;
	*funct	= instruction & functMask;
	*offset	= instruction & offsetMask;
	*jsec	= instruction & jsecMask;
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	//Switch for different Op codes to decode 
	//TODO Get proper Op codes and find correct values that go in controls
	 switch(op){
		case 0:   //R-type instructions (add, and, nor, or, sub, slt, sltu)
   			       controls->RegDst = 1; 
                   controls->Jump = 0; 
			       controls->Branch = 0; 
			       controls->MemRead = 0; 
			       controls->MemtoReg = 0;
			       controls->ALUOp = 7;
			       controls->MemWrite = 0; 
			       controls->ALUSrc = 0; 
			       controls->RegWrite = 1;
                   break;
      
         case 8:   //add immediate
   			       controls->RegDst = 0; 
                   controls->Jump = 0; 
			       controls->Branch = 0; 
			       controls->MemRead = 0; 
			       controls->MemtoReg = 0;
			       controls->ALUOp = 0;
			       controls->MemWrite = 0; 
			       controls->ALUSrc = 1; 
			       controls->RegWrite = 1;
                   break;
                                   
         case 10:  //slti (signed)
   			       controls->RegDst = 0; 
                   controls->Jump = 0; 
			       controls->Branch = 0; 
			       controls->MemRead = 0; 
			       controls->MemtoReg = 0;
			       controls->ALUOp = 2;
			       controls->MemWrite = 0; 
			       controls->ALUSrc = 1; 
			       controls->RegWrite = 1;
                   break;          
          
          case 9:  //sltiu (unsinged)
   			       controls->RegDst = 0; 
                   controls->Jump = 0; 
			       controls->Branch = 0; 
			       controls->MemRead = 0; 
			       controls->MemtoReg = 0;
			       controls->ALUOp = 3;
			       controls->MemWrite = 0; 
			       controls->ALUSrc = 1; 
			       controls->RegWrite = 1;
                   break;
          
          case 4:  //beq
   			       controls->RegDst = 0; 
                   controls->Jump = 0; 
			       controls->Branch = 1; 
			       controls->MemRead = 0; 
			       controls->MemtoReg = 0;
			       controls->ALUOp = 1;
			       controls->MemWrite = 0; 
			       controls->ALUSrc = 0; 
			       controls->RegWrite = 0;
                   break;
          
          case 2:  //j
   			       controls->RegDst = 0; 
                   controls->Jump = 1; 
			       controls->Branch = 0; 
			       controls->MemRead = 0; 
			       controls->MemtoReg = 0;
			       controls->ALUOp = 0;
			       controls->MemWrite = 0; 
			       controls->ALUSrc = 0; 
			       controls->RegWrite = 0;
                   break;
          
          case 35:  //lw
   			       controls->RegDst = 0; 
                   controls->Jump = 0; 
			       controls->Branch = 0; 
			       controls->MemRead = 1; 
			       controls->MemtoReg = 1;
			       controls->ALUOp = 0;
			       controls->MemWrite = 0; 
			       controls->ALUSrc = 1; 
			       controls->RegWrite = 1;
                   break;
                   
          case 15:  //lui
   			       controls->RegDst = 0; 
                   controls->Jump = 0; 
			       controls->Branch = 0; 
			       controls->MemRead = 0; 
			       controls->MemtoReg = 0;
			       controls->ALUOp = 6;
			       controls->MemWrite = 0; 
			       controls->ALUSrc = 1; 
			       controls->RegWrite = 1;
                   break;         
                   
          case 43:  //sw
   			       controls->RegDst = 2; 
                   controls->Jump = 0; 
			       controls->Branch = 0; 
			       controls->MemRead = 0; 
			       controls->MemtoReg = 2;
			       controls->ALUOp = 0;
			       controls->MemWrite = 1; 
			       controls->ALUSrc = 1; 
			       controls->RegWrite = 0;
                   break;
                   
                   default: return 1;
                   } 
       return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
	//  Read the registers addressed by r1 and r2 from Reg, and write the read values to data1 and data2 respectively
	*data1 = Reg[r1];
	*data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
	//If negative sign extend for negative
	unsigned extend1s = 0xFFFF0000;     
	unsigned Negative = offset >> 15;

    if (Negative == 1)  
         *extended_value = extend1s | offset;

    //Otherwise sign extend normally   
    else 
         *extended_value = offset;
         
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	// declare a pointer, we'll have it point to our operand
	unsigned *operand;

	//declare a pointer, we'll have it point to what we want the ALU to do
	char* operation;

	// ... once we figure out what it is
	//@TODO figure out how to implement these, fairly certain this is not it
	//input sources are correct, either data2 or ex val
	switch ((int) ALUSrc)
	{
		// data2
	case 0:
		operand = &data2;
		break;

		// extended_value
	case 1:
		operand = &extended_value;
		break;

	default:
		//@TODO catch some errors
		return 1; // HALT, HAMMERZEIT
	}

	// ... whatever that might be
	//@TODO figure out what should be in this switch, logic is correct implementation probably isn't
	switch ((int) ALUOp)
	{
		// 000: ALU will do addition or "don't care"
	case 000:
		operation = &ALUOp;
		break;

		// 001: ALU will do subtraction
	case 001:
		operation = &ALUOp;
		break;

		// 010: ALU will do "set less than" operation
	case 010:
		operation = &ALUOp;
		break;

		// 011: ALU will do "set less than unsigned" operation
	case 011:
		operation = &ALUOp;
		break;

		// 100: ALU will do "AND" operation
	case 100:
		operation = &ALUOp;
		break;

		// 101: ALU will do "OR" operation
	case 101:
		operation = &ALUOp;
		break;

		// 110: ALU will shift left extended_value by 16 bits
	case 110:
		operation = &ALUOp;
		break;

		// 111: The instruction is an R-type instruction
	case 111:
		operation = (char*) &funct; //@TODO this seems gross, also wrong
		break;
	}

	// the reason for the season, call the ALU
	ALU(data1,*operand , *operation, ALUresult, Zero);

	// we made it here without everything breaking! yay!
	return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
	//if reading from memory
	if (MemRead == 1) {
		if((ALUresult % 4) == 0){
			*memdata = Mem[ALUresult >> 2];    
		}

		//Improper Address
		else{
			return 1;
		}

	}
	
	//If writting to memory
	if (MemWrite == 1) {
		if((ALUresult % 4) == 0){
			Mem[ALUresult >> 2] = data2;
		}
		//Improper Address Halt
		else{
			return 1;
		}
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
	// increment the PC
	*PC+= 4;

	// shift branch offset
	extended_value = extended_value << 2;

	// shift jump target
	jsec = jsec << 2;

	// @TODO PC + 4 should be bytes 31 - 26, ensure they are
	// @TODO instruction should be bytes 0 - 25, ensure they are

	// Branch mux
	switch (Branch)
	{
	case 0:
		// use PC+4 value, do nothing
		break;

		// when the mux goes to 1, use extended_value for PC
	case 1:
		*PC = extended_value;
		break;

		//@TODO handle errors
	default:
		return;
	}

	// Jump mux
	switch (Jump)
	{
	case 0:
		// use current PC value, do nothing
		break;

		// when the mux goes to 1, use jsec
	case 1:
		*PC = jsec;
		break;

		//@TODO handle errors
	default:
		return;
	}
}

