/**
 * @file main.c
 * @author Rados Mirkovic (you@domain.com)
 * @brief Personal Diary writen in C
 * @version 0.1
 * @date 2021-12-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */



#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>

int password();
void addRecord();
void viewRecord();
void editRecord();
void editPassword();
void deleteRecord();

struct Record{
    char time[6];
    char name[30];
    char place[25];
    char duration[10];
    char note[500];
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}


void addRecord()
{
    system("CLS");
    FILE *fp;
    char another = 'Y', time[10];
    struct Record record;
    char fileName[15];
    int choice;
    printf("\n\n\t\t*********************");
    printf("\t\t *WELCOME TO THE ADD MENU*");
    printf("\n\n\t\t*********************");
    printf("\n\n\tENTER DATE OF YOUR RECORD:[yyyy-mm-dd]");
    fflush(stdin);
    fgets(fileName, 15, stdin);
    fp = fopen(fileName, "ab+");
    if(fp == NULL)
    {
        fp = fopen(fileName, "wb+");
        if(fp == NULL)
        {
            printf("\nSystem error...");
            printf("\nPress any key to exit");
            getch();
            return;
        }
    }

    while(another == 'Y' || another == 'y')
    {
        choice = 0;
        fflush(stdin);
        printf("\n\tEnter time:[hh:mm]:");
        fscanf(fp, "%s", time);
        rewind(fp);

        while(fread(fp, &record, sizeof(record), 1) == 1)
        {
            if(strcmp(record.time, time) == 0)
            {
                printf("\n\tThe record already exist");
                choice  = 1;
            }
        }

        if(choice == 0)
        {
            strcmp(record.time, time);
            printf("\tEnter name:");
            fflush(stdin);
            fgets(record.name, 30, stdin);
            fflush(stdin);
            printf("\tEnter place:");
            fgets(record.place, 25, stdin);
            fflush(stdin);
            printf("\tEnter duration:");
            fgets(record.duration, 10, stdin);
            fflush(stdin);
            printf("\tEnter note:");
            fgets(record.note, 500, stdin);
            fwrite(&record, sizeof(record), 1, fp);
            printf("\nYour record is added...");
        }
        printf("\n\tAdd another record:(Y / N)");
        fflush(stdin);
        another = getchar();
    }

    fclose(fp);
    pritnf("\n\tPress any key to exit...");
    getch();

}

void viewRecord()
{
    FILE *fpt;
    system("CLS");
    struct Record customer;
    char time[6], choice, fileName[14];
    int ch;
    printf("\n\t**************************");
    printf("\t\t *HERE IS THE VIEWING MENU*");
    printf("\n\t**************************");
    choice = password();
    if(choice != 0)
    {
        return;
    }
    do
    {
        printf("\t\tENTER THE DATE OF RECORD TO BE VIEWED:[yyyy-mm-dd]");
        fflush(stdin);
        fgets(fileName, 14, stdin);
        fpt = fopen(fileName, "rb+");
        if(fpt == NULL)
        {
            printf("\nRecord doesn`t exists....");
            printf("Press any key to exit");
            getch();
            return;
        }
        system("CLS");
        printf("\n\tHow would you like to view?");
        printf("\n\t1.The whole record of the day.");
        printf("\n\t2.Record of fixed time.");
        printf("\n\t\tEnter your choice:");
        fscanf(fpt, "%s", &ch);
        switch(ch)
        {
            case 1:
            printf("\nPrint the whole record for %s is:", fileName);
            while(fread(&customer, sizeof(customer), 1, fpt) == 1)
            {
                printf("\n");
                printf("\nTIME:%s", customer.time);
                printf("\nMeting with:%s", customer.name);
                printf("\nMeeting at:%s", customer.place);
                printf("\nDuration:%s", customer.duration);
                printf("\nNote:%s", customer.note);
                printf("\n");
            }
            break;

            case 2:
            fflush(stdin);
            printf("\nEnter time:[hh:mm]:");
            fgets(fpt, 6, time);
            while(fread(&customer, sizeof(customer), 1, fpt) == 1)
            {
                if(strcmp(customer.time, time) == 0)
                {
                    printf("\nYour record is:");
                    printf("\nTime:%s", customer.time);
                    printf("\nMeeting with:%s", customer.name);
                    printf("\nMeeting at:%s", customer.place);
                    printf("\nDuration:%s", customer.duration);
                    printf("\nNote:%s", customer.note);
                }
            }
            break;

            default:
            printf("\n\nYou typed something else...");
            fflush(stdin);
            fscanf(fpt, "%c", choice);
        }
    }while(choice == 'y' || choice == 'Y');

    fclose(fpt);

    return;
}

        
void editRecord()
{
    system("CLS");
    FILE *fpt;
    struct Record customer;
    char time[6], choice, fileName[14];
    int num, count = 0;
    printf("\n\t******************************");
    printf("\n\t*WELCOME TO THE EDITING MENU*");
    printf("\n\t******************************");
    choice = password;
    if(choice != 0)
    {
        return;
    }

    do{
        printf("\n\tENTER THE DATE OF RECORD TO BE EDITED:[yyyy-mm-dd]:");
        fflush(stdin);
        fgets(fileName, 14, stdin);
        printf("\n\tEnter time:[hh:mm]:");
        fgets(time, 6, stdin);
        fpt = fopen(fileName, "rb+");
        if(fpt == NULL)
        {
            printf("\n\tRecord doesn`t exist...");
            printf("\\n\tPress any key to go back");
            getch();
            return;
        }
        while(fread(&customer, sizeof(customer), 1, fpt) == 1)
        {
            if(strcmp(customer.time, time) == 0)
            {
                printf("\nYour old record was:");
                printf("\nTime:%s", customer.time);
                printf("\nMeeting with:%s", customer.name);
                printf("\nMeeting at:%s", customer.place);
                printf("\nDuration:%s", customer.duration);
                printf("\nNote:%s", customer.note);
                printf("\nWhat would you like to edit?");
                printf("\n1.Time");
                printf("\n2.Meeting with");
                printf("\n3.Meeting place");
                printf("\n4.Duration");
                printf("\n5.Note");
                printf("\n6.Whole record");
                printf("\n7.Back to the main menu");

                do{
                    printf("\nEnter choice");
                    fflush(stdin); //za output streams writes unwritten data from streams buffer to the device
                    scanf("%d", &num);
                    fflush(stdin);
                    switch(num)
                    {
                        case 1:
                        printf("\nEnter the new data");
                        printf("\nNew time:[hh:mm]:");
                        fgets(customer.time, 6, fpt);
                        break;

                        case 2:
                        printf("\nEnter the new data");
                        printf("\nNew meeting person");
                        fgets(customer.name, 10, fpt);
                        break;

                        case 3:
                        printf("\nEnter new data");
                        printf("\nNew meeting place");
                        fgets(customer.place, 10, fpt);
                        break;

                        case 4:
                        printf("\nEnter new data");
                        printf("\nDuration");
                        fgets(customer.duration, 10, fpt);
                        break;

                        case 5:
                        printf("\nEnter new data");
                        printf("\nNote");
                        fgets(customer.note, 10, fpt);
                        break;

                        case 6:
                        printf("\nEnter new data");
                        printf("\nNew time:[hh:mm]:");
                        fgets(customer.time, 6, fpt);
                        printf("\nNew meeting person");
                        fgets(customer.name, 10, fpt);
                        printf("\nNew meeting place");
                        fgest(customer.place, 10, fpt);
                        printf("New duration");
                        fgets(customer.duration, 10, fpt);
                        printf("\nNew note");
                        fgets(customer.note, 10, fpt);
                        break;

                        case 7:
                        printf("\nPress any key to go back...");
                        getch();
                        return;
                        break;

                        default:
                        printf("\nYou typed something else. Try again");
                        break;
                    }
                }
                while(num < 1 || num > 8);
                fseek(fpt, -sizeof(customer), SEEK_CUR);
                fwrite(&customer, sizeof(customer), 1, fpt);
                fseek(fpt, -sizeof(customer), SEEK_CUR);
                fwrite(&customer, sizeof(customer), 1, fpt);
                choice = 5;
                break;
            }
        }
        if(choice == 5)
        {
            system("CLS");
            printf("\n\nEditing completed");
            printf("----------------------------");
            printf("The new record is");
            printf("----------------------------");
            printf("\nTime:%s", customer.time);
            printf("\nMeeting with:%s", customer.name);
            printf("\nMeeting at:%s", customer.place);
            printf("\nDuration:%s", customer.duration);
            printf("\nNote:%s", customer.note);
            fclose(fpt);
            printf("\nWould you like to edit another record?(Y / N)");
            fscanf("%c", &choice);
            count++;
        }else{
            printf("\nThe record doesn`t exist");
            printf("\nWould you like to try again?");
            fscanf("%c", &choice);
        }

    }while(choice == 'Y' || choice == 'y');

    if(count == 1)
    {
        printf("\n%d file is edited", count);
    }
    else if(count > 1)
    {
        printf("\n%d files are edited", count);
    }else{
        printf("\nNo files edited...");
    }
    printf("\nPress enter to exit editing menu");
    getch();

}

int password()
{
    char pass[15] = {0}, check[15] = {0}, ch;
    FILE *fpass;
    int i = 0, j;
    printf("::For secutiry purposes::");
    printf("::Only 3 trials are alowed::");
    for(j = 0; j < 3; j++)
    {
        i = 0;
        printf("\nEnter password:");
        pass[i] = getch();
        if(pass[i] != '\r') //carriage return, nothing special
        {
            if(pass[i] != '\b') //backspace, cursor shift backward
            {
                i--;
                printf("\b");
                printf(" ");
                printf("\b");
                pass[i] = getch();
            }else{
                printf("*");
                i++;
                pass[i] = getch();
            }
        }
        pass[i] = '\0'; //null termination, termination of character string
        fpass = fopen("Password", "r");
        if(fpass == NULL)
        {
            printf("\nError with system file...[File missing]\n");
            getch();
            return 1; //user defined function returns false-error
        }else{
            i = 0; //int kao boolean:1 true, 0 false
        }

        while(1)
        {
            ch = fgetc(fpass);
            if(ch == EOF)
            {
                check[i] = '\0';
                break;
            }
            check[i] = ch - 5;
            i++;
        }

        if(strcmp(pass, check) == 0)
        {
            printf("\nAccess granted");
            return 0;
        }else{
            printf("\nWrong password");
        }
    }

    printf("\nYou entered wrong passwod");
    printf("\nPress any key to go back");
    getch();

    return 1;
}
            

void editPassword()
{
    system("CLS");
    printf("\n");
    char pass[15] = {0}, confirm[15] = {0}, ch;
    int choice, i, check;
    FILE *editpass;
    editpass = fopen("Password", "rb");
    if(editpass == NULL)
    {
        editpass = fopen("Password", "wb");
        if(editPassword == NULL)
        {
            printf("\nSystem error. File doesn`t exist...");
            getch();
            return; 
        }

        fclose(editpass);
        printf("\nPres 'Enter' to change password");
        getch();
    }
    //close stream
    fclose(editpass);

    //check if passwords match
    check = password();
    if(check == 1) //int as boolean; in main 0 = true, 1 = false; user defined functions:0 = false, 1 = true
    {
        return;
    }
    do{
        if(check == 0)
        {
            i = 0;
            choice = 0;
            printf("\nEnter the new password:");
            fflush(stdin);
            pass[0] = getch();
            while(pass[i] != '\r')
            {
                if(pass[i] == '\b')
                {
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    pass[i] = getch();
                }
                else{
                    printf("*");
                    i++;
                    pass[i] = getch();
                }
            }
            pass[i] = '\0';
            i = 0;
            printf("\nConfirm password");
            confirm[0] = getch();
            while(confirm[i] != '\r')
            {
                if(confirm[i] == '\b')
                {
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    confirm[i] = getch();
                }
                else{
                    printf("*");
                    i++;
                    confirm[i] = getch();
                    

                }
            }
            confirm[i] = '\0';
            if(strcmp(pass, confirm) == 0)
            {
                editpass = fopen("Password", "wb");
                if(editpass == NULL)
                {
                    printf("\nSystem error");
                    getch();
                    return; //like break statement
                }
                i = 0;

                while(pass[i] != '\0')
                {
                    ch = pass[i];
                    putc(ch + 5, editpass);
                    i++;
                }
                putc(EOF, editpass);
                fclose(editpass);
            }else{
                printf("\nThe new password doesn`t match");
                choice = 1;
            }

        }
    }while(choice == 1);
    printf("\nPassword changed. Press any key to go back");
    getch();
            
}

void deleteRecord()
{

}
