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
	L1 SDWORD 25
	L2 SDWORD 46
	L3 SDWORD 100

.data
	buffer BYTE 256 dup(0)
	maini SDWORD 0
	mainb SDWORD 0

.code

main PROC
	push L1
	pop maini
	push L2
	push L3
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop mainb
	push mainb
	call OutputInt
	call ExitProcess
main ENDP
end main