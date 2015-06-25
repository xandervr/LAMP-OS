TARGET = Lamp
all:
	@echo "[INFO] Building kernel..."
	nasm -f elf32 ./build/kernel.asm -o ./build/kasm.o
	gcc -Wmultichar -Woverflow -m32 -c ./build/kernel.c -o ./build/kc.o
	ld -m elf_i386 -T ./build/link.ld -o ./build/release/$(TARGET) ./build/kasm.o ./build/kc.o
	make clean
	cat README.md
	qemu-system-i386 -kernel ./build/release/$(TARGET)
	
unix:
	@echo "[INFO] Building kernel..."
	nasm -f elf32 ./build/kernel.asm -o ./build/kasm.o
	gcc -Wmultichar -Woverflow -m32 -c ./build/kernel.c -o ./build/kc.o
	ld -m elf_i386 -T ./build/link.ld -o ./build/release/$(TARGET) ./build/kasm.o ./build/kc.o
	make clean
	cat README.md
	qemu-system-i386 -kernel ./build/release/$(TARGET)

osx:
	@echo "[INFO] Building kernel..."
	nasm -f macho32 ./build/kernel.asm -o ./build/kasm.o
	./build/gcc-osx/4.9.2/bin/x86_64-apple-darwin14.0.0-gcc-4.9.2 -arch i386 -Wmultichar -Woverflow -m32 -c ./build/kernel.c -o ./build/kc.o
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
