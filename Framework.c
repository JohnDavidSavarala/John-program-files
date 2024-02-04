// CRUDS framework program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFIELDVALUELENGTH 20
#define MAXFIELDNAMELENGTH 100
#define MAXMENULENGTH 50
#define MAXMESSAGELENGTH 100
#define FIELDSFILE "Fields.cfg"
#define MENUFILE "Menu.cfg"
#define DATAFILE "Records.dat"
#define MESSAGESFILE "Messages.cfg"

FILE *fp_records, *fp_fields, *fp_menu, *fp_messages;
int choice;
char fieldValue[MAXFIELDVALUELENGTH], fieldName[MAXFIELDNAMELENGTH];
char **fieldNames, name[5], **messagesArray;
int countOfFields, countOfUserMessages;
char target_id[MAXFIELDVALUELENGTH], updateField[MAXFIELDVALUELENGTH], newFieldValue[MAXFIELDVALUELENGTH], message[MAXMESSAGELENGTH];

void showMenu();
char **getFieldsArray();
int getFieldsCount();
char **getRecordDetails();
void addRecord(char **, int userChoice);
void showAllRecords();
char *getTargetRecordId();
void updateRecord(char *,int userChoice);
void deleteRecord(char *, int userChoice);
void searchRecord(char *);
char *getId();
char *getNewFieldValue();
int getChoice();
void RecordNotFoundMessage(char *);
char **getMessages();
int getUserMessagesCount();

void main()
{
    fp_fields = fopen(FIELDSFILE, "r");
    fp_messages = fopen(MESSAGESFILE, "r");
    messagesArray = getMessages();
    countOfFields = getFieldsCount();
    countOfUserMessages = getUserMessagesCount();
    fieldNames = getFieldsArray();
    do
    {
        showMenu();
    } while (1);
}

void RecordNotFoundMessage(char *target_id)
{
    printf("%s%s\n", messagesArray[4], target_id);
}

int getUserMessagesCount()
{
    int messagesCounter = 0;

    while (fgets(message, sizeof(message), fp_messages) != NULL)
    {
        messageCounter++;
    }

    return messageCounter;   
}

int getFieldsCount()
{
    int fieldsCounter = 0;

    while (fgets(fieldName, sizeof(fieldName), fp_fields) != NULL)
    {
        fieldsCounter++;
    }

    return fieldsCounter;
}

int getChoice()
{
    printf("Enter your choice: ");
    scanf("%d", &choice);

    return(choice);
}


void showMenu()
{

    char Menu[MAXMENULENGTH];

    fp_fields = fopen(MENUFILE, "r");

    while (fgets(Menu, sizeof(Menu), fp_fields) != NULL)
    {
        printf("%s", Menu);
    }

    printf("\n");


    switch (getChoice())
    {
        case 1: addRecord(getRecordDetails());
                break;
        case 2: showAllRecords();
                break;
        case 3: updateRecord(getId());
                break;
        case 4: deleteRecord(getId());
                break;
        case 5: searchRecord(getId());
                break;
        case 0: printf("Thank you.\n");
                fclose(fp_fields);
                fclose(fp_messages);
                exit(0);
        default: printf("You entered an invalid choice.\n");
    }
}

char *getId()
{
    printf("Enter Id: ");
    scanf("%s", target_id);

    return(target_id);
}

char *getUpdateField()
{
    printf("Enter field name to be updated: ");
    scanf("%s", updateField);

    return(updateField);
}

char *getNewFieldValue()
{
    printf("Enter new field value: ");
    scanf("%s", newFieldValue);

    return(newFieldValue);
}

char** getFieldsArray()
{
    int fieldsCounter;

    rewind(fp_fields);
    
    fieldNames = (char **)malloc(countOfFields * sizeof(char *));
    
    for (fieldsCounter = 0; fieldsCounter < countOfFields; fieldsCounter++)
    {
        fieldNames[fieldsCounter] = malloc(MAXFIELDNAMELENGTH);
        fgets(fieldName, sizeof(fieldName), fp_fields);
        fieldName[strlen(fieldName) - 1] = '\0';
        strcpy(fieldNames[fieldsCounter], fieldName);
    }

    return fieldNames;
}

char** getRecordDetails()
{
    int counter;
    char **fieldValues = (char **)malloc(countOfFields * sizeof(char *));

    for (counter = 0; counter < countOfFields; counter++)
    {
        fieldValues[counter] = malloc(MAXFIELDVALUELENGTH);

        if (counter == 0)
        {
            strcpy(fieldValue, "A");
            strcpy(fieldValues[counter], fieldValue);
            continue;
        }

        printf("Enter %s: ", fieldNames[counter]);
        scanf("%s", fieldValues[counter]);
    }

    return fieldValues;
}

void addRecord(char **fieldValues, int userChoice)
{
    int counter;
    fp_records = fopen(DATAFILE, "a");

    for (counter = 0; counter < countOfFields; counter++)
    {
        strcpy(fieldValue, fieldValues[counter]);
        fwrite(fieldValue, sizeof(fieldValue), 1, fp_records);
    }

    fclose(fp_records);

    printf("%s%s\n", messagesArray[0], fieldValues[1]);
}

void showAllRecords()
{
    fp_records = fopen(DATAFILE, "r");
    int counter, count_of_records = 0;

    while(1)
    {
        fread(fieldValue, sizeof(fieldValue), 1, fp_records);
        
        if (strcmp(fieldValue, "A") == 0)
        {  
            for (counter = 0; counter < countOfFields; counter++)
            {
                if (counter != 0)
                {
                    fread(fieldValue, sizeof(fieldValue), 1, fp_records);
                    printf("%s: %s\n", fieldNames[counter], fieldValue);
                }
            }
            count_of_records++;   
        }

        if (feof(fp_records))
        {
            break;
        }
    }

    printf("%d%s.\n", count_of_records, messagesArray[1]);
    fclose(fp_records);
}

void updateRecord(char *target_id, int userChoice)
{
    fp_records = fopen(DATAFILE, "r+");

    int fieldsCount = 0, counter, isFound = 0, choice;

    while (fread(fieldValue, sizeof(fieldValue), 1, fp_records))
    {
        if (strcmp(fieldValue, target_id) == 0)
        {
            isFound = 1;

            for (counter = 2; counter < countOfFields; counter++)
            {
                printf("%d. %s\n", counter - 1, fieldNames[counter]);
            }
            choice = getChoice();

            strcpy(newFieldValue, getNewFieldValue());
            fseek(fp_records, sizeof(fieldValue) * (choice - 1), SEEK_CUR);
            strcpy(fieldValue, newFieldValue);
            fwrite(fieldValue, sizeof(fieldValue), 1, fp_records);
            fseek(fp_records, -sizeof(fieldValue) * (choice + 1), SEEK_CUR);
            fread(fieldValue, sizeof(fieldValue), 1, fp_records);
            // printf("Record with Id %s updated successfully.\n", fieldValue);
            // printf("hii.\n");
            printf("%s%s\n", messagesArray[userChoice - 2], target_id);
            fseek(fp_records, sizeof(fieldValue) * (choice - 1), SEEK_CUR);
            printf("Now the new %s is %s.\n", fieldNames[choice + 1], newFieldValue);

            break;
        }
    }

        
    if (isFound == 0)
    {
        RecordNotFoundMessage(target_id);
    }

    fclose(fp_records);
}

void deleteRecord(char *target_id, int userChoice)
{
    fp_records = fopen(DATAFILE, "r+");

    int isFound = 0;

    while (fread(fieldValue, sizeof(fieldValue), 1, fp_records))
    {
        if (strcmp(fieldValue, target_id) == 0)
        {
            isFound = 1;
            fseek(fp_records, -sizeof(fieldValue) * 2, SEEK_CUR);
            strcpy(fieldValue, "I");
            fwrite(fieldValue, sizeof(fieldValue), 1, fp_records);
            // fseek(fp_records, sizeof(fieldValue), SEEK_CUR);
            // fread(fieldValue, sizeof(fieldValue), 1, fp_records);
            // printf("Record with name %s deleted succesfully.\n", fieldValue);
            printf("%s%s\n", messagesArray[userChoice - 2], target_id);
            break;
        }
    }

    if (isFound == 0)
    {
        RecordNotFoundMessage(target_id);
    }

    fclose(fp_records);
}

void searchRecord(char *target_id)
{
    fp_records = fopen(DATAFILE, "r");
    int counter, isFound = 0;

    while (fread(fieldValue, sizeof(fieldValue), 1, fp_records))
    {
        if (strcmp(fieldValue, target_id) == 0)
        {
            isFound = 1;
            fseek(fp_records, -sizeof(fieldValue), SEEK_CUR);
            for (counter = 1; counter < countOfFields; counter++)
            {
                fread(fieldValue, sizeof(fieldValue), 1, fp_records);
                printf("%s: %s\n", fieldNames[counter], fieldValue);
            }
            break;
        }
    }

    if (isFound == 0)
    {
        RecordNotFoundMessage(target_id);
    }


    fclose(fp_records);
}

char **getMessages()
{
    int messageCounter;

    rewind(fp_messages);
    
    messagesArray = (char **)malloc(6 * sizeof(char *));
    
    for (messageCounter = 0; messageCounter < 6; messageCounter++)
    {
        messagesArray[messageCounter] = malloc(MAXMESSAGELENGTH);
        fgets(message, sizeof(message), fp_messages);
        messagesArray[strlen(message) - 1] = '\0';
        strcpy(messagesArray[messageCounter], message);
    }

    return messagesArray;
}

