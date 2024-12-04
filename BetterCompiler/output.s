.data
	t2: .word 0
.text
.globl main
main:
	li $t0, 1
	li $t1, 1
	beq $t0, $t1, L0
L0:
	li $t0, 3
	sw $t0, t2
	lw $t0, t2
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
