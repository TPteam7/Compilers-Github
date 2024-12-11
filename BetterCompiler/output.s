.data

	t1: .word 0

	t2: .word 0

	b: .word 0

	t3: .word 0

	t4: .word 0

	t5: .word 0

	t6: .word 0

	t7: .word 0

	a1: .word 0

	b1: .word 0

	t0: .word 0

	c: .word 0

.text

.globl main

main:

	li $t0, 1

	sw $t0, t1

	li $t0, 2

	sw $t0, t2

	lw $t1, t2

	move $t0, $t1

	sw $t0, b

WhileStart0:

	li $t0, 3

	sw $t0, t3

	lw $t0, b

	lw $t1, t3

	slt $t2, $t0, $t1

	bne $t2, $zero, Continue0

	li $t0, 1

	sw $t0, t4

	lw $t0, t4

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $t0, 1

	sw $t0, t5

	lw $t0, b

	lw $t1, t5

	add $t2, $t0, $t1

	sw $t2, t6

	j WhileStart0

Continue0:

	li $t0, 10

	sw $t0, t7

	lw $t0, t7

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $v0, 10

	syscall



add:

	addi $sp, $sp, -4

	sw $ra, 0($sp)



	sw $a0, a1

	sw $a1, b1

	lw $t0, a1

	lw $t1, b1

	add $t2, $t0, $t1

	sw $t2, t0

	lw $t1, t0

	move $t0, $t1

	sw $t0, c

	lw $v0, c



	lw $ra, 0($sp)

	addi $sp, $sp, 4



	jr $ra
