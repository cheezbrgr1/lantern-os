TARGET := i686-elf

ASM      := nasm
CC       := clang --target=$(TARGET)
LD       := clang --target=$(TARGET)
OBJCOPY  := objcopy

LIBC_PATH    := /usr/i686-elf-clang/lib
INCLUDE_PATH := /usr/i686-elf-clang/include

# Kernel linker flags
LDFLAGS := -fuse-ld=lld -nostdlib -no-pie \
           -Wl,-m,elf_i386 -Wl,-T,linker.ld \
           -L$(LIBC_PATH)

# Find LLVM's resource directory dynamically.
CLANG_RESOURCE_DIR := $(shell $(CC) -print-resource-dir)

# Find the installed 32-bit x86 compiler runtime.
COMPILER_RT := $(shell find "$(CLANG_RESOURCE_DIR)" \
    -type f -name 'libclang_rt.builtins-i386.a' \
    -print -quit 2>/dev/null)

# Fail early if compiler-rt is missing.
ifeq ($(strip $(COMPILER_RT)),)
$(error Could not find libclang_rt.builtins-i386.a under $(CLANG_RESOURCE_DIR))
endif

# Link Picolibc first, then LLVM's compiler runtime.
LIBS := -L$(LIBC_PATH) -lc $(COMPILER_RT)

ASFLAGS := -f elf32

DATE := $(shell date)
ARCH := $(shell $(CC) -dumpmachine)

CFLAGS := -g -ffreestanding -fno-stack-protector \
          -fno-pic -fno-pie \
          -std=c99 -Wall -Wextra -U__TLS -fcommon \
          -I$(shell pwd)/../include -I$(INCLUDE_PATH) \
          -D__BUILD_DATE__="\"$(DATE)\"" \
          -D__BUILD_ARCH__="\"$(ARCH)\"" \
          -DNO_DIR