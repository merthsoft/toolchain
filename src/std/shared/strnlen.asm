	.def _strnlen
	.ref __frameset0
	.assume adl=1

_strnlen:
	call	__frameset0
	ld	de,(ix+6)
	ld	bc,(ix+9)
	or	a,a
	sbc	hl,hl
	jr	StartFor
ForLoop:
	inc	hl
	inc	de
StartFor:
	push	hl
	or	a,a
	sbc	hl,bc
	pop	hl
	jr	nc,ReachedMax
	ld	a,(de)
	or	a,a
	jr	nz,ForLoop
ReachedMax:
	ld	sp,ix
	pop	ix
	ret