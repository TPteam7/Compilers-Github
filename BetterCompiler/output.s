.data
	a: .word 0
	t3: .word 0
.text
.globl main
main:
	li $t0, 0
	sw $t0, a
	lw $t0, a
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $t0, 0
	li $t1, 1
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
	li $v0, 10
	syscall
