.data

	t0: .word 0

	t1: .word 0

	t2: .word 0

	t3: .word 0

	t4: .word 0

.text

.globl main

main:

	li $t0, 0

	sw $t0, t0

	li $t0, 1

	sw $t0, t1

	lw $t0, t0

	lw $t1, t1

	xor $t2, $t0, $t1

	li $t0, 1

	sw $t0, t2

	li $t0, 1

	sw $t0, t3

	lw $t0, t2

	lw $t1, t3

	sge $t3, $t0, $t1

	or $t0, $t2, $t3

	bne $t0, $zero, L1

	j L2

L1:

	li $t0, 1

	sw $t0, t4

	lw $t0, t4

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	j L0

L2:

L0:

	li $v0, 10

	syscall
