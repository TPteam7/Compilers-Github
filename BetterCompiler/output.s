.data

	a: .word 0

	t2: .word 0

	b: .word 0

	t3: .word 0

	c: .word 0

	t6: .word 0

	t8: .word 0

	t10: .word 0

	t11: .word 0

.text

.globl main

main:

	li $t0, 3

	sw $t0, a

	li $t0, 3

	li $t1, 7

	add $t2, $t0, $t1

	sw $t2, t2

	lw $t1, t2

	move $t0, $t1

	sw $t0, b

	li $t0, 3

	lw $t1, b

	add $t2, $t0, $t1

	sw $t2, t3

	lw $t1, t3

	move $t0, $t1

	sw $t0, c

	lw $t0, c

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	lw $t0, c

	li $t1, 3

	beq $t0, $t1, L0

	lw $t0, c

	li $t1, 3

	beq $t0, $t1, L1

	lw $t0, c

	li $t1, 9

	beq $t0, $t1, L2

	j L3

	lw $t0, a

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

L0:

	li $t0, 3

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

L1:

	li $t0, 2

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

L2:

	li $t0, 5

	sw $t0, t10

	lw $t0, t10

	li $v0, 1

	move $a0, $t0

	syscall

	li $v0, 11

	li $a0, 10

	syscall

	li $v0, 10

	syscall

L3:

	li $t0, 10

	sw $t0, t11

	lw $t0, t11

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
