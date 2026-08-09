#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"




void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//Function prototype
int is_alpha(char*);
int is_digit(char*);
int is_ID(char*);
int count_num(char*);

void createContact(AddressBook *addressBook)
{
    int flag = 0;
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
        printf("Address Book is Full...\n");
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

int is_digit(char *p)
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

int is_ID(char *p)
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