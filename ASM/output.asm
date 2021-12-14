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
	L1 BYTE "ÀÁÂ", 0

.data
	buffer BYTE 256 dup(0)

.code

main PROC
	push offset L1
	call OutputStrLn
	call ExitProcess
main ENDP
end main