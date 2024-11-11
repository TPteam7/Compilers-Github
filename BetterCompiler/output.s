.data
	arr: .space 20
	t4: .word 0
	t6: .word 0
.text
.globl main
main:
	la $t0, arr
	li $t0, 3
	lw $t0, arr
	lw $t1, 17
	mul $t0, $t0, 4
	add $t1, $t1, $t0
	sw $t0, 0($t1)
	li $t0, 3
	lw $t0, arr
	mul $t1, $t0, 4
	add $t0, $t0, $t1
	lw $t1, 0($t0)
	sw $t1, t4
	li $t0, 3
	lw $t0, arr
	mul $t1, $t0, 4
	add $t0, $t0, $t1
	lw $t1, 0($t0)
	sw $t1, t6
	lw $t0, t6
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
