.data
	a: .word 0
	t3: .word 0
	t4: .word 0
.text
.globl main
main:
	li $t0, 5
	sw $t0, a
WhileStart0:
	lw $t0, a
	li $t1, 10
	slt $t2, $t0, $t1
	beq $t2, $zero, Continue0
	lw $t0, a
	li $t1, 1
	add $t2, $t0, $t1
	sw $t2, t3
	lw $t1, t3
	move $t0, $t1
	sw $t0, a
	lw $t0, a
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	j WhileStart0
Continue0:
	li $t0, 7
	sw $t0, t4
	lw $t0, t4
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $v0, 10
	syscall
