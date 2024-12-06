.data
	a: .word 0
	b: .word 0
	t11: .word 0
	t13: .word 0
.text
.globl main
main:
	li $t0, 0
	sw $t0, a
	li $t0, 0
	sw $t0, b
WhileStart0:
	lw $t0, (null)
	lw $t1, (null)
	lw $t0, a
	li $t1, 1
	add $t2, $t0, $t1
	sw $t2, t11
	lw $t1, t11
	move $t0, $t1
	sw $t0, a
	lw $t0, b
	li $t1, 1
	add $t2, $t0, $t1
	sw $t2, t13
	lw $t1, t13
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
