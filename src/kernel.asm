
bits 32
section .text

	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002 + 0x00)

global start
global _keyboard_handler
global _read_port
global _write_port
global _write_led
global _load_idt
global _system_halt

extern _main
extern _keyboard_handler_main

_read_port:
	mov edx, [esp + 4]
	in al, dx
	ret

_write_port:
	mov edx, [esp + 4]
	mov al, [esp + 4 + 4]
	out dx, al
	ret

_write_led:

    ret
_load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret

_keyboard_handler:
	call _keyboard_handler_main
	iretd

_system_halt:
	mov ax, 5301h
	xor bx, bx
	int 15h
	je near continue_connection
	cmp ah, 2
	je near continue_connection
	ret

continue_connection:
	mov ax, 530Eh
	int 15h
	ret

start:
	cli
	mov esp, stack_space
	call _main
	hlt

section .bss
resb 8192
stack_space:
