# LanternOS
LanternOS is a hobbyist OS and kernel made by me to explore how OS's work. It currently has an IDT, a basic GDT, IRQ and ISRs, a basic keyboard and VGA text-mode driver, and an ATA and USTAR fs driver. It also uses a custom bootloader called Lightbulb. It runs on 32-bit x86, and although it boots on x86_64, 64-bit hasn't been thoroughly tested yet and the binaries are still 32-bit. Picolibc has been ported, although very unstable.

## Building
### Prereqs
- An LLVM toolchain (should support `i686-elf`)
- `nasm`
- `make`
- `qemu-system-i386` (if you want to test out the built image)
### Linux
To build, simply run
```sh
make
```
To run the image in qemu, run
```sh
make run
```
### Windows
Not supported :sob:
### MacOS
Haven't tested
## Goals for v0.0.3
- Get into ring 3
- Add paging
- Basic multitasking
## TODO
- Better bootloader
- GUI (maybe?)