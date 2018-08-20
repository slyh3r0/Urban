ASM = nasm
ASMFLAGS = -fbin

ASMOBJ = kboot.bin
HEADERS = $(filter-out $(patsubst %.bin, %.asm, $(ASMOBJ)), $(wildcard *.asm))

.PHONY: clean

$(ASMOBJ): $(patsubst %.bin, %.asm, $(ASMOBJ)) $(HEADERS)
	$(ASM) $(ASMFlAGS) $< -o $@

run: $(ASMOBJ)
	qemu-system-x86_64 $<

clean:
	rm kboot.bin

