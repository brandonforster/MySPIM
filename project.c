// Brandon Forster
// Michael Andacht
// CDA 3103 - Computer Logic and Organization
// 22 April 2013
// MySPIM
// A simple MIPS simulator
// Complete Git repository (with contributions and issue tracking) available at https://github.com/brandonforster/MySPIM

#include "spimcore.h"


/* ALU */
/* Written by Brandon Forster */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	// Switch to control which ALU control gets executed
	switch ((int) ALUControl)
	{
		// 000: Z = A + B ADD
	case 000:
		*ALUresult = A + B;
		break;

		// 001: Z = A - B
	case 001:
		*ALUresult = A - B;
		break;

		// 010: if A < B, Z = 1; otherwise, Z = 0 (A and B are signed integers)
	case 010:
		if ((signed)A < (signed)B)
		{
			*ALUresult = 1;
		}
		else
		{
			*ALUresult = 0;
		}
		break;

		// 011: if A < B, Z = 1; otherwise, Z = 0 (A and B are unsigned integers)
	case 011:	
		if (A < B)
		{
			*ALUresult = 1;
		}
		else
		{
			*ALUresult = 0;
		}
		break;

		// 100: Z = A AND B (bitwise)
	case 100:
		*ALUresult = A & B;
		break;

		// 101: Z = A OR B (bitwise)
	case 101:

		*ALUresult = A | B;
		break;

		// 110: Shift left B by 16 bits
	case 110:
		B << 16;
		break;

		// 111: Z = NOT A (bitwise)
	case 111:
		*ALUresult = ~A;
		break;


	}
	//Check for zeroes
	//When Zero = 1, the value is zero.
	if(*ALUresult == 0){
		*Zero = 1;
	}
	// When Zero = 0, the value is not zero.
	else{
		*Zero = 0;
	}
}

/* instruction fetch */
/* Written by Michael Andacht */
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
    else{
		return 1; 
	}
}


/* instruction partition */
/* Written by Brandon Forster */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	// we will use these partitions to only change values we want
	unsigned rPartition		= 0x1f;	
	unsigned functopPartition	= 0x0000003f;	
	unsigned offsetPartition	= 0x0000ffff;	
	unsigned jsecPartition	= 0x03ffffff;	

	// apply partitions and shifts
	*op		= (instruction >> 26) & functopPartition;	// instruction [31-26]
	*r1		= (instruction >> 21) & rPartition; // instruction [25-21]
	*r2		= (instruction >> 16) & rPartition; // instruction [20-16]
	*r3		= (instruction >> 11) & rPartition; // instruction [15-11]
	*funct	= instruction & functopPartition; // instruction [5-0]
	*offset	= instruction & offsetPartition; // instruction [15-0]
	*jsec	= instruction & jsecPartition; // instruction [25-0]
}



/* instruction decode */
/* Written by Michael Andacht */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	//Switch for different Op codes to decode 
	//TODO Get proper Op codes and find correct values that go in controls
	 switch(op){
		case 0:   //This is for R Type
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
      
         case 8:   // Case for add immediate
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
                                   
         case 10:  //Case for slti
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
          
          case 11:  //Case for sltiu
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
          
          case 4:  //Case for Branch Equal
   			       controls->RegDst = 2; 
                   controls->Jump = 0; 
			       controls->Branch = 1; 
			       controls->MemRead = 0; 
			       controls->MemtoReg = 2;
			       controls->ALUOp = 1;
			       controls->MemWrite = 0; 
			       controls->ALUSrc = 0; 
			       controls->RegWrite = 0;
                   break;
          
          case 2:  //Case for Jump
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
          
          case 35:  //Case for Load word
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
                   
          case 15:  //Case for load unsigned imediate
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
                   
          case 43:  //Case for Store word
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
                   
				   //Return 1 if Halt
          default:
				   return 1;
	
     } 
       return 0;
}

/* Read Register */
/* Written by Brandon Forster */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
	//  Read the registers addressed by r1 and r2 from Reg, and write the read values to data1 and data2 respectively
	*data1 = Reg[r1];
	*data2 = Reg[r2];
}


/* Sign Extend */
/* Written by Michael Andacht */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
	//If negative sign extend for negative
	unsigned extend1s = 0xFFFF0000;     
	unsigned Negative = offset >> 15;

    if (Negative == 1)  
         *extended_value = offset | extend1s;


    //Otherwise sign extend normally   
    else 
         *extended_value = offset & 0x0000ffff;
         
}

/* ALU operations */
/* Written by Brandon Forster */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	//Check which data we are opperating on by ALU src
	if(ALUSrc == 1){
		data2 = extended_value;
	}

	//All ALUOps just send instructions to ALU which updates ALU result
	//ALUOP 7 is R type insturction which requires use of funct
	if(ALUOp == 7){
		//Find the proper ALUOp for each R type instruction
		switch(funct) {
			
			//Add
			case 32:
					ALUOp = 0;
					break;
			//Sub
			case 34:
					ALUOp = 1;
					break;
			//Set Less Signed
			case 42:
					ALUOp = 2;
					break;
			//Set Less Unsigned
			case 43:
					ALUOp = 3;
					break;
			//And
			case 36:
					ALUOp = 4;
					break;
			//Or
			case 37:
					ALUOp = 5;
					break;
			//Shift Left extended value 16
			case 6: 
					ALUOp = 6;
					break;
			//Nor
			case 39:
					ALUOp = 7;
					break;
			//Halt not proper funct
			default:
					return 1;

		}
		//Send to ALU for funct
		ALU(data1,data2,ALUOp,ALUresult,Zero);
				
	}


	else{
	//Send to ALU for non funct
	ALU(data1,data2,ALUOp,ALUresult,Zero);
	}
	
	//Return
	return 0;


}

/* Read / Write Memory */
/* Written by Michael Andacht */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

	//if reading from memory
	if (MemRead == 1) {
		if((ALUresult % 4) == 0){
			*memdata = Mem[ALUresult >> 2];    
		}

		//Improper Address Halt
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
/* Written by Michael Andacht */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
	//Check if writing
	if(RegWrite == 1){
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
}

/* PC update */
/* Written by Brandon Forster */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
	// increment the PC by 4 always
	*PC += 4;

	//If branching and we got a zero properly add extended value
	if(Zero == 1 && Branch == 1){
		*PC += extended_value << 2;
	}

	// If Jumping shift Instruction and combine with PC
	if(Jump == 1){
		*PC = (jsec << 2) | (*PC & 0xf0000000);
	}
}

