#include<stdio.h>
#include<stdlib.h>

int LoginScreen() {

    char username[50], password[100];
    int in, quit = 0, accntType = 3, c;/*0=Root, 1=Admin, 2=Normal*/
    FILE *filePointer;

    do {

        system("cls");

        printf("\n######## Welcome to Kottawa-Matara Highway Program ########\n\n");
        printf("1. Login\n");
        printf("2. Create Account\n");
        printf("3. Continue\n");
        printf("4. Exit\n");

        do {
            printf("\n>");
            scanf("%d", &in);

            if(in == 1) {
                system("cls");

                printf("\n### Login ###\n\n");
                printf("Enter Username : ");
                scanf("%s", username);
                printf("\nEnter Password : ");
                scanf("%s", password);

                if(strcmp(username, "admin")==0 && strcmp(password, "root")==0) {
                    accntType = 0;
                    system("cls");
                    printf("\nSuccessful login\n");
                    printf("\nPress any key...");
                    getch();
                }
                else {
                    accntType = AccntSearch(username, password);
                    if(accntType != 3) {
                        system("cls");
                        printf("\nSuccessful Login\n");
                        printf("\nPress any key...");
                        getch();
                        break;
                    }
                    else {
                        printf("\nInvalid Username or Password\nTry again or contact an Administrator\n");
                        printf("\nPress any key...");
                        getch();
                    }
                }

                break;
            }
            else if(in == 2) {
                if(accntType < 2) {
                    CreateAccount();
                    break;
                }
                else {
                    printf("Insufficient user privilege\n");
                }
            }
            else if(in == 3) {
                if(accntType != 3) {
                    quit = 1;
                    break;
                }
                else {
                    printf("Login first\n");
                }
            }
            else if(in == 4) {
                return 3;
            }
            else{
                InvalidInput();
            }
        }while(1);
    }while(quit != 1);

    return accntType;
}


int AccntSearch (char username[50], char password[100]) {

    FILE *filePointer;
    char ptrUsername[50], ptrPassword[100];
    int ptrAccntType;

    filePointer = fopen("users.txt", "r");
    if(!filePointer) {
        printf("\nNo user file detected");
    }
    else {
        while(!feof(filePointer)) {
            fscanf(filePointer, "%s", &ptrUsername);
            if(strcmp(ptrUsername, username)==0) {
                fscanf(filePointer, "%s", &ptrPassword);
                if(strcmp(ptrPassword, password)==0) {
                    fscanf(filePointer, "%d", &ptrAccntType);
                    return ptrAccntType;
                }
            }
        }
    }

    fclose(filePointer);

    return 3;
}


int CreateAccount () {

    char username[50], password[100], tempPassword[100];
    int accntType, in;
    FILE *filePointer;

    do {
        system("cls");
        printf("\nEnter username for the new Account (0 to exit): ");
        scanf("%s", username);
        if(strcmp(username, "0")==0) {
            break;
        }
        system("cls");
        printf("\nEnter password (0 to exit): ");
        scanf("%s", password);
        if(strcmp(password, "0")==0) {
            break;
        }
        system("cls");
        printf("\nConfirm password (0 to exit): ");
        scanf("%s", tempPassword);
        if(strcmp(tempPassword, "0")==0) {
            break;
        }

        if(strcmp(password, tempPassword) != 0) {
            printf("\nPasswords do not match, try again");
            getch();
        }
        else {
            system("cls");
            printf("\nSelect Account Type for the new account\n\n1. Admin\n2. Normal\n\n3. Cancel\n");
            do {
                printf("\n>");
                scanf("%d", &accntType);
                if(accntType == 1 || accntType == 2) {
                    system("cls");
                    printf("\nConfirm creation of account %s\n\n1. Confirm\n2. Cancel\n\n>", username);
                    scanf("%d", &in);
                    if(in == 1) {
                        filePointer = fopen("users.txt", "a");
                        fprintf(filePointer, "%s %s %d\n", username, password, accntType);
                        fclose(filePointer);
                    }
                    return 0;
                }
                else if(accntType == 2) {
                    return 0;
                }
                else {
                    InvalidInput();
                }
            } while(1);
        }
    } while(1);

    return 0;
}
