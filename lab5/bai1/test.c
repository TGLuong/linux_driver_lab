#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define MEM_SIZE 1024

int open_thiet_bi(char * ten_thiet_bi) {
    int fd = open(ten_thiet_bi, O_RDWR);
    if (fd == -1) {
        printf("file driver khong the mo\n");
        exit(0);
    }
    return fd;
}

int doc_so_he_2(int fd, int value, char * result) {
    if (fd == -1) {
        printf("thiet bi chua duoc mo\n");
        return -1;
    }

    char buffer[MEM_SIZE];

    sprintf(buffer, "cmd:bin\nvalue:%d\n", value);
    write(fd, buffer, sizeof(buffer));

    read(fd, result, sizeof(result));

    return 0;
}

int doc_so_he_8(int fd, int value, char * result) {
    if (fd == -1) {
        printf("thiet bi chua duoc mo\n");
        return 0;
    }

    char buffer[MEM_SIZE];

    sprintf(buffer, "cmd:oct\nvalue:%d\n", value);
    write(fd, buffer, sizeof(buffer));

    read(fd, result, sizeof(result));

    return 0;
}

int doc_so_he_16(int fd, int value, char * result) {
    if (fd == -1) {
        printf("thiet bi chua duoc mo\n");
        return -1;
    }

    char buffer[MEM_SIZE];

    sprintf(buffer, "cmd:hex\nvalue:%d\n", value);
    write(fd, buffer, sizeof(buffer));

    read(fd, result, sizeof(result));

    return 0;
}

int main() {
    int fd = -1;
    int value = 0;
    char buffer[MEM_SIZE];
    while (1) {
        system("clear");
        printf("1. open thiet bi\n");
        printf("2. nhap so he 10 (input)\n");
        printf("3. doc so he 2\n");
        printf("4. doc so he 8\n");
        printf("5. doc so he 16\n");
        printf("6. dong thiet bi va ket thuc ctr\n");

        int choose;
        scanf("%d", &choose);

        switch (choose) {
            case 1:
                fd = open_thiet_bi("/dev/lab5_1_tran_gia_luong");
                break;
            case 2:
                printf("nhap so: ");
                scanf("%d", &value);
                break;
            case 3:
                doc_so_he_2(fd, value, buffer);
                printf("he 2: %s\n", buffer);
                getchar();
                getchar();
                break;
            case 4:
                doc_so_he_8(fd, value, buffer);
                printf("he 8: %s\n", buffer);
                getchar();
                getchar();
                break;
            case 5:
                doc_so_he_16(fd, value, buffer);
                printf("he 16: %s\n", buffer);
                getchar();
                getchar();
                break;
            case 6:
                close(fd);
                exit(0);
                break;
            default:
                break;
        }
    }
    
    return 0;
}
