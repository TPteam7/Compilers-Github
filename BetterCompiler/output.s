.data
	t3: .word 0
	t7: .word 0
	t8: .word 0
.text
.globl main
main:
	lw $t0, t2
	lw $t1, (null)
	beq $t0, $t1, L0
L0:
	li $t0, 5
	sw $t0, t3
	lw $t0, t3
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	lw $t0, t6
	lw $t1, (null)
	beq $t0, $t1, L1
L1:
	li $t0, 3
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
	li $t0, 1
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
	li $v0, 10
	syscall
