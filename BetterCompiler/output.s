.data
	t0: .word 0
	diff: .word 0
.text
.globl main
main:
	li $v0, 10
	syscall

sub:
	lw $t0, a
	lw $t1, b
	subu $t2, $t0, $t1
	sw $t2, t0
	lw $t1, t0
	move $t0, $t1
	sw $t0, diff
	lw $v0, (null)
	jr $ra
