#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>




int main() {
    char buffer[1024] = "gia luong";
    int fd = open("/dev/lab4_2_tran_gia_luong", O_RDWR);

    if (fd == -1) {
        printf("file khong ton tai\n");
        exit(0);
    }

    write(fd, buffer, strlen(buffer));
    printf("write to device\n");

    memset(buffer, 0, sizeof(buffer));
    read(fd, buffer, 1024);

    printf("data: %s\n", buffer);

    return 0;
}
