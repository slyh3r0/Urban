
AS=i686-elf-as
CC=i686-elf-gcc
LD=i686-elf-gcc

ASFLAGS=
CCFLAGS= -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS= -ffreestanding -O2 -nostdlib -lgcc

BIN=kurban.bin

LINKER= klink.ld

AOBJECTS:= $(patsubst %.s, %.o, $(wildcard *.s))
COBJECTS:= $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS:= $(wildcard *.h)

.PHONY: qemu clean


default: $(BIN) 


$(BIN): $(AOBJECTS) $(COBJECTS)
	$(LD) -T $(LINKER) $(LDFLAGS) -o $@ $^

$(AOBJECTS): %.o : %.s 
	$(AS) $(ASFLAGS) -o $@ $<

$(COBJECTS): %.o: %.c $(HEADERS)
	$(CC) $(CCFLAGS) -o $@ $<

qemu: $(BIN)
	qemu-system-i386 -kernel $<

clean:
	rm -rf $(AOBJECTS) $(COBJECTS) $(BIN)

