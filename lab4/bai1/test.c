#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


int main() {
    char buffer[1024] = "TRAN GIA LUONG";
    int fd = open("/dev/lab4_1_tran_gia_luong", O_RDWR);

    if (fd < 0) {
        printf("driver file not exist\n");
        exit(0);
    }
    
    write(fd, buffer, strlen(buffer));
    printf("write to device\n");

    memset(buffer, 0, sizeof(buffer));
    read(fd, buffer, 1024);

    printf("data read from device: %s", buffer);

    return 0;
}
