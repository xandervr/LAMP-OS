

unsigned char keyboard_special_keys[] =
{
    0x1C, // ENTER
    0x01, // ESC
    0x0E, // BACKSPACE
    0x2A, // LEFT SHIFT
    0x36, // RIGHT SHIFT
    0x3A, // CAPS LOCK
    0x45, // NUM LOCK
};

unsigned char keyboard_map[] =
{
0, 27, '&', /*'é'*/0, '\"', '\'', '(', 0, /*'è'*/0, '!', /* 9 */
/*'ç'*/0, /*'à'*/0, ')', '-', '\b', /* Backspace */
'\t', /* Tab */
'a', 'z', 'e', 'r', /* 19 */
't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n', /* Enter key */
0, /* 29 - Control */
'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', /* 39 */
'\'', '`', 0, /* Left shift */
'<', 'w', 'x', 'c', 'v', 'b', 'n', /* 49 */
',', ';', ':', '=', 0, /* Right shift */
'*',
0, /* Alt */
' ', /* Space bar */
0, /* Caps lock */
0, /* 59 - F1 key ... > */
0, 0, 0, 0, 0, 0, 0, 0,
0, /* < ... F10 */
0, /* 69 - Num lock*/
0, /* Scroll Lock */
0, /* Home key */
0, /* Up Arrow */
0, /* Page Up */
'-',
0, /* Left Arrow */
0,
0, /* Right Arrow */
'+',
0, /* 79 - End key*/
0, /* Down Arrow */
0, /* Page Down */
0, /* Insert Key */
0, /* Delete Key */
0, 0, 0,
0, /* F11 Key */
0, /* F12 Key */
0, /* All other keys are undefined */
};

unsigned char keyboard_num_lock_map[] =
{
0, 27, '&', /*'é'*/0, '\"', '\'', '(', 0, /*'è'*/0, '!', /* 9 */
/*'ç'*/0, /*'à'*/0, ')', '-', '\b', /* Backspace */
'\t', /* Tab */
'a', 'z', 'e', 'r', /* 19 */
't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n', /* Enter key */
0, /* 29 - Control */
'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', /* 39 */
'\'', '`', 0, /* Left shift */
'<', 'w', 'x', 'c', 'v', 'b', 'n', /* 49 */
',', ';', ':', '=', 0, /* Right shift */
'*',
0, /* Alt */
' ', /* Space bar */
0, /* Caps lock */
0, /* 59 - F1 key ... > */
0, 0, 0, 0, 0, 0, 0, 0,
0, /* < ... F10 */
0, /* 69 - Num lock*/
0, /* Scroll Lock */
'7', /* Home key */
'8', /* Up Arrow */
'9', /* Page Up */
'-',
'4', /* Left Arrow */
'5',
'6', /* Right Arrow */
'+',
'1', /* 79 - End key*/
'2', /* Down Arrow */
'3', /* Page Down */
'0', /* Insert Key */
'.', /* Delete Key */
0, 0, 0,
0, /* F11 Key */
0, /* F12 Key */
0, /* All other keys are undefined */
};

unsigned char keyboard_caps_lock_map[] =
{
0, 27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
'9', '0', /*'°'*/0, '_', '\b', /* Backspace */
'\t', /* Tab */
'A', 'Z', 'E', 'R', /* 19 */
'T', 'Y', 'U', 'I', 'O', 'P', '"', '*', '\n', /* Enter key */
0, /* 29 - Control */
'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', /* 39 */
'%', /*'£'*/0, 0, /* Left shift */
'>', 'W', 'X', 'C', 'V', 'B', 'N', /* 49 */
'?', '.', '/', '+', 0, /* Right shift */
'*',
0, /* Alt */
' ', /* Space bar */
0, /* Caps lock */
0, /* 59 - F1 key ... > */
0, 0, 0, 0, 0, 0, 0, 0,
0, /* < ... F10 */
0, /* 69 - Num lock*/
0, /* Scroll Lock */
0, /* Home key */
0, /* Up Arrow */
0, /* Page Up */
'-',
0, /* Left Arrow */
0,
0, /* Right Arrow */
'+',
0, /* 79 - End key*/
0, /* Down Arrow */
0, /* Page Down */
0, /* Insert Key */
0, /* Delete Key */
0, 0, 0,
0, /* F11 Key */
0, /* F12 Key */
0, /* All other keys are undefined */
};

unsigned char keyboard_caps_num_lock_map[] =
{
0, 27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
'9', '0', /*'°'*/0, '_', '\b', /* Backspace */
'\t', /* Tab */
'A', 'Z', 'E', 'R', /* 19 */
'T', 'Y', 'U', 'I', 'O', 'P', '"', '*', '\n', /* Enter key */
0, /* 29 - Control */
'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', /* 39 */
'%', /*'£'*/0, 0, /* Left shift */
'>', 'W', 'X', 'C', 'V', 'B', 'N', /* 49 */
'?', '.', '/', '+', 0, /* Right shift */
'*',
0, /* Alt */
' ', /* Space bar */
0, /* Caps lock */
0, /* 59 - F1 key ... > */
0, 0, 0, 0, 0, 0, 0, 0,
0, /* < ... F10 */
0, /* 69 - Num lock*/
0, /* Scroll Lock */
'7', /* Home key */
'8', /* Up Arrow */
'9', /* Page Up */
'-',
'4', /* Left Arrow */
'5',
'6', /* Right Arrow */
'+',
'1', /* 79 - End key*/
'2', /* Down Arrow */
'3', /* Page Down */
'0', /* Insert Key */
'.', /* Delete Key */
0, 0, 0,
0, /* F11 Key */
0, /* F12 Key */
0, /* All other keys are undefined */
};


