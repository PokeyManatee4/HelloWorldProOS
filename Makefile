corp: 
	as src/boot.s -o lib/corpboot.o
	g++ -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -c src/corporationkernel.cpp -o lib/corpkernel.o
	gcc -ffreestanding -T link.ld lib/corpboot.o lib/corpkernel.o -o bin/corp/os/corp.elf -nostdlib -lgcc
	grub-mkrescue -o isoOutput/HelloWorldOSCorp.iso bin/corp
	@echo Done

pro: 
	as src/boot.s -o lib/proboot.o
	g++ -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -c src/prokernel.cpp -o lib/prokernel.o
	gcc -ffreestanding -T link.ld lib/proboot.o lib/prokernel.o -o bin/Pro/os/pro.elf -nostdlib -lgcc
	grub-mkrescue -o isoOutput/HelloWorldOSPro.iso bin/Pro
	@echo Done

standard: 
	as src/boot.s -o lib/standardboot.o
	g++ -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -c src/corporationkernel.cpp -o lib/corpkernel.o
	gcc -ffreestanding -T link.ld lib/standardboot.o lib/standardkernel.o -o bin/standard/os/standard.elf -nostdlib -lgcc
	grub-mkrescue -o isoOutput/HelloWorldOS-Standard.iso bin/standard
	@echo Done
