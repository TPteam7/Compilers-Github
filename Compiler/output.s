.data
	x: .word 0
	t4: .word 0
	t6: .word 0
	t8: .word 0
	t10: .word 0
	t12: .word 0
.text
.globl main
main:
	li $t0, 1
	sw $t0, x
	li $t0, 23
	li $t1, 10
	add $t2, $t0, $t1
	sw $t2, t4
	li $t0, 12
	li $t1, 1
	mul $t2, $t0, $t1
	sw $t2, t6
	lw $t1, t6
	move $t0, $t1
	sw $t0, x
	li $t0, 12
	li $t1, 1
	add $t2, $t0, $t1
	sw $t2, t8
	li $t0, 12
	li $t1, 1
	add $t2, $t0, $t1
	sw $t2, t10
	lw $t0, t10
	li $t1, 3
	add $t2, $t0, $t1
	sw $t2, t12
	lw $t1, t12
	move $t0, $t1
	sw $t0, x
	lw $t0, x
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 10
	syscall
