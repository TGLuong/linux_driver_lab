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



int main() {
    int fd = -1;
    int len = 0;
    char buffer[MEM_SIZE], value[800];
    fd = open_thiet_bi("/dev/lab7_ma_hoa");

    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "type:%s\nvalue:%s\n", "sha1", "gialuong");
    write(fd, buffer, MEM_SIZE);
    read(fd, value, sizeof(value));

    printf("ban ma: %s\n", value);



    return 0;
    while (1) {
        system("clear");
        printf("1. nhap vao mot xau\n");
        printf("2. ma hoa dich chuyen\n");
        printf("3. ma hoa thay the\n");
        printf("4. ma hoa hoan vi\n");
        printf("5. giai ma dich chuyen\n");
        printf("6. giai ma hoan vi\n");
        printf("7. giai ma thay the\n");

        int choose;
        scanf("%d", &choose);
        getchar();

        switch (choose) {
            case 1:
                fgets(value, MEM_SIZE, stdin);
                len = strlen(value);
                value[len - 1] = 0;
                printf("%s\n", value);
                getchar();
                break;
                
            case 2:
                memset(buffer, 0, sizeof(buffer));

                sprintf(buffer, "cmd:%s\nvalue:%s\n", "ma-hoa-dich-chuyen", value);

                write(fd, buffer, MEM_SIZE);
                
                memset(value, 0, sizeof(value));
                read(fd, value, sizeof(value));

                printf("ban ma: %s\n", value);
                getchar();
                break;
            
            case 3:
                memset(buffer, 0, sizeof(buffer));

                sprintf(buffer, "cmd:%s\nvalue:%s\n", "ma-hoa-thay-the", value);

                write(fd, buffer, MEM_SIZE);
                
                memset(value, 0, sizeof(value));
                read(fd, value, sizeof(value));

                printf("ban ma: %s\n", value);
                getchar();
                break;

            case 4:
                memset(buffer, 0, sizeof(buffer));

                sprintf(buffer, "cmd:%s\nvalue:%s\n", "ma-hoa-hoan-vi", value);

                write(fd, buffer, MEM_SIZE);
                
                memset(value, 0, sizeof(value));
                read(fd, value, sizeof(value));

                printf("ban ma: %s\n", value);
                getchar();
                break;

            case 5:
                memset(buffer, 0, MEM_SIZE);

                sprintf(buffer, "cmd:%s\nvalue:%s\n", "giai-ma-dich-chuyen", value);

                write(fd, buffer, MEM_SIZE);

                memset(value, 0, sizeof(value));
                read(fd, value, sizeof(value));

                printf("ban ro: %s\n", value);
                getchar();
                break;

            case 6:
                memset(buffer, 0, MEM_SIZE);

                sprintf(buffer, "cmd:%s\nvalue:%s\n", "giai-ma-thay-the", value);

                write(fd, buffer, MEM_SIZE);

                memset(value, 0, sizeof(value));
                read(fd, value, sizeof(value));

                printf("ban ro: %s\n", value);
                getchar();
                break;

            case 7:
                memset(buffer, 0, MEM_SIZE);

                sprintf(buffer, "cmd:%s\nvalue:%s\n", "giai-ma-hoan-vi", value);

                write(fd, buffer, MEM_SIZE);

                memset(value, 0, sizeof(value));
                read(fd, value, sizeof(value));

                printf("ban ro: %s\n", value);
                getchar();
                break;
            default:
                break;
        }
    }
    
    return 0;
}