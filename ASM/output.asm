.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib C:/Users/Dima/Desktop/KURSACH/ZDA-2021/Debug/StaticLibrary.lib 
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
EXTRN minus: proc

.stack 4096

.const
	L1 SDWORD 0
	L2 SDWORD 1
	L3 BYTE " ", 0
	L4 SDWORD 127
	L5 SDWORD -20
	L6 BYTE "special message", 0
	L7 BYTE "◊ËÒÎÓ  = ", 0
	L8 SDWORD 20
	L9 SDWORD 5
	L10 BYTE "‘¿ “Œ–»¿À 5 = ", 0
	L11 SDWORD 2
	L12 SDWORD 3
	L13 SDWORD -127

.data
	buffer BYTE 256 dup(0)
	factoriali SDWORD 0
	factorialres SDWORD 0
	libtesti SDWORD 0
	maini SDWORD 0
	mainmessage DWORD ?
	maintest SDWORD 0

.code

factorial PROC factorialn : SDWORD
	mov eax, factorialn
	cmp eax, L1
	jl m0
	jg m1
	je m1
m0:
	push 0
	jmp local0
m1:
	push L2
	pop factoriali
	push factorialn
	push L2
	call sum
	push eax
	pop factorialn
	push L2
	pop factorialres
	mov eax, factoriali
	cmp eax, factorialn
	jl cycle0
	jmp cyclenext0
cycle0:
	push factorialres
	push factoriali
	 call multip
	push eax
	pop factorialres
	push factoriali
	push L2
	call sum
	push eax
	pop factoriali
	mov eax, factoriali
	cmp eax, factorialn
	jl cycle0
cyclenext0:
	push factorialres
	jmp local0
local0:
	pop eax
	ret
factorial ENDP

libtest PROC libtestmin : SDWORD, libtestmax : SDWORD
	push libtestmin
	push libtestmax
	pop edx
	pop edx
	push libtestmax
	push libtestmin
	call mrand
	push eax
	pop libtesti
	push libtesti
	push libtesti
	pop edx
	pop edx
	push libtesti
	push libtesti
	call mpow
	push eax
	pop libtesti
	push libtesti
	call OutputInt
	push offset L3
	call OutputStrLn
	ret
libtest ENDP

allnumbers PROC allnumbersi : SDWORD
	mov eax, allnumbersi
	cmp eax, L4
	jl cycle1
	jmp cyclenext1
cycle1:
	mov eax, allnumbersi
	cmp eax, L5
	jz m2
	jnz m3
	je m3
m2:
	push offset L6
	call OutputStrLn
	jmp e0
m3:
	push offset L7
	call OutputStr
	push allnumbersi
	call OutputIntLn
e0:
	push allnumbersi
	push L2
	call sum
	push eax
	pop allnumbersi
	mov eax, allnumbersi
	cmp eax, L8
	jz m4
	jnz m5
	je m5
m4:
	push offset L6
	call OutputStrLn
m5:
	mov eax, allnumbersi
	cmp eax, L4
	jl cycle1
cyclenext1:
	ret
allnumbers ENDP

functest PROC functesti : SDWORD
	push functesti
	jmp local1
local1:
	pop eax
	ret
functest ENDP

main PROC
	push L9
	pop edx
	push L9
	call factorial
	push eax
	pop maini
	push offset L10
	pop mainmessage
	push mainmessage
	call OutputStr
	push maini
	call OutputIntLn
	push L12
	push L11
	call libtest
	push L11
	push L2
	call libtest
	push L13
	call allnumbers
	push L2
	pop edx
	push L2
	call functest
	push eax
	push L8
	pop edx
	push L8
	call functest
	push eax
	call sum
	push eax
	push L8
	call sum
	push eax
	pop maintest
	push maintest
	call OutputIntLn
	call ExitProcess
main ENDP
end main