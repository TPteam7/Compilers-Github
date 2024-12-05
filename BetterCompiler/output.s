.data
	a: .word 0
	b: .word 0
	t4: .word 0
	t6: .word 0
.text
.globl main
main:
	li $t0, 0
	sw $t0, a
	li $t0, 100
	sw $t0, b
WhileStart0:
	lw $t0, a
	li $t1, 3
	sge $t2, $t0, $t1
	bne $t2, $zero, Continue0
	lw $t0, a
	li $t1, 1
	add $t2, $t0, $t1
	sw $t2, t4
	lw $t1, t4
	move $t0, $t1
	sw $t0, a
	lw $t0, b
	li $t1, 1
	add $t2, $t0, $t1
	sw $t2, t6
	lw $t1, t6
	move $t0, $t1
	sw $t0, b
	lw $t0, a
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	j WhileStart0
Continue0:
	lw $t0, b
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $v0, 10
	syscall
