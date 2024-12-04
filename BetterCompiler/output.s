.data
	t0: .word 0
	c: .word 0
	t1: .word 0
	t4: .word 0
.text
.globl main
main:
	li $t0, 4
	li $t1, 3
	sgt $t2, $t1, $t0
	bne $t2, $zero, L0
	li $v0, 10
	syscall

sumThese:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	li $a0, 3
	li $a1, 4
	li $t0, 3
	li $t1, 4
	add $t2, $t0, $t1
	sw $t2, t0
	lw $t1, t0
	move $t0, $t1
	sw $t0, c
	lw $v0, c

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra

printSum:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	li $a0, 3
	li $a1, 4
	li $a0, 3
	li $a1, 4
	jal sumThese
	move $t0, $v0
	sw $t0, t1
	lw $t1, t1
	move $t0, $t1
	sw $t0, c
	lw $v0, c

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra
L0:
	li $a0, 3
	li $a1, 4
	jal printSum
	move $t0, $v0
	sw $t0, t4
	li $v0, 10
	syscall
