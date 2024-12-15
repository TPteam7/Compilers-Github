.data
	length: .word 0
	array: .space 20
	i: .word 0
	t20: .word 0
	fact: .word 0
	t22: .word 0
	t24: .word 0
	t25: .word 0
	var: .word 0
	t27: .word 0
	a: .word 0
	b: .word 0
	t0: .word 0
	sum: .word 0
	t2: .word 0
	temp: .word 0
	t4: .word 0
	doubleSum: .word 0
	t6: .word 0
	t7: .word 0
	c: .word 0
	t10: .word 0
	n: .word 0
	result: .word 0
	current: .word 0
	t13: .word 0
	t15: .word 0
	dividend: .word 0
	divisor: .word 0
	t16: .word 0
.text
.globl main
main:
	li $t0, 5
	sw $t0, length
	la $t0, array
	li $t1, 0
	sw $t1, i
WhileStart3:
	lw $t1, i
	li $t2, 5
	slt $t3, $t1, $t2
	beq $t3, $zero, Continue3
	lw $a0, i
	jal factorial
	move $t1, $v0
	sw $t1, t20
	lw $t2, t20
	move $t1, $t2
	sw $t1, fact
	lw $t1, i
	lw $t2, fact
	mul $t1, $t1, 4
	add $t3, $t0, $t1
	sw $t2, 0($t3)
	lw $t1, i
	li $t2, 1
	add $t3, $t1, $t2
	sw $t3, t22
	lw $t2, t22
	move $t1, $t2
	sw $t1, i
	j WhileStart3
Continue3:
	li $t1, 0
	sw $t1, i
WhileStart4:
	lw $t1, i
	li $t2, 5
	slt $t3, $t1, $t2
	beq $t3, $zero, Continue4
	lw $t1, i
	mul $t1, $t1, 4
	add $t3, $t0, $t1
	lw $t2, 0($t3)
	sw $t2, t24
	lw $a0, t24
	jal printInt
	move $t1, $v0
	sw $t1, t25
	lw $t2, t25
	move $t1, $t2
	sw $t1, var
	lw $t1, i
	li $t2, 1
	add $t3, $t1, $t2
	sw $t3, t27
	lw $t2, t27
	move $t1, $t2
	sw $t1, i
	j WhileStart4
Continue4:
	li $v0, 10
	syscall

add:
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
	sw $t1, sum
	lw $t1, sum
	li $t2, 5
	add $t3, $t1, $t2
	sw $t3, t2
	lw $t2, t2
	move $t1, $t2
	sw $t1, temp
	lw $t1, temp
	li $t2, 2
	mul $t3, $t1, $t2
	sw $t3, t4
	lw $t2, t4
	move $t1, $t2
	sw $t1, doubleSum
	lw $t1, doubleSum
	li $t2, 50
	sgt $t3, $t1, $t2
	bne $t3, $zero, L1
	j L2
L1:
	lw $t1, doubleSum
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	j L0
L2:
	li $t1, 0
	sw $t1, t6
	lw $t1, t6
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	j L0
L0:
	lw $v0, doubleSum

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra

subtract:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	sw $a0, a
	sw $a1, b
	lw $t1, a
	lw $t2, b
	subu $t3, $t1, $t2
	sw $t3, t7
	lw $t2, t7
	move $t1, $t2
	sw $t1, c
WhileStart0:
	lw $t1, c
	li $t2, 20
	slt $t3, $t1, $t2
	beq $t3, $zero, Continue0
	lw $t1, c
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	lw $t1, c
	li $t2, 2
	add $t3, $t1, $t2
	sw $t3, t10
	lw $t2, t10
	move $t1, $t2
	sw $t1, c
	j WhileStart0
Continue0:
	lw $v0, c

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra

factorial:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	sw $a0, n
	li $t1, 1
	sw $t1, result
	lw $t2, n
	move $t1, $t2
	sw $t1, current
WhileStart1:
	lw $t1, current
	li $t2, 1
	sgt $t3, $t1, $t2
	beq $t3, $zero, Continue1
	lw $t1, result
	lw $t2, current
	mul $t3, $t1, $t2
	sw $t3, t13
	lw $t2, t13
	move $t1, $t2
	sw $t1, result
	lw $t1, current
	li $t2, 1
	subu $t3, $t1, $t2
	sw $t3, t15
	lw $t2, t15
	move $t1, $t2
	sw $t1, current
	j WhileStart1
Continue1:
	lw $v0, result

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra

modulus:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	sw $a0, dividend
	sw $a1, divisor
WhileStart2:
	lw $t1, dividend
	lw $t2, divisor
	sge $t3, $t1, $t2
	beq $t3, $zero, Continue2
	lw $t1, dividend
	lw $t2, divisor
	subu $t3, $t1, $t2
	sw $t3, t16
	lw $t2, t16
	move $t1, $t2
	sw $t1, dividend
	j WhileStart2
Continue2:
	lw $v0, dividend

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra

printInt:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	sw $a0, a
	lw $t1, a
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $v0, 1

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra
