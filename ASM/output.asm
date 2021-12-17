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
EXTRN minus: proc

.stack 4096

.const
	L1 SDWORD 20
	L2 SDWORD 10
	L3 SDWORD 25
	L4 SDWORD 2

.data
	buffer BYTE 256 dup(0)
	fb SDWORD 0
	mainb SDWORD 0
	maini SDWORD 0

.code

f2 PROC f2b : SDWORD
	push f2b
	jmp local0
local0:
	pop eax
	ret
f2 ENDP

f PROC fi : SDWORD
	push L1
	pop edx
	push L1
	call f2
	push eax
	pop fb
	push fb
	jmp local1
local1:
	pop eax
	ret
f ENDP

main PROC
	push L2
	pop edx
	push L2
	call f
	push eax
	pop mainb
	push mainb
	call OutputInt
	push L3
	pop maini
	push maini
	push L3
	call sum
	push eax
	push L4
	pop ebx
	pop eax
	cdq
	idiv ebx
	push eax
	pop mainb
	push mainb
	call OutputInt
	call ExitProcess
main ENDP
end main