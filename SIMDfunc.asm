; Name: Alonzo, Jose Anton S.
; Section: CEPARCO S11
; Process: Y[i] = X[i-3] + X[i-2] + X[i-1] + X[i] + X[i+1] + X[i+2] + X[i+3]

section .data
reset dq 0.0

section .text
bits 64
default rel
global SIMD_stencil

SIMD_stencil:

; Parameters:
;	1st - n - rcx
;	2nd - rdx - output
;	3rd - r8 - input

add rdx, 24		; skip first few elements of output vector (i.e. leave them 0)
sub rcx, 3
shr rcx, 4		; 256bit/64bit = 4 elements at a time 

L1:	

	vmovdqu ymm1, [r8]	
	vmovdqu ymm2, [r8+8]
	vmovdqu ymm3, [r8+16]
	vmovdqu ymm4, [r8+24]
	vmovdqu ymm5, [r8+32]
	vmovdqu ymm6, [r8+40]
	vmovdqu ymm7, [r8+48]

	vaddpd ymm0, ymm1, ymm2
	vaddpd ymm0, ymm0, ymm3
	vaddpd ymm0, ymm0, ymm4
	vaddpd ymm0, ymm0, ymm5
	vaddpd ymm0, ymm0, ymm6
	vaddpd ymm0, ymm0, ymm7

	vmovdqu [rdx], ymm0 ; store 4 elems at time

	; move to next positions in the vectors
	add r8, 32
	add rdx, 32

	loop L1

ret
	
