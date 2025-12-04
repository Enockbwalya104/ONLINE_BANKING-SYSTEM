#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user {
    char phone[50];
    char acc[50];
    char password[50];
    float balance;
};

int main() {
    struct user usr, usr1;
    FILE *fp;
    char filename[50], phone[50], pword[50];
    int choice, opt;
    char cont = 'y';
    float amount;

    printf("* ONLINE BANKING SYSTEM \n\n");
    printf("\n1. Create an account");
    printf("\n2. Login into an account\t");
    printf("\n\nEnter choice:\t");
    scanf("%d", &opt);

    if(opt == 1) {
        printf("Enter account number:\t");
        scanf("%s", usr.acc);
        printf("\nEnter phone number:\t");
        scanf("%s", usr.phone);
        printf("Enter your new password:\t");
        scanf("%s", usr.password);
        usr.balance = 0;

        strcpy(filename, usr.phone);
        fp = fopen(strcat(filename, ".dat"), "wb");
        if(fp == NULL) {
            printf("\nError creating account file.");
            return 1;
        }

        if(fwrite(&usr, sizeof(struct user), 1, fp) != 0) {
            printf("\n\nAccount successfully registered");
        } else {
            printf("\n\nSomething went wrong, try again");
        }
        fclose(fp);
    }

    else if(opt == 2) {
        printf("\nPhone number:\t");
        scanf("%s", phone);
        printf("\nEnter password:\t");
        scanf("%s", pword);

        strcpy(filename, phone);
        fp = fopen(strcat(filename, ".dat"), "rb");
        if(fp == NULL) {
            printf("\nAccount not registered");
        } else {
            fread(&usr, sizeof(struct user), 1, fp);
            fclose(fp);

            if(strcmp(pword, usr.password) == 0) {
                printf("\n\tWelcome %s", usr.phone);

                while(cont == 'y') {
                    printf("\n\nPress 1 to check balance");
                    printf("\nPress 2 to deposit an amount");
                    printf("\nPress 3 to withdraw");
                    printf("\nPress 4 to online transfer");
                    printf("\nPress 5 to change password");
                    printf("\n\nYour choice:\t");
                    scanf("%d", &choice);

                    switch(choice) {
                        case 1:
                            printf("\nYour current balance is K%.2f", usr.balance);
                            break;

                        case 2:
                            printf("\nEnter the amount:\t");
                            scanf("%f", &amount);
                            usr.balance += amount;
                            fp = fopen(filename, "wb");
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            fclose(fp);
                            printf("\nSuccessfully deposited.");
                            break;

                        case 3:
                            printf("\nEnter the amount:\t");
                            scanf("%f", &amount);
                            if(amount > usr.balance) {
                                printf("\nInsufficient balance");
                            } else {
                                usr.balance -= amount;
                                fp = fopen(filename, "wb");
                                fwrite(&usr, sizeof(struct user), 1, fp);
                                fclose(fp);
                                printf("\nYou have withdrawn K%.2f", amount);
                            }
                            break;

                        case 4:
                            printf("\nEnter recipient phone number:\t");
                            scanf("%s", phone);
                            printf("\nEnter amount to transfer:\t");
                            scanf("%f", &amount);

                            if(amount > usr.balance) {
                                printf("\nInsufficient balance");
                            } else {
                                strcpy(filename, phone);
                                fp = fopen(strcat(filename, ".dat"), "rb");
                                if(fp == NULL) {
                                    printf("\nRecipient account not found");
                                } else {
                                    fread(&usr1, sizeof(struct user), 1, fp);
                                    fclose(fp);

                                    usr1.balance += amount;
                                    fp = fopen(filename, "wb");
                                    fwrite(&usr1, sizeof(struct user), 1, fp);
                                    fclose(fp);

                                    strcpy(filename, usr.phone);
                                    fp = fopen(strcat(filename, ".dat"), "wb");
                                    usr.balance -= amount;
                                    fwrite(&usr, sizeof(struct user), 1, fp);
                                    fclose(fp);

                                    printf("\nTransferred K%.2f to %s", amount, phone);
                                }
                            }
                            break;

                        case 5:
                            printf("\nEnter new password:\t");
                            scanf("%s", pword);
                            strcpy(usr.password, pword);
                            fp = fopen(filename, "wb");
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            fclose(fp);
                            printf("\nPassword successfully changed");
                            break;

                        default:
                            printf("\nInvalid option");
                    }

                    printf("\nDo you want to continue transactions [y/n]?\t");
                    scanf(" %c", &cont);
                }
            } else {
                printf("\nInvalid password");
            }
        }
    }

    return 0;
}

