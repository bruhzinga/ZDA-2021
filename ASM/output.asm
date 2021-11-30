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
EXTRN slen: proc
EXTRN scpy: proc
EXTRN mpow: proc
EXTRN mrand: proc

.stack 4096

.const
	L1 SDWORD 83
	L2 SDWORD 3
	L3 SDWORD 1
	L4 SDWORD 5
	L5 BYTE "1234567h#jknf", 0

.data
	buffer BYTE 256 dup(0)
	maini SDWORD 0
	mainr SDWORD 0
	mainstr DWORD ?
	mainlen SDWORD 0

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
	push maini
	call OutputIntLn
	push L3
	push L4
	pop edx
	pop edx
	push L4
	push L3
	call mrand
	push eax
	pop mainr
	push mainr
	call OutputIntLn
	push offset L5
	pop mainstr
	push mainstr
	pop edx
	push mainstr
	call slen
	push eax
	pop mainlen
	push mainlen
	call OutputInt
	call ExitProcess
main ENDP
end main