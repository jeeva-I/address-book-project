#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

//Function prototype
int is_alpha(char*);
int is_digit(char*);
int is_ID(char*);
int count_num(char*);



void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    user_list: //goto label
      if(sortCriteria == 1) //for printing all name's
        {
            printf("        *=======================================*\n");
            printf("                        Name:-\n");
            for(int i = 0;i < addressBook -> contactCount; i++)
            {
                printf("%14d%15s\n", i+1, addressBook ->contacts[i].name);
            }
            printf("        *=========================================*\n");
        }
        else if(sortCriteria == 2) //For printing all mobile numbers 
        {
            printf("        *======================================*\n");
            printf("                    Phone.no:-\n");
            for(int i = 0;i < addressBook -> contactCount; i++)
            {
            printf("%14d%15s\n", i+1, addressBook ->contacts[i].phone);
            }
            printf("        *======================================*\n");
        }
        else if(sortCriteria == 3) //for printing all email id's
        {
            printf("    *======================================================*\n");
            printf("                          Email_ID:-\n");
            for(int i = 0;i < addressBook -> contactCount; i++)
            {
            printf("%18d%20s\n", i+1, addressBook ->contacts[i].email);
            }
            printf("     *======================================================*\n");
        }
        else
        {
            printf("Invalid Input, Try again...,\n");
            goto user_list; //using goto
        }

}
    

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    int flag = 0; //declaraing flag as zero 
	/* Define the logic to create a Contacts */
    if(addressBook -> contactCount < MAX_CONTACTS) //Checking the space is availabe to store the details
    {
        user_name:
            printf("Enter the Name: ");

            getchar();// for getting each character one by one
            fgets(addressBook -> contacts[addressBook -> contactCount].name, sizeof(addressBook -> contacts[addressBook -> contactCount].name), stdin); //Getting the name from the user
            addressBook -> contacts[addressBook -> contactCount].name[strcspn(addressBook -> contacts[addressBook -> contactCount].name, "\n")] = '\0'; //getting the newline index and assigning null
            //Function call
            flag = is_alpha(addressBook -> contacts[addressBook -> contactCount].name); 

            //checking the name valid or not
            if(flag)
            {
                printf("Invalid name, Enter again..."); //printing the error message
                goto user_name; //going to starting 
            }
        flag = 0;

        user_number:
            printf("Enter the Mobile Number: ");

            getchar(); //for getting each character one by one

            fgets(addressBook -> contacts[addressBook -> contactCount].phone, sizeof(addressBook -> contacts[addressBook -> contactCount].phone), stdin); //Getting the number from the user
            addressBook -> contacts[addressBook -> contactCount].phone[strcspn(addressBook -> contacts[addressBook -> contactCount].phone, "\n")] = '\0'; //getting the newline index and assigning null
            //Function call
            flag = count_num(addressBook -> contacts[addressBook -> contactCount].phone);

            //Checking validation
            if(flag)
            {
                printf("Invalid number, Enter again...\n"); //printing the error message
                goto user_number; //going to starting 
            }

            flag = 0;

            //Function call
            flag = is_digit(addressBook -> contacts[addressBook -> contactCount].phone); 

            //checking the name valid or not
            if(flag)
            {
                printf("Invalid number, Enter again...\n"); //printing the error message
                goto user_number; //going to starting 
            }

         flag = 0;

        user_Id:
            printf("Enter the Email ID: ");
            getchar(); //getting character one by one
            fgets(addressBook -> contacts[addressBook -> contactCount].email, sizeof(addressBook -> contacts[addressBook -> contactCount].email), stdin); //Getting the number from the user
            addressBook -> contacts[addressBook -> contactCount].email[strcspn(addressBook -> contacts[addressBook -> contactCount].email, "\n")] = '\0'; //getting the newline index and assigning null
            //Function call
            flag = is_ID(addressBook -> contacts[addressBook -> contactCount].email); 
            printf("\n"); //New line
            //checking the ID valid or not
            if(flag)
            {
                printf("Invalid Mail Id, Enter again...\n"); //printing the error message
                goto user_Id; //going to staring 
            }

        addressBook -> contactCount++;
        
    }
    else
    {
        printf("Address Book is Full...\n"); //printing the message
    }
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}

int is_alpha(char *p) //For checking the valid name or not
{
    while(*p != '\0') //validation
    {
        if((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z'))
        {
            p++;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

int is_digit(char *p) //For checking valid mobile number or not
{
    while(*p != '\0')
    {
        if(*p >= '0' && *p <= '9')
        {
            p++;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

int count_num(char *p) //Checking whether there are 10 numbers or not 
{
    int count = 1; //initialize count from zero to check the length
    while(*p != '\0')
    {
        p++;
        count++;
    }
    //Validation
    if(count != 10)
    {
        return 1;
    }

    return 0;
}

int is_ID(char *p) //For checking valid email id or not
{
    //Declaration 
    int at_count = 0;
    int dot_count = 0;

    while(*p != '\0') //Validation
    {
        if(*p == '@')
        {
            at_count++;
        }
        else if(*p == '.')
        {
            dot_count++;
        }
        p++;
    }

    if(at_count != 1 || dot_count != 1)
    {
        return 1;
    }

    return 0;
}