#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int NewTicket(char [][20], int, char [][20]);
int Settings(char [][20], int*, int*);
int Records(char [][20], char [][20]);
int VehicalSelection(char [][20]);
int CheckpointSelection(char [][20], int, char [20]);
int PriceCalculate(int, int);
int Credits();
int ChangeSavePath(char [50], int);
int LoginScreen();

float Distance(int, int);

void InvalidInput();
void WriteToFile(FILE*, int, int, int);
void Display(int, char[][20], int, int, char[][20], int, float);

int issueNo = 1;

char logSavePath[100] = "./logs.txt";
char issueSavePath[100] = "./issue.txt";

int main() {

    char checkpoints[][20] = {"Kottawa", "Kahathuduwa", "Gelanigama", "Dodangoda", "Welipanna",
                              "Kurundugahahetekma", "Baddegama", "Pinnaduwa", "Imaduwa", "Kokmaduwa",
                              "Godagama", "<None>"}; //Stores all the Checkpoints available
    char vehicalTypes[][20] = {"Car", "Jeep", "Station Wagon", "Cab", "Van", "Truck", "<None>"};



    int currentCheck = 11,
        quit = 0, //controls the main program loop
        in = 0; //stores temporary integer type user inputs inside Main function scope

    static int accntType;

    accntType = LoginScreen();
    if(accntType == 3) {
        return 0;
    }

    do { //main program loop
        system("cls"); //clear screen
        printf("\n######## Welcome to Kottawa-Matara Highway Program ########\n");
        printf("\n### Main Menu ###\n\n");
        printf("Checkpoint : %s\n\n",checkpoints[currentCheck]); //Displays the current selected checkpoint
        printf("1. New Ticket\n");
        printf("2. Counter\n");
        printf("3. Records\n");
        printf("4. Settings\n");
        printf("5. Exit\n\n>");

        do {
            scanf("%d",&in); //takes user input to start program, go to Settings or exit
            switch (in) {
                case 1 : {
                    if(currentCheck == 11) {
                        printf("Current checkpoint must be assigned from Settings");
                        getch();
                    }
                    else {
                        NewTicket(checkpoints, currentCheck, vehicalTypes);
                    }
                    break;
                }
                case 2 : Counter(checkpoints);break;
                case 3 : Records(checkpoints, vehicalTypes);break;
                case 4 : Settings(checkpoints, &currentCheck, &accntType);break;
                case 5 : quit = Credits();break;
                default : InvalidInput();
            }
        break;
        } while (1);
    } while (quit!=1);

    return 0;
}

int NewTicket(char checkpoints[][20], int currentCheck, char vehicalTypes[][20]) {

    int quit = 0,
        in = 0,
        destination = 11,
        vehicalType = 6,
        ticketPrice;

    float distance = 0;

    FILE *filePointer;

    filePointer = fopen(issueSavePath, "r");
    if(filePointer != NULL) {
        fscanf(filePointer, "%d",&issueNo);
        issueNo++;
    }
    fclose(filePointer);

    do {
        system("cls");
        printf("\n### New Ticket ###\n\n");
        printf("Issue No : %d\n",issueNo);
        printf("Checkpoint : %s\n\n",checkpoints[currentCheck]);
        printf("Destination set to : %s\n",checkpoints[destination]);
        printf("Vehicle type set to : %s\n\n",vehicalTypes[vehicalType]);
        if(currentCheck == 11) {
            printf("Please set Checkpoint from Main menu\n");
        }
        if(destination == 11) {
            printf("Please set destination\n");
        }
        if(vehicalType == 6) {
            printf("Please select vehicle type\n");
        }
        printf("\n1. Select Destination\n");
        printf("2. Select Vehicle type\n");
        printf("3. Confirm\n");
        printf("4. Main menu\n");

        do {
            printf("\n>");
            scanf("%d",&in);

            if(in == 1){
                destination = CheckpointSelection(checkpoints, currentCheck, "Destination");
                break;
            }
            else if(in == 2) {
                vehicalType = VehicalSelection(vehicalTypes);
                break;
            }
            else if(in == 3) {
                if(destination != 11 && vehicalType != 6 && currentCheck != 11) {
                    ticketPrice = PriceCalculate(currentCheck, destination);
                    distance = Distance(currentCheck, destination);
                    Display(ticketPrice, checkpoints, currentCheck, destination, vehicalTypes, vehicalType, distance);
                    WriteToFile(filePointer, currentCheck, destination, vehicalType);
                    issueNo++;
                    break;
                }
                else {
                    printf("Set the required information mentioned above to continue\n");
                }
            }
            else if(in == 4) {
                quit = 1;
                break;
            }
            else {
                InvalidInput();
            }
        } while (1);
    } while (quit != 1);


    return 0;
}


int Records(char checkpoints[][20], char vehicalTypes[][20]) {

    FILE *filePointer;
    int x, c=1, in, issue;
    char d[10];

    if(recFileCheck("Records")==1)
        return 0;

    do {
        system("cls");
        printf("\n### Records ###\n\n");
        printf("1. Display all\n");
        printf("2. Search\n");
        printf("3. Main menu\n");

        do {
                printf("\n>");
                scanf("%d", &in);

                if(in == 1) {
                    system("cls");
                    printf("\n### Records ###\n\n");
                    filePointer = fopen(logSavePath, "r");
                    while(1) {
                        if(fscanf(filePointer, "%*s%d", &x) == EOF) {
                            break;
                        }
                        printf("%d.\tIssue No : %d\t\t\t", c, x);

                        fscanf(filePointer, "%d", &x);
                        printf("Entry Time : %d-", x);
                        fscanf(filePointer, "%d", &x);
                        printf("%d-", x);
                        fscanf(filePointer, "%d", &x);
                        printf("%d ", x);
                        fscanf(filePointer, "%d", &x);
                        printf("%d:", x);
                        fscanf(filePointer, "%d", &x);
                        printf("%d:", x);
                        fscanf(filePointer, "%d", &x);
                        printf("%d\n", x);

                        fscanf(filePointer, "%d", &x);
                        printf("\tEntry Checkpoint : %s\t", checkpoints[x]);

                        fscanf(filePointer, "%d", &x);
                        printf("Exit Checkpoint : %s\n", checkpoints[x]);

                        fscanf(filePointer, "%d", &x);
                        printf("\tVehicle Type : %s\n\n", vehicalTypes[x]);

                        c++;
                    }
                    fclose(filePointer);
                    printf("Press any key...");
                    getch();
                    break;
                }
                else if(in == 2) {
                    filePointer = fopen(logSavePath, "r");
                    system("cls");
                    printf("\n### Records ###\n\n");
                    printf("Enter issue number : ");
                    scanf("%d", &issue);

                    while(!feof(filePointer)) {
                        fscanf(filePointer, "%s", d);
                        if(strcmp(d, "issue")==0) {
                            fscanf(filePointer, "%d", &x);
                            if(x == issue) {
                                system("cls");

                                printf("\n\nIssue No : %d\t\t\t", x);
                                fscanf(filePointer, "%d", &x);
                                printf("Entry Time : %d-", x);
                                fscanf(filePointer, "%d", &x);
                                printf("%d-", x);
                                fscanf(filePointer, "%d", &x);
                                printf("%d ", x);
                                fscanf(filePointer, "%d", &x);
                                printf("%d:", x);
                                fscanf(filePointer, "%d", &x);
                                printf("%d:", x);
                                fscanf(filePointer, "%d", &x);
                                printf("%d\n", x);

                                fscanf(filePointer, "%d", &x);
                                printf("Entry Checkpoint : %s\t", checkpoints[x]);

                                fscanf(filePointer, "%d", &x);
                                printf("Exit Checkpoint : %s\n", checkpoints[x]);

                                fscanf(filePointer, "%d", &x);
                                printf("Vehicle Type : %s\n\n", vehicalTypes[x]);

                                fclose(filePointer);
                                printf("Press any key...");
                                getch();
                                break;
                            }
                        }
                    }
                    if(feof(filePointer)) {
                        system("cls");
                        printf("\nNo entry found with issue number : %d", issue);
                        getch();
                    }
                    fclose(filePointer);
                    break;
                }
                else if(in == 3) {
                    return 0;
                }
                else {
                    InvalidInput();
                }
            } while(1);
        } while(1);

        return 0;
}


int Settings(char checkpoints[][20], int *currentCheck, int *accntType) { //Settings function

    int in = 0, //stores temporary integer type user inputs inside Settings function scope
        quit = 0; //display message if Checkpoint setting is changed

    do {
        system("cls");
        printf("\n### Settings ###\n\n");
        printf("1. Change Checkpoint\n");
        printf("2. Change Log file save location\n");
        printf("3. Change Issue Number file save location\n");
        printf("4. Change User\n");
        printf("5. Main menu\n");
        printf("\nCheckpoint set to : %s",checkpoints[*currentCheck]);
        printf("\nLog file path set to : %s", logSavePath);
        printf("\nIssue file path set to : %s\n", issueSavePath);

        do { //loop to option menu and invalid inputs
            printf("\n>");
            scanf("%d",&in); //user input for Change checkpoint or go back to main menu
            if(in == 1){ //change checkpoint if 1 is entered
                *currentCheck = CheckpointSelection(checkpoints, &currentCheck, "Checkpoint");
                break;
            }
            else if(in == 2) {
                if(*accntType == 0 || *accntType == 1) {
                    ChangeSavePath("logs.txt", 2);
                    break;
                }
                else {
                    printf("Insufficient user privilege\n");
                }
            }
            else if(in == 3) {
                if(*accntType == 0 || *accntType == 1) {
                    ChangeSavePath("issue.txt", 3);
                    break;
                }
                else {
                    printf("Insufficient user privilege\n");
                }

            }
            else if(in == 4) {
                *accntType = LoginScreen();
                break;
            }
            else if(in == 5) { //back to Main menu
                quit = 1; //exit option menu loop
                break;
            }
            else { //print error for invalid input and repeat
                InvalidInput();
            }
        } while (1);
    } while (quit != 1);

    return 0;
}


void InvalidInput () {
    while(getchar() != '\n');
    printf("Invalid input, try again.\n");
}

int PriceCalculate(int currentCheck, int destination) {

    int startingPrice = 100,
        additionalPrice = 50,
        additionalCheck,
        ticketPrice;

    if (currentCheck > destination) {
        additionalCheck = (currentCheck - destination)-1;
    }
    else {
        additionalCheck = (destination - currentCheck)-1;
    }

    ticketPrice = startingPrice + (additionalCheck * additionalPrice);

    return ticketPrice;
}


void Display(int ticketPrice, char checkpoints[][20], int currentCheck, int destination, char vehicalTypes[][20], int vehicalType, float distance) {

    time_t t= time(NULL);
    struct tm tm = *localtime(&t);

    system("cls");
    printf("############################################################################\n#\n");
    printf("#\t\tWELCOME TO KOTTAWA-MATARA EXPRESSWAY\n#\n");
    printf("#\tIssue No : %d\t\t\tEntry : %d-%d-%d %d:%d:%d\n#\n", issueNo, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("#\tCheckpoint : %s\t\tDestination : %s\n#\n", checkpoints[currentCheck], checkpoints[destination]);
    printf("#\tDistance : %.2fkm\n", distance);
    printf("#\tTicket Price : Rs.%d\n#\n", ticketPrice);
    printf("#\t\tHave a safe travel and Come again!\n#\n");
    printf("############################################################################");
    getch();
}


float Distance(int currentCheck, int destination) {

    float checkpointsDist[11] = {0.0,5.9,13.7,34.8,46,67.6,79.8,95.3,108,116.5,127};
    float distance;

    if(currentCheck > destination) {
        distance = checkpointsDist[currentCheck] - checkpointsDist[destination];
    }
    else
        distance = checkpointsDist[destination] - checkpointsDist[currentCheck];

    return distance;
}


int CheckpointSelection (char checkpoints[][20], int currentCheck, char message[20]) {

    int in,
        c,
        checkpoint = currentCheck;

    printf("\n\tSet %s : \n", message);

    for (c = 0;c<11;c++) { //prints all available Checkpoints from the checkpoint array
        if(c == currentCheck) {
            continue;
        }
        printf("\n\t%d. %s",c+1,checkpoints[c]);
    }
    printf("\n\n\t0. Back");

    do {
        printf("\n\n\t>");
        scanf("%d",&in);

        if(in == 0) {
            break;
        }
        else if(in-1 == currentCheck) {
            printf("\tInvalid input, try again.");
        }
        else if(in > 0 && in < 12) {
            checkpoint = in-1;
            break;
        }
        else {
            printf("\tInvalid input, try again.");
        }
    } while (1);

    return checkpoint;
}


int VehicalSelection(char vehicalTypes[][20]) {

    int in,
        c,
        vehicalType;

    printf("\n\tSet Vehicle type : \n");
    for (c = 0;c<6;c++) { //prints all available Checkpoints from the checkpoint array
        printf("\n\t%d. %s",c+1,vehicalTypes[c]);
    }

    do {
        printf("\n\n\t>");
        scanf("%d",&in);

        if(in > 0 && in < 7) {
            vehicalType = in-1;
            break;
        }
        else {
            printf("\tInvalid input, try again.");
        }
    } while (1);

    return vehicalType;
}


void WriteToFile(FILE *filePointer, int currentCheck, int destination, int vehicalType) {

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    filePointer = fopen(logSavePath, "a");
    fprintf(filePointer, "issue %d ",issueNo);
    fprintf(filePointer, "%d %d %d %d %d %d ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(filePointer, "%d ",currentCheck);
    fprintf(filePointer, "%d ",destination);
    fprintf(filePointer, "%d ",vehicalType);
    fclose(filePointer);

    filePointer = fopen(issueSavePath, "w");
    fprintf(filePointer, "%d",issueNo);
    fclose(filePointer);
}


int Credits() {

    int in;

    system("cls");
    printf("\n\n\n\t\t#########################################################\n\t\t#\t\t\t\t\t\t\t#\n");
    printf("\t\t#\t\t\t17.1 GROUP 2\t\t\t#\n\t\t#\t\t\t\t\t\t\t#\n");
    printf("\t\t#\t\t1. Dunura Dulshan\t\t\t#\n");
    printf("\t\t#\t\t2. Jithma Gamage\t\t\t#\n");
    printf("\t\t#\t\t3. Salman Faris\t\t\t\t#\n");
    printf("\t\t#\t\t4. Ranuka Dilshan\t\t\t#\n");
    printf("\t\t#\t\t5. Dulmin Gunerathne\t\t\t#\n");
    printf("\t\t#\t\t6. Dulana Dias\t\t\t\t#\n");
    printf("\t\t#\t\t7. Fayas Faris\t\t\t\t#\n");
    printf("\t\t#\t\t8. Malik Eranda\t\t\t\t#\n\t\t#\t\t\t\t\t\t\t#\n");
    printf("\t\t#########################################################\n\n");

    printf("Press 0 to go back to program or any other to exit\n\n>");
    scanf("%d", &in);
    if(in != 0) {
        in = 1;
    }

    return in;
}


int ChangeSavePath(char fileName[50], int operation) {

    system("cls");

    char in[100];
    FILE *filePointer;

    printf("\n### Change %s Path ###\n\n", fileName);

    if(operation == 2) {
        printf("Current %s save path : %s\n", fileName, logSavePath);
        printf("Make sure to enter file name(%s) after the directory path. i.e: /path/path/%s\n\n", fileName, fileName);
        printf("0. Back\n\n");
        printf("Enter new path for %s\n\n>", fileName);
        scanf("%s", &in);

        if(!strcmp(in, "0")) {
            return 0;
        }
        else {
            strcpy(logSavePath, in);
        }
    }
    else if(operation == 3) {
        printf("Current %s save path : %s\n", fileName, issueSavePath);
        printf("Make sure to enter file name(%s) after the directory path. i.e: /path/path/s\n\n", fileName, fileName);
        printf("0. Back\n\n");
        printf("Enter new path for %s\n\n>", fileName);
        scanf("%s", &in);

        if(!strcmp(in, "0")) {
            return 0;
        }
        else {
            strcpy(issueSavePath, in);
        }

        filePointer = fopen(issueSavePath, "w");
        fprintf(filePointer, "%d",issueNo-1);
        fclose(filePointer);
    }

    return 0;
}


int Counter(char checkpoints[][20]) {

    int in, issue, x, currentCheck, destination;
    float distance, avgSpeed, fine = 2000;
    char d[10];
    time_t entryTime, exitTime;
    double timeTaken;
    struct tm tm = {0};
    FILE *filePointer;

    if(recFileCheck("Counter")==1)
        return 0;

    exitTime = time(NULL);

    system("cls");
    printf("\n### Counter ###\n\n");
    printf("Enter issue number : ");
    scanf("%d", &issue);

    filePointer = fopen(logSavePath, "r");
    while(!feof(filePointer)) {
        fscanf(filePointer, "%s", d);
        if(strcmp(d, "issue")==0) {
            fscanf(filePointer, "%d", &x);
            if(x == issue) {
                system("cls");
                printf("\n\nIssue No : %d\t\t\t", x);

                fscanf(filePointer, "%d", &tm.tm_year);
                printf("Entry Time : %d-", tm.tm_year);
                fscanf(filePointer, "%d", &tm.tm_mon);
                printf("%d-", tm.tm_mon);
                fscanf(filePointer, "%d", &tm.tm_mday);
                printf("%d ", tm.tm_mday);
                fscanf(filePointer, "%d", &tm.tm_hour);
                printf("%d:", tm.tm_hour);
                fscanf(filePointer, "%d", &tm.tm_min);
                printf("%d:", tm.tm_min);
                fscanf(filePointer, "%d", &tm.tm_sec);
                printf("%d\n", tm.tm_sec);

                fscanf(filePointer, "%d", &currentCheck);
                printf("Entry Checkpoint : %s\t", checkpoints[currentCheck]);

                fscanf(filePointer, "%d", &destination);
                printf("Exit Checkpoint : %s\n", checkpoints[destination]);

                printf("Confirm ticket (Yes=1, No=0) : ");
                scanf("%d", &in);

                if(in == 1) {
                    tm.tm_year -= 1900;
                    tm.tm_mon -= 1;

                    timeTaken = difftime(exitTime, mktime(&tm));
                    distance = Distance(currentCheck, destination);
                    avgSpeed = distance/((timeTaken/60)/60);
                    printf("\nAverage speed = %.2fkmph", avgSpeed);
                    if(avgSpeed > 120) {
                        fine += (avgSpeed - 120) * 10;
                        printf("\nHigh Speed fine issued Rs.%.2f", fine);
                    }
                    getch();
                    break;
                }
            }
        }
    }
    if(feof(filePointer)) {
        system("cls");
        printf("\nNo entry found with issue number : %d", issue);
        getch();
    }
    fclose(filePointer);
}

int recFileCheck(char operation[50]) {
    FILE *filePointer;

    filePointer = fopen(logSavePath, "r");
    if(!filePointer) {
        system("cls");
        printf("\n### %s ###\n", operation);
        printf("\nError : Couldn't find record file");
        printf("\nIf the files are not in default directory, change directories from settings");
        fclose(filePointer);
        getch();
        return 1;
    }
}
