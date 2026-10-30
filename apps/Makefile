include ../src/settings.mk

# Application compiler flags
APP_CFLAGS := -ffreestanding -fno-stack-protector \
              -fno-pic -fno-pie \
              -std=c99 -Wall -Wextra -U__TLS -fcommon \
              -I$(shell pwd)/../include -I$(INCLUDE_PATH)

# Application linker flags
APP_LDFLAGS := -fuse-ld=lld -nostdlib -no-pie \
               -Wl,-m,elf_i386 -Wl,-T,app.ld -Wl,-e,_start \
               -L$(LIBC_PATH)

STUB_SRC    := app_stub.c
STUB_OBJ    := app_stub.o
SYSCALL_SRC := user_syscalls.c
SYSCALL_OBJ := user_syscalls.o

# Every C file except the runtime files becomes an application
APP_SRCS := $(filter-out $(STUB_SRC) $(SYSCALL_SRC),$(wildcard *.c))
APP_OBJS := $(APP_SRCS:.c=.o)
APP_ELFS := $(APP_OBJS:.o=.elf)

all: $(APP_ELFS)

$(STUB_OBJ): $(STUB_SRC)
	$(CC) $(APP_CFLAGS) -c $< -o $@

$(SYSCALL_OBJ): $(SYSCALL_SRC)
	$(CC) $(APP_CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(APP_CFLAGS) -c $< -o $@

# Link objects first, then libraries.
%.elf: %.o $(STUB_OBJ) $(SYSCALL_OBJ)
	$(LD) $(APP_LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(STUB_OBJ) $(SYSCALL_OBJ) $(APP_OBJS) $(APP_ELFS)

.PHONY: all clean