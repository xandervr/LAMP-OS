
bits 32
section .text

	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002 + 0x00)

global start
global keyboard_handler
global read_port
global write_port
global write_led
global load_idt
global system_halt

extern kmain
extern keyboard_handler_main

read_port:
	mov edx, [esp + 4]
	in al, dx
	ret

write_port:
	mov edx, [esp + 4]
	mov al, [esp + 4 + 4]
	out dx, al
	ret

write_led:

    ret
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret

keyboard_handler:
	call keyboard_handler_main
	iretd

system_halt:
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
	call kmain
	hlt

section .bss
resb 8192
stack_space:
