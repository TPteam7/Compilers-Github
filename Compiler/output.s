.data
	t3: .word 0
	t4: .word 0
	t6: .word 0
	x: .word 0
.text
.globl main
main:
	li $t0, 2
	li $t1, 3
	mul $t2, $t0, $t1
	sw $t2, t3
	li $t0, 1
	lw $t1, t3
	add $t2, $t0, $t1
	sw $t2, t4
	lw $t0, t4
	li $t1, 5
	subu $t2, $t0, $t1
	sw $t2, t6
	lw $t1, t6
	move $t0, $t1
	sw $t0, x
	lw $t0, x
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 10
	syscall
