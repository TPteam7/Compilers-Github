.data
	arr: .space 20
	t9: .word 0
	t11: .word 0
	t13: .word 0
	t14: .word 0
	sum: .word 0
	a: .word 0
	b: .word 0
	t0: .word 0
	total: .word 0
.text
.globl main
main:
	la $t0, arr
	li $t1, 3
	li $t2, 17
	mul $t1, $t1, 4
	add $t3, $t0, $t1
	sw $t2, 0($t3)
	li $t1, 2
	li $t2, 2
	mul $t1, $t1, 4
	add $t3, $t0, $t1
	sw $t2, 0($t3)
	li $t1, 5
	li $t2, 5
	mul $t1, $t1, 4
	add $t3, $t0, $t1
	sw $t2, 0($t3)
	li $t1, 4
	mul $t1, $t1, 4
	add $t3, $t0, $t1
	lw $t2, 0($t3)
	sw $t2, t9
	lw $t1, t9
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $t1, 2
	mul $t1, $t1, 4
	add $t3, $t0, $t1
	lw $t2, 0($t3)
	sw $t2, t11
	lw $a0, t11
	li $t1, 3
	mul $t1, $t1, 4
	add $t3, $t0, $t1
	lw $t2, 0($t3)
	sw $t2, t13
	lw $a1, t13
	jal addNums
	move $t1, $v0
	sw $t1, t14
	lw $t2, t14
	move $t1, $t2
	sw $t1, sum
	lw $t1, sum
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $v0, 10
	syscall

addNums:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	sw $a0, a
	sw $a1, b
	lw $t1, a
	lw $t2, b
	add $t3, $t1, $t2
	sw $t3, t0
	lw $t2, t0
	move $t1, $t2
	sw $t1, total
	lw $v0, total

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra
