.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/StaticLibrary.lib
ExitProcess PROTO :DWORD

EXTRN BREAKL: proc
EXTRN OutputInt: proc
EXTRN OutputStr: proc
EXTRN OutputIntLn: proc
EXTRN OutputStrLn: proc
EXTRN sum: proc
EXTRN multip: proc
EXTRN mpow: proc
EXTRN mrand: proc

.stack 4096

.const
	L1 SDWORD 100
	L2 SDWORD -20
	L3 BYTE "special message", 0
	L4 SDWORD 20
	L5 SDWORD 1
	L6 BYTE "Число  = ", 0
	L7 SDWORD -127

.data
	buffer BYTE 256 dup(0)
	maini SDWORD 0

.code

f PROC fi : SDWORD
	mov eax, fi
	cmp eax, L1
	jl cycle0
	jmp cyclenext0
cycle0:
	mov eax, fi
	cmp eax, L2
	jz m0
	jnz m1
	je m1
m0:
	push offset L3
	call OutputStrLn
m1:
	mov eax, fi
	cmp eax, L4
	jz m2
	jnz m3
	je m3
m2:
	push offset L3
	call OutputStrLn
m3:
	push fi
	push L5
	call sum
	push eax
	pop fi
	push offset L6
	call OutputStr
	push fi
	call OutputIntLn
	mov eax, fi
	cmp eax, L1
	jl cycle0
cyclenext0:
	ret
f ENDP

main PROC
	push L7
	pop maini
	push maini
	call f
	call ExitProcess
main ENDP
end main