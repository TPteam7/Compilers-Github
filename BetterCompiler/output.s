.data
	t0: .word 0
	t1: .word 0
	t2: .word 0
	t3: .word 0
	t4: .word 0
	t5: .word 0
.text
.globl main
main:
	li $t0, 1
	sw $t0, t0
	li $t0, 1
	sw $t0, t1
	lw $t0, t0
	lw $t1, t1
	xor $t2, $t0, $t1
	lw $t0, goto
	lw $t1, (null)
L0:
	li $t0, 5
	sw $t0, t2
	lw $t0, t2
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $t0, 1
	sw $t0, t3
	li $t0, 1
	sw $t0, t4
	lw $t0, t3
	lw $t1, t4
	xor $t3, $t0, $t1
	lw $t0, goto
	lw $t1, (null)
L2:
	li $t0, 6
	sw $t0, t5
	lw $t0, t5
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $v0, 10
	syscall
