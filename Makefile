TARGET = Lamp
CC = clang
all:
	@echo "[INFO] Building kernel..."
	nasm -f elf32 ./src/kernel.asm -o ./build/kasm.o
	gcc -Wmultichar -Woverflow -m32 -c ./src/kernel.c -o ./build/kc.o
	ld -m elf_i386 -T ./linker/link.ld -o ./src/release/$(TARGET) ./build/kasm.o ./build/kc.o
	make clean
	cat README.md
	qemu-system-i386 -kernel ./build/release/$(TARGET)

linux:
	@echo "[INFO] Building kernel..."
	nasm -f elf32 ./src/kernel.asm -o ./build/kasm.o
	gcc -Wmultichar -Woverflow -m32 -c ./src/kernel.c -o ./build/kc.o
	ld -m elf_i386 -T ./src/link.ld -o ./build/release/$(TARGET) ./build/kasm.o ./build/kc.o
	make clean
	cat README.md
	qemu-system-i386 -kernel ./build/release/$(TARGET)

osx:
	@echo "[INFO] Building kernel..."
	nasm -f macho32 ./src/kernel.asm -o ./build/kasm.o
	$(CC) -arch i386 -Wmultichar -Woverflow -m32 -c ./src/kernel.c -o ./build/kc.o
	ld -demangle -dynamic -arch i386 -force_cpusubtype_ALL -o ./build/release/$(TARGET) ./build/kasm.o ./build/kc.o
	make clean
	cat README.md
	qemu-system-i386 -kernel ./build/release/$(TARGET)

clean:
	@echo "[INFO] Cleaning up..."
	$(RM) ./build/kasm.o
	$(RM) ./build/kc.o

wipe:
	@echo "[INFO] Wiping kernel..."
	$(RM) ./build/release/$(TARGET)
