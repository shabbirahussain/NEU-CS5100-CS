.globl main
.data
        dataLen:  .word 2
           	  .align 5
        data:  	  .asciiz "Ji"
           	  .align 5
           	  .asciiz  "J"
           	  .align 5
           	  .asciiz "Jeff"
           	  .align 5
           	  .asciiz  "Joyce"
           	  .align 5
           	  .asciiz  "Jerry"
           	  .align 5
           	  .asciiz  "Janice"
           	  .align 5
           	  .asciiz "Jake"
           	  .align 5
           	  .asciiz  "Jonna"
           	  .align 5
           	  .asciiz  "Jack"
           	  .align 5
           	  .asciiz  "Jocelyn"
           	  .align 5
           	  .asciiz "Jessie"
           	  .align 5
           	  .asciiz  "Jess"
           	  .align 5
           	  .asciiz  "Janet"
           	  .align 5
           	  .asciiz  "Jane"
.text
main:
	la $a0, data
	addi $a1, $a0, 32
	jal string_compare
	move $s0, $v1
	
        li $v0, 10       	# system call 10 is exit()
        li $a0, 0          	# setting return code of program to 0 (success)
	syscall	       		# Equivalent to "return" statement in main.

string_compare: # Expects the address of strings in $a0 $a1, returns result in $v1
	##### Start: Stub for starting a function
	sw $ra, 4($sp)
	sw $s0, 8($sp)
	sw $s1, 12($sp)
	sw $s2, 16($sp)
	sw $s3, 20($sp)
	sw $s4, 24($sp)
	sw $s5, 28($sp)
	sw $s6, 32($sp)
	sw $s7, 36($sp)
	addi $sp, $sp, 36
	##### End: Stub for starting a function
	
	subi $a0, $a0, 1
	subi $a1, $a1, 1
	
	string_comp_l1_start:
		addi $a0, $a0, 1
		addi $a1, $a1, 1
		
		lw $t0, ($a0)
		andi $t0, $t0, 0x000000FF
		lw $t1, ($a1)
		andi $t1, $t1, 0x000000FF
		sub $v1, $t0, $t1
		bnez $v1, string_comp_return
		
		lw $t0, ($a0)
		andi $t0, $t0, 0x0000FF00
		lw $t1, ($a1)
		andi $t1, $t1, 0x0000FF00
		sub $v1, $t0, $t1
		bnez $v1, string_comp_return
		
		lw $t0, ($a0)
		andi $t0, $t0, 0x00FF0000
		lw $t1, ($a1)
		andi $t1, $t1, 0x00FF0000
		sub $v1, $t0, $t1
		bnez $v1, string_comp_return
		
		lw $t0, ($a0)
		andi $t0, $t0, 0xFF000000
		lw $t1, ($a1)
		andi $t1, $t1, 0xFF000000
		sub $v1, $t0, $t1
		bnez $v1, string_comp_return
		
		j string_comp_l1_start
	string_comp_return:
	
	##### Start: Stub for returning from a function
	subi $sp, $sp, 36	# Restore the stack pointer
	lw $ra, 4($sp)
	lw $s0, 8($sp)
	lw $s1, 12($sp)
	lw $s2, 16($sp)
	lw $s3, 20($sp)
	lw $s4, 24($sp)
	lw $s5, 28($sp)
	lw $s6, 32($sp)
	lw $s7, 36($sp)
	li $v0, 0  # 0 means success; Pass return value in $v0
	jr $ra
	##### End: Stub for returning from a function	