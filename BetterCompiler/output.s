.data

	a: .word 0

	b: .word 0

	t3: .word 0

	t6: .word 0

	t8: .word 0

	t9: .word 0

.text

.globl main

main:

	li $t0, 3

	sw $t0, a

	li $t0, 3

	li $t1, 3

	beq $t0, $t1, L0

L0:

	li $t0, 2

	sw $t0, b

	li $t0, 3

	sw $t0, t3

	lw $t0, t3

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $t0, 2

	li $t1, 1

	sge $t2, $t1, $t0

	bne $t2, $zero, L1

L1:

	lw $t0, b

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $v0, 10

	syscall

	li $v0, 10

	syscall

	li $t0, 3

	li $t1, 3

	beq $t0, $t1, L2

L2:

	li $t0, 2

	sw $t0, t6

	lw $t0, t6

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $v0, 10

	syscall

	li $t0, 3

	li $t1, 9

	beq $t0, $t1, L3

L3:

	li $t0, 5

	sw $t0, t8

	lw $t0, t8

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $v0, 10

	syscall

	j L4

L4:

	li $t0, 10

	sw $t0, t9

	lw $t0, t9

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $v0, 10

	syscall

	lw $t0, a

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $v0, 10

	syscall
