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
	L1 SDWORD 2
	L2 SDWORD 100
	L3 SDWORD 3
	L4 BYTE "Результат = ", 0

.data
	buffer BYTE 256 dup(0)
	count2mul SDWORD 0
	mainres SDWORD 0

.code

count2 PROC count2i : SDWORD
	push count2i
	push L1
	 call multip
	push eax
	pop count2mul
	push count2mul
	jmp local0
local0:
	pop eax
	ret
count2 ENDP

count1 PROC count1i : SDWORD
	mov eax, count1i
	cmp eax, L2
	jl cycle0
	jmp cyclenext0
cycle0:
	push count1i
	call OutputIntLn
	push count1i
	pop edx
	push count1i
	call count2
	push eax
	pop count1i
	mov eax, count1i
	cmp eax, L2
	jl cycle0
cyclenext0:
	push count1i
	jmp local1
local1:
	pop eax
	ret
count1 ENDP

main PROC
	push L3
	pop edx
	push L3
	call count1
	push eax
	pop mainres
	push offset L4
	call OutputStr
	push mainres
	call OutputIntLn
	call ExitProcess
main ENDP
end main