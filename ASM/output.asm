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
	L1 SDWORD 2
	L2 SDWORD 20

.data
	buffer BYTE 256 dup(0)

.code

f PROC fi : SDWORD
	push fi
	call OutputInt
	ret
f ENDP

f2 PROC f2i : SDWORD
	push 2
	jmp local0
local0:
	pop eax
	ret
f2 ENDP

main PROC
	push L2
	call f
	call ExitProcess
main ENDP
end main