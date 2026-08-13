#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    //Declaring file pointer
    FILE *fptr;
    fptr = fopen("contact.txt","w"); //File opening and Setting the mode

    //Validation
    if(fptr == NULL)
    {
        printf("File doesn't open\n");
        return;
    }
    printf("File opened successfully..\n");
    //Saves all contacts from addressBook to file
    for(int i = 0;i < addressBook -> contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
    }
    printf("All Contacts are stored Successfully!\n");
    fclose(fptr); //closing the file
}

void loadContactsFromFile(AddressBook *addressBook)
{
    //Declaring file pointer
    FILE *fptr;
    fptr = fopen("contact.txt","r"); //File opening and Setting the mode

    //Validation
    if(fptr == NULL)
    {
        printf("File doesn't open\n");
        return;
    }
    printf("File opened successfully..\n");
    //Saves all contacts from File to AddressBook
    while(addressBook -> contactCount < MAX_CONTACTS && (fscanf(fptr," %[^,],%[^,],%[^\n]", addressBook -> contacts[addressBook -> contactCount].name, addressBook -> contacts[addressBook -> contactCount].phone, addressBook -> contacts[addressBook -> contactCount].email) == 3) )
    {
        addressBook -> contactCount++;
    }
    printf("All Contacts are loaded  Successfully!\n");
    fclose(fptr); //closing the file
}
