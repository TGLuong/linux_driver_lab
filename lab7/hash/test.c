#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>

#define MEM_SIZE 1024

typedef struct Account{
    char username[200];
    uint8_t md5[33];
    uint8_t sha1[41];
    uint8_t sha224[57];
} Account;

Account accounts[200];
uint16_t size = 0;

int add_account(Account account);
int remove_account(uint16_t ind);
int login(int hash_fd, char *username, char *password);
int load_account(char *file_path);
int open_thiet_bi(char * ten_thiet_bi);
int read_line(int fd, char *out, uint8_t *length);
int string_to_account(char *data, Account *account);
int account_to_string(Account *account, char *output);
int hash(int fd, char *type, char *data, size_t len, char *out);
int hextostring(char *in, int len, char *out);

int add_account(Account account) {
    strcpy(accounts[size].username, account.username);
    strcpy(accounts[size].md5, account.md5);
    strcpy(accounts[size].sha1, account.sha1);
    strcpy(accounts[size].sha224, account.sha224);
    size++;
    return 0;
}

int remove_account(uint16_t ind) {
    for (int i = ind; i < size; i++) {
        accounts[i] = accounts[i + 1];
    }
    size--;
}

int load_account(char *file_path) {
    int fd = open(file_path, O_CREAT | O_RDWR);
    char buffer[500];
    uint8_t length;
    Account account;
    while (read_line(fd, buffer, &length)) {
        string_to_account(buffer, &account);
        add_account(account);
    }
    return 0;
}

int print_account() {
    printf("%-5s%-15s%-35s%-45s%-57s\n", "STT", "username", "md5", "sha1", "sha224");
    for (int i = 0; i < size; i++) {
        printf("%-5d%-15s%-35s%-45s%-57s\n", i + 1, accounts[i].username, accounts[i].md5, accounts[i].sha1, accounts[i].sha224);
    }
}

int save_account(char *file_path) {
    char replace_file[1000], write_buffer[1000];
    sprintf(replace_file, "%s.copy", file_path);
    printf("buf: %s\n", replace_file);

    int fd = open(replace_file, O_CREAT | O_TRUNC | O_RDWR, S_IRWXO | S_IWGRP | S_IRGRP);
    for (int i = 0; i < size; i++) {
        account_to_string(&accounts[i], write_buffer);
        write(fd, write_buffer, strlen(write_buffer));
        write(fd, "\n", 1);
    }

    close(fd);
    rename(replace_file, file_path);

    return 0;
}

int login(int hash_fd, char *username, char *password) {
    for (int i = 0; i < size; i++) {
        if (strcmp(username, accounts[i].username) == 0) {
            char buffer[200], hash_string[200];
            int length = hash(hash_fd, "md5", password, strlen(password), buffer);
            hextostring(buffer, length, hash_string);
            if (strcmp(hash_string, accounts[i].md5) != 0) {
                return 0;
            }
            length = hash(hash_fd, "sha1", password, strlen(password), buffer);
            hextostring(buffer, length, hash_string);
            if (strcmp(hash_string, accounts[i].sha1) != 0) {
                return 0;
            }
            length = hash(hash_fd, "sha224", password, strlen(password), buffer);
            hextostring(buffer, length, hash_string);
            if (strcmp(hash_string, accounts[i].sha224) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int open_thiet_bi(char * ten_thiet_bi) {
    int fd = open(ten_thiet_bi, O_RDWR);
    if (fd == -1) {
        printf("file driver khong the mo\n");
        exit(0);
    }
    return fd;
}

int read_line(int fd, char *out, uint8_t *length) {
    char buffer[1] = {0};
    uint8_t len = 0;

    memset(out, 0, sizeof(out));
    
    while (read(fd, buffer, 1) != 0 && buffer[0] != '\n') {
        sprintf(out, "%s%c", out, buffer[0]);
        len++;
    }
    (*length) = len;
    if (buffer[0] != 0) return 1; else return 0;
}

int string_to_account(char *data, Account *account) {
    char username[200];
    char md5[200];
    char sha1[200];
    char sha224[200];

    memset(username, 0, sizeof(username));
    memset(md5, 0, sizeof(md5));
    memset(sha1, 0, sizeof(sha1));
    memset(sha224, 0, sizeof(sha224));
    memset(account->username, 0, sizeof(account->username));
    memset(account->md5, 0, sizeof(account->md5));
    memset(account->sha1, 0, sizeof(account->sha1));
    memset(account->sha224, 0, sizeof(account->sha224));

    sscanf(data, "%[^:]:%[^:]:%[^:]:%[^:]", username, md5, sha1, sha224);

    sprintf(account->username, "%s", username);
    sprintf(account->md5, "%s", md5);
    sprintf(account->sha1, "%s", sha1);
    sprintf(account->sha224, "%s", sha224);

    return 0;
}

int account_to_string(Account *account, char *output) {
    memset(output, 0, sizeof(output));
    sprintf(output, "%s:%s:%s:%s", account->username, account->md5, account->sha1, account->sha224);
    return 0;
}

int hash(int fd, char *type, char *data, size_t len, char *out) {
    uint16_t buffer_size = len + 100;
    char buffer[buffer_size];

    memset(out, 0, sizeof(out));
    sprintf(buffer, "type:%s\nvalue:%s\n", type, data);

    write(fd, buffer, sizeof(buffer));
    return read(fd, out, sizeof(out));
}

int hextostring(char *in, int len, char *out) {
    memset(out, 0, sizeof(out));
    for (int i = 0; i < len; i++) {
        sprintf(out, "%s%02hhx", out, in[i]);
    }
    return 0;
}

int main() {
    char *db_path = "./db.txt";
    int choice = 0;
    int hash_fd = open("/dev/lab7_ma_hoa", O_RDWR);
    char username[200], password[200], hash_buffer[200];
    if (hash_fd == -1) {
        printf("khong mo dc file driver\n");
        exit(0);
    }

    load_account(db_path);
    while (1) {
        system("clear");
        print_account();
        printf("1. them account\n");
        printf("2. xoa account\n");
        printf("3. login\n");
        printf("4. thoat\n");

        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                Account account;
                int length;
                printf("username: ");
                fgets(username, sizeof(username), stdin);
                username[strlen(username) - 1] = 0;
                printf("password: ");
                fgets(password, sizeof(password), stdin);
                password[strlen(password) - 1] = 0;

                printf("u: %s, p: %s\n", username, password);
                strcpy(account.username, username);
                length = hash(hash_fd, "md5", password, strlen(password), hash_buffer);
                hextostring(hash_buffer, length, account.md5);
                length = hash(hash_fd, "sha1", password, strlen(password), hash_buffer);
                hextostring(hash_buffer, length, account.sha1);
                length = hash(hash_fd, "sha224", password, strlen(password), hash_buffer);
                hextostring(hash_buffer, length, account.sha224);

                // printf("username: %s\n", account.username);
                // printf("md5: %s\n", account.md5);
                // printf("sha1: %s\n", account.sha1);
                // printf("sha224: %s\n", account.sha224);
                add_account(account);
                save_account(db_path);
                break;
            }
            case 2: {
                int index;
                scanf("%d", &index);
                getchar();
                printf("%d\n", index);
                remove_account(index);
                save_account(db_path);
                break;
            }
            case 3: {
                printf("username: ");
                fgets(username, sizeof(username), stdin);
                username[strlen(username) - 1] = 0;
                printf("password: ");
                fgets(password, sizeof(password), stdin);
                password[strlen(password) - 1] = 0;
                if (login(hash_fd, username, password)) {
                    printf("login success\n");
                } else {
                    printf("login failure\n");
                }
                getchar();
            }
            case 4: {
                exit(0);
            }
            default:
                break;
        }


    }

    return 0;
}