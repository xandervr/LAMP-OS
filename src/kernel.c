
#include "keyboard_map.h"
#include "commands.h"

#define LINE_COUNT 25
#define COLUMNS_COUNT 80
#define BYTES 2
#define SCREENSIZE BYTES * COLUMNS_COUNT * LINE_COUNT

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

extern char *os_version = "0.1a"; // OS Version
extern char *os_cmd_line = "root@localhost:!# ";

extern unsigned char keyboard_map[];
extern unsigned char keyboard_num_lock_map[];
extern unsigned char keyboard_caps_lock_map[];
extern unsigned char keyboard_caps_num_lock_map[];
extern char *commands_list[];
extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern char write_port(unsigned short port, unsigned char data);
extern char write_led(unsigned char data);
extern void load_idt(unsigned long *idt_ptr);
extern void system_halt(void); // shutdown system

void kprint(const char *str); // text printer
void set_console_color(const char *clr); // change font color
int str_cmp(const char *str1, const char *str2); // compare 2 strings
void str_cat(char *str1, char *str2); // add str2 to str1
int str_len(char *str); // count string length
void str_chr(unsigned char *cmd, unsigned char chr); // add char to string
void idt_init(void); // init idt
void kb_init(void); // init keyboard
void kprint_newline(void); // print newline
void clear_screen(void); // clear the screen
void init_command(void); // init commands
void execute_command(void); // execute command
void clear_command(void); // erase command
void clear_last_character(void); // erase last character

char *vidptr = (char*)0xb8000; // video memory address
char color = (char)0x07; // set output color
unsigned int current_loc = 0; // follow video memory address
extern int num_lock_pressed = 0; // check if numlock is pressed
extern int caps_lock_pressed = 0; // check if caps lock is pressed
extern int shift_pressed = 0; // check if shift is pressed
extern unsigned char *keyboard_mapping = keyboard_map; // set the keyboard layout
extern unsigned char *command_str = 0; // keep track of last entered commands
extern unsigned int command_loc = 0; // follow command string location

// keyboard setup
struct IDT_entry {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

void main(void) {
	clear_screen();
	init_command();
	clear_command();
	kprint("######################################");
	kprint_newline();
	kprint("# LAMP OS - (Build 20)               #");
	kprint_newline();
	kprint("# Developed by Xander Van Raemdonck  #");
	kprint_newline();
	kprint("######################################");
	kprint_newline();
    kprint_newline();

    set_console_color("purple");
	kprint(os_cmd_line);
    set_console_color("white");

	idt_init();
	kb_init();

	while(1);
}


void idt_init(void) {

	unsigned long keyboard_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	keyboard_address = (unsigned long)keyboard_handler;
	IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = INTERRUPT_GATE;
	IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

	// ICW1
	write_port(0x20, 0x11);
	write_port(0xA0, 0x11);

	// ICW2
	write_port(0x21, 0x20);
	write_port(0xA1, 0x28);

	// ICW3
	write_port(0x21, 0x00);
	write_port(0xA1, 0x00);

	// ICW4
	write_port(0x21, 0x01);
	write_port(0xA1, 0x01);

	// mask int's
	write_port(0x21, 0xff);
	write_port(0xA1, 0xff);

	idt_address = (unsigned long)IDT;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16;

	load_idt(idt_ptr);
}

void kb_init(void) {
	write_port(0x21, 0xFD); // enables keyboard IRQ1
}

void kprint(const char *str) {
	unsigned int i = 0;
	while(str[i] != '\0') {
        if(current_loc==SCREENSIZE) {
            clear_screen();
            current_loc=0;
        }
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = color;
	}
}

void kprint_newline(void) {
    if(current_loc==SCREENSIZE) {
            clear_screen();
            current_loc=0;
    }
	unsigned int line_size = BYTES * COLUMNS_COUNT;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

void set_console_color(const char *clr) {
	if(str_cmp(clr, "blue")==0) {
		color = (char)0x01;
	} else if(str_cmp(clr, "green")==0) {
		color = (char)0x02;
	} else if(str_cmp(clr, "cyan")==0) {
		color = (char)0x03;
	} else if(str_cmp(clr, "red")==0) {
		color = (char)0x04;
	} else if(str_cmp(clr, "purple")==0) {
		color = (char)0x05;
	} else if(str_cmp(clr, "brown")==0) {
		color = (char)0x04;
	} else if(str_cmp(clr, "grey")==0) {
		color = (char)0x07;
	} else if(str_cmp(clr, "yellow")==0) {
		color = (char)0x0E;
	} else if(str_cmp(clr, "white")==0) {
		color = (char)0x0F;
	} else {
		color = (char)0x0F;
	}
return;
}

// STRING FUNCTIONS
int str_cmp(const char *str1, const char *str2) {
	int status = 0;
	unsigned int i = 0;
	while(str1[i]!='\0' || str2[i]!='\0')  {
		if(str1[i]!=str2[i]) {
			status = 1;
			break;
		}
	i++;
	}

	return status;
}

void str_cat(char *str1, char *str2) {
    unsigned int i = 0;
    int str1len = str_len(str1);
    int str2len = str_len(str2);
    for(i;i<=str2len;i++) {
        str1[str1len + i] = str2[i];
    }
return;
}

void str_chr(unsigned char *cmd, unsigned char chr) {
    cmd[command_loc] = chr;
    command_loc++;
return;
}

int str_len(char *str) {
    unsigned int i = 0;
    int strlen = 0;
    while(str[i]!='\0') {
        strlen++;
        i++;
    }
    return strlen;
}

void clear_screen(void) {
	unsigned int i = 0;
	while(i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = color;
	}
}

// clear command tracker
void clear_command(void) {
    unsigned int i = 0;
    while(command_str[i]!='\0') {
        command_str[i] = 0;
        i++;
    }
    command_loc = 0;
return;
}

void init_command(void) {
    unsigned int i = 0;
    for(i;i<10;i++) {
        command_str[i] = 'x';
    }
    clear_command();
return;
}

void clear_last_character(void) {
    command_loc--;
    vidptr[current_loc--] = 0x00;
    vidptr[current_loc--] = 0x00;
    command_str[command_loc] = 0;
return;
}

void keyboard_handler_main(void) {
	unsigned char status;
	char keycode;
    if(current_loc==SCREENSIZE) {
            clear_screen();
            current_loc=0;
    }
	// set keyboard layout
    if(caps_lock_pressed==1 && shift_pressed==0) {
        write_led(0x07);
        keyboard_mapping =  keyboard_caps_lock_map;
    } else if(caps_lock_pressed==1 && shift_pressed==1) {
        keyboard_mapping = keyboard_map;
    } else if(num_lock_pressed==1) {
        keyboard_mapping = keyboard_num_lock_map;
    } else if(caps_lock_pressed==1 && num_lock_pressed==1) {
        keyboard_mapping = keyboard_caps_num_lock_map;
    } else if(shift_pressed==1 && num_lock_pressed == 0) {
        keyboard_mapping = keyboard_caps_lock_map;
    } else if(shift_pressed==1 && num_lock_pressed == 1) {
        keyboard_mapping = keyboard_caps_num_lock_map;
    } else {
        keyboard_mapping = keyboard_map;
    }

    if(shift_pressed==1) { // disable shift after key
        shift_pressed = 0;
    }

	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);
	if(status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);
		if(keycode < 0) {
			return;
		}
		if(keycode == keyboard_special_keys[0]) {
			execute_command();
			return;
		}
		if(keycode == keyboard_special_keys[2]) {
            clear_last_character();
            return;
		}
		if(keycode == keyboard_special_keys[1]) {
			system_halt();
			return;
		}
		if(keycode == keyboard_special_keys[3] || keycode == keyboard_special_keys[4]) {
            shift_pressed = 1;
            return;
		}
		if(keycode == keyboard_special_keys[5] && caps_lock_pressed==0) {
            caps_lock_pressed = 1;
            return;
		}
		if(keycode == keyboard_special_keys[5] && caps_lock_pressed==1) {
            caps_lock_pressed = 0;
            return;
		}
		if(keycode == keyboard_special_keys[6] && num_lock_pressed==0) {
            num_lock_pressed = 1;
            return;
		}
		if(keycode == keyboard_special_keys[6] && num_lock_pressed==1) {
            num_lock_pressed = 0;
            return;
		}
        str_chr(command_str, keyboard_mapping[(unsigned char) keycode]);
		vidptr[current_loc++] = keyboard_mapping[(unsigned char) keycode];
		vidptr[current_loc++] = color;
	}
}

void execute_command(void) {

	set_console_color("red");
	kprint_newline();
	if(str_cmp(command_str, commands_list[0])==0) {
        kprint("Version ");
        kprint(os_version);
	} else if(str_cmp(command_str, commands_list[1])==0) {
        kprint("--- Command list ---");
        kprint_newline();
        kprint("version - Displays OS version");
        kprint_newline();
        kprint("help - Displays help menu");
        kprint_newline();
        kprint("shutdown - Shutdown the system");
	} else if(str_cmp(command_str, commands_list[2])==0) {
        kprint("Shutting down...");
        system_halt();
	} else {
        kprint("Syntax error: Unknown command ");
        kprint(command_str);
	}
	clear_command();
	kprint_newline();
	set_console_color("purple");
	kprint(os_cmd_line);
    set_console_color("white");

return;
}

