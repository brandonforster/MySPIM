.ent main

main:
addi $8, $8, 1		
addi $9, $8, 2		
add $10, $8, $9		
sw $10, 0($29)        	
lw $11, 0($29) 	      	
slt $t4, $t3, $t2    	
sltu $t5, $t1, $t2  	
lui $14, 32		
j end		      	
label: addi $8, $8, 2929
sub $8, $8, 3
end: beq $10, $11, label  
.end main