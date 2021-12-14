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
	L1 SDWORD 5
	L2 SDWORD 3
	L3 BYTE "5^3 = ", 0
	L4 BYTE "Случайное число: ", 0
	L5 SDWORD 1
	L6 BYTE "1234567h#jknf", 0
	L7 BYTE " строка: ", 0

.data
	buffer BYTE 256 dup(0)
	maini SDWORD 0
	mainr SDWORD 0
	mainstr DWORD ?

.code

main PROC
	push L1
	pop maini
	push maini
	push L2
	pop edx
	pop edx
	push L2
	push maini
	call mpow
	push eax
	pop maini
	push offset L3
	call OutputStr
	push maini
	call OutputIntLn
	push offset L4
	call OutputStr
	push L5
	push L1
	pop edx
	pop edx
	push L1
	push L5
	call mrand
	push eax
	pop mainr
	push mainr
	call OutputIntLn
	push offset L6
	pop mainstr
	push offset L7
	call OutputStr
	push mainstr
	call OutputStr
	call ExitProcess
main ENDP
end main