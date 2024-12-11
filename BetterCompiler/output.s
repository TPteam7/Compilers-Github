.data
	t0: .word 0
	a: .word 0
	t1: .word 0
	x2: .word 0
	t2: .word 0
	t3: .word 0
	t4: .word 0
.text
.globl main
main:
	li $t0, 5
	sw $t0, t0
	lw $t1, t0
	move $t0, $t1
	sw $t0, a
	li $t0, 10
	sw $t0, t1
	lw $t1, t1
	move $t0, $t1
	sw $t0, x2
WhileStart0:
	lw $t0, a
	lw $t1, x2
	slt $t2, $t0, $t1
	beq $t2, $zero, Continue0
	li $t0, 1
	sw $t0, t2
	lw $t0, a
	lw $t1, t2
	add $t2, $t0, $t1
	sw $t2, t3
	lw $t1, t3
	move $t0, $t1
	sw $t0, a
	lw $t0, a
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	j WhileStart0
Continue0:
	li $t0, 7
	sw $t0, t4
	lw $t0, t4
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $v0, 10
	syscall
