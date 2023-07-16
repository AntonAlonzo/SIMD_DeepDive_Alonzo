; Name: Alonzo, Jose Anton S.
; Section: CEPARCO S11
; Process: Y[i] = X[i-3] + X[i-2] + X[i-1] + X[i] + X[i+1] + X[i+2] + X[i+3]

section .text
bits 64
default rel
global x86_stencil

x86_stencil:

; Parameters:
;	1st - n - rcx
;	2nd - rdx - output
;	3rd - r8 - input

add rdx, 24		; skip first few elements of output vector (i.e. leave them 0)
sub ecx, 3		; does not count the last few elements (will lead to out of bounds if using the formula)

L1: 	
	movsd xmm0, [r8]
	addsd xmm0, [r8 + 8]
	addsd xmm0, [r8 + 16]
	addsd xmm0, [r8 + 24]
	addsd xmm0, [r8 + 32]
	addsd xmm0, [r8 + 40]
	addsd xmm0, [r8 + 48]

	movsd [rdx], xmm0	; store result in output

	add r8, 8		; move to the start of the next set of inputs
	add rdx, 8		; move to next element in output vector

	loop L1

ret
