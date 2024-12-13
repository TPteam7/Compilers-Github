.data
	t3: .word 0
	sum: .word 0
	a: .word 0
	b: .word 0
	t0: .word 0
	c: .word 0
.text
.globl main
main:
	li $a0, 5
	li $a1, 3
	jal add
	move $t0, $v0
	sw $t0, t3
	lw $t1, t3
	move $t0, $t1
	sw $t0, sum
	lw $t0, sum
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $v0, 10
	syscall

add:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	sw $a0, a
	sw $a1, b
	lw $t0, a
	lw $t1, b
	add $t2, $t0, $t1
	sw $t2, t0
	lw $t1, t0
	move $t0, $t1
	sw $t0, c
	lw $v0, c

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra
