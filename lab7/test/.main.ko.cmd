cmd_/home/embedded/linux_driver_lab/lab7/test/main.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000  --build-id  -T ./scripts/module-common.lds -o /home/embedded/linux_driver_lab/lab7/test/main.ko /home/embedded/linux_driver_lab/lab7/test/main.o /home/embedded/linux_driver_lab/lab7/test/main.mod.o;  true