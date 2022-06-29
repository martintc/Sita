	.section ".text.boot"

	.global _start // execution starts here

_start:
	// check processor ID is zero
	mrs	x1, mpidr_el1
	and	x1, x1, #3
	cbz	x1, 2f
	// not on main core, so conduct inifinit loop
1:	wfe
	b	1b
2:	// on main core

	// set stack to start below code
	ldr	x1, =_start
	mov	sp, x1

	// clean the BSS section
	ldr	x1, =__bss_start // start address
	ldr	w2, =__bss_size // size of section
3:	cbz	w2, 4f
	str	xzr, [x1], #8
	sub	w2, w2, #1
	cbnz	w2, 3b // loop if non-zero

	// jump to main routine in C
4:	bl	main
	// in case it does return halt the master core
	b	1b
	
