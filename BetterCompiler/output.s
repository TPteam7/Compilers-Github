.data
	t5: .word 0
	subtraction: .word 0
	a1: .word 0
	b1: .word 0
	t0: .word 0
	total: .word 0
	a: .word 0
	b: .word 0
	t1: .word 0
	t2: .word 0
	diff: .word 0
.text
.globl main
main:
	li $a0, 10
	li $a1, 5
	jal sub
	move $t0, $v0
	sw $t0, t5
	lw $t1, t5
	move $t0, $t1
	sw $t0, subtraction
	lw $t0, subtraction
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $v0, 10
	syscall

divide:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	sw $a0, a1
	sw $a1, b1
	lw $t0, a1
	lw $t1, b1
	div $t0, $t1
	mflo $t2
	sw $t2, t0
	lw $t1, t0
	move $t0, $t1
	sw $t0, total
	lw $t0, total
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	lw $v0, total

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra

sub:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	sw $a0, a
	sw $a1, b
	lw $a0, a
	lw $a1, b
	jal divide
	move $t0, $v0
	sw $t0, t1
	lw $t1, t1
	move $t0, $t1
	sw $t0, b
	lw $t0, b
	lw $t1, a
	subu $t2, $t0, $t1
	sw $t2, t2
	lw $t1, t2
	move $t0, $t1
	sw $t0, diff
	lw $t0, diff
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	lw $v0, diff

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra
