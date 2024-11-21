.data
	arr: .space 20
	t7: .word 0
	t10: .word 0
	sum: .word 0
	a: .word 0
	b: .word 0
	t0: .word 0
	total: .word 0
	t1: .word 0
	divideTotal: .word 0
	t2: .word 0
.text
.globl main
main:
	la $t0, arr
	li $t1, 3
	li $t2, 17
	mul $t1, $t1, 4
	add $t3, $t0, $t1
	sw $t2, 0($t3)
	li $t1, 3
	mul $t1, $t1, 4
	add $t3, $t0, $t1
	lw $t2, 0($t3)
	sw $t2, t7
	lw $t1, t7
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $a0, 10
	li $a1, 2
	jal addNums
	move $t1, $v0
	sw $t1, t10
	lw $t2, t10
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

divideNums:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	sw $a0, a
	sw $a1, b
	lw $t1, a
	lw $t2, b
	div $t1, $t2
	mflo $t3
	sw $t3, t0
	lw $t2, t0
	move $t1, $t2
	sw $t1, total
	lw $v0, total

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra

addNums:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	sw $a0, a
	sw $a1, b
	lw $a0, a
	lw $a1, b
	jal divideNums
	move $t1, $v0
	sw $t1, t1
	lw $t2, t1
	move $t1, $t2
	sw $t1, divideTotal
	lw $t1, divideTotal
	lw $t2, a
	add $t3, $t1, $t2
	sw $t3, t2
	lw $t2, t2
	move $t1, $t2
	sw $t1, total
	lw $v0, total

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra