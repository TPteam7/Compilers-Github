.data
	t2: .word 0
	t5: .word 0
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
	li $t0, 2
	li $t1, 1
	beq $t0, $t1, L2
L2:
	li $t0, 4
	sw $t0, t5
	lw $t0, t5
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $t0, 0
	li $t1, 1
	add $t2, $t0, $t1
	sw $t2, t6
	lw $t1, t6
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
	li $v0, 10
	syscall
