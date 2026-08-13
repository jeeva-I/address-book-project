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
        else if(sortCriteria == 4)
        {
            printf("                       ***************************************************************\n");
            printf("                       ---------------------------------------------------------------\n");
            printf("                                                 ADDRESS BOOK                        \n");
            printf("                       ---------------------------------------------------------------\n");
            printf("                       **************************************************************\n");
            for(int i = 0;i < addressBook -> contactCount; i++)
            {
                printf("                       --------------------------------------------------------------\n");
                printf("                       --------------------------------------------------------------\n");
                printf("                                  Name            Phoneno            email_Id\n");
                printf("%40s%19s%23s\n", addressBook -> contacts[i].name,  addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
            }
    
        }
        else
        {
            printf("Invalid Input, Try again...,\n");
            goto user_list; //using goto
        }

}
    

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
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

void searchContact(AddressBook *addressBook, int searchChoice) 
{
    /* Define the logic for search */

    user_searchcontact: //Adding label to return 
    //declaration of temporary veriables
    char temp[50];
    int flag = 0;
    if(searchChoice == 1) //Searching name in contacts
    {
        printf("Enter the name: ");
        getchar();
        fgets(temp,sizeof(temp),stdin); //Getting name from the user to search 
        temp[strcspn(temp,"\n")] = '\0'; //adding null by replacing \n

        //Function call to check the name is valid or nor
        flag = is_alpha(temp);
        
        if(flag)
        {
            printf("Invalid name, Enter again...,\n");
            goto user_searchcontact; //returning the pgm from top 
        }
        flag = 0;
        //Function call
        flag = search_name(addressBook, temp);

        //Validation for name
        if(flag == -1)
        {
            printf("No matches found, Try again!...\n"); //
            goto user_searchcontact;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("      Name            Phoneno            email_Id\n");
        printf("%12s%18s%23s\n", addressBook -> contacts[flag].name,  addressBook -> contacts[flag].phone, addressBook -> contacts[flag].email);
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
    }
    else if(searchChoice == 2)
    {
        printf("Enter the Mobileno: ");
        getchar();
        fgets(temp,sizeof(temp),stdin); //Getting name from the user to search 
        temp[strcspn(temp,"\n")] = '\0'; //adding null by replacing \n

        //Function call to check the name is valid or nor
        flag = is_digit(temp);
        
        if(flag)
        {
            printf("Invalid Number, Enter again...,\n");
            goto user_searchcontact; //returning the pgm from top 
        }
        flag = 0;
        //Function call
        flag = search_number(addressBook, temp);

        //Validation for name
        if(flag == -1)
        {
            printf("No matches found, Try again!...\n"); //
            goto user_searchcontact;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("      Name            Phoneno            email_Id\n");
        printf("%12s%18s%23s\n", addressBook -> contacts[flag].name,  addressBook -> contacts[flag].phone, addressBook -> contacts[flag].email);
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
    }
    else if(searchChoice == 3)
    {
        printf("Enter the Mail ID: ");
        getchar();
        fgets(temp,sizeof(temp),stdin); //Getting name from the user to search 
        temp[strcspn(temp,"\n")] = '\0'; //adding null by replacing \n

        //Function call to check the name is valid or nor
        flag = is_ID(temp);
        
        if(flag)
        {
            printf("Invalid Mail ID, Enter again...,\n");
            goto user_searchcontact; //returning the pgm from top 
        }
        flag = 0;
        //Function call
        flag = search_mail(addressBook, temp);

        //Validation for name
        if(flag == -1)
        {
            printf("No matches found, Try again!...\n"); //
            goto user_searchcontact;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("      Name            Phoneno            email_Id\n");
        printf("%12s%18s%23s\n", addressBook -> contacts[flag].name,  addressBook -> contacts[flag].phone, addressBook -> contacts[flag].email);
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
    }
    else if(searchChoice == 4) //for exit from search 
    {
        return;
    }
    else
    {
        printf("Enter the valid search choice!..."); //printing the error msg
        goto user_searchcontact; //returning to top of search contact  
    }

}

void editContact(AddressBook *addressBook, int e_searchChoice)
{
    user_editcontact:
	/* Define the logic for Editcontact */
     char var[50]; //Declaring temporary variable
     int flag = 0;
     int index;
     //search function
     if(e_searchChoice == 1)
     {   
        user_esearch_name:
         printf("Enter the Name to edit: ");
         getchar();
         fgets(var,sizeof(var),stdin); //Getting input from the user
         var[strcspn(var,"\n")] = '\0'; 

         flag = is_alpha(var); // function call 
         //for name validation
         if(flag)
         {
            printf("Invalid name, Try again...\n");
            goto user_esearch_name;
         }
         //function call
        index = search_name(addressBook, var);

        //Validation for name
        if(index == -1)
        {
            printf("No matches found, Try again!...\n"); //
            goto user_esearch_name;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("      Name            Phoneno            email_Id\n");
        printf("%12s%18s%23s\n", addressBook -> contacts[index].name,  addressBook -> contacts[index].phone, addressBook -> contacts[index].email);
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");

        //Function call
        edit_option(&addressBook -> contacts[index]);   
     }
     else if(e_searchChoice == 2)
     {
        user_esearch_number:
         printf("Enter the number to edit: ");
         fgets(var,sizeof(var),stdin); //Getting input from the user
         var[strcspn(var,"\n")] = '\0'; 

        //  flag = count_num(var); // function call 
        //  //for 10 number validation
         if(count_num(var) || is_digit(var))
          {
             printf("Invalid Number, Try again...\n");
             goto user_esearch_number;
          }
       //function call
        index = search_number(addressBook, var);

        //Validation for name
        if(index == -1)
        {
            printf("No matches found, Try again!...\n"); //
            goto user_esearch_number;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("      Name            Phoneno            email_Id\n");
        printf("%12s%18s%23s\n", addressBook -> contacts[index].name,  addressBook -> contacts[index].phone, addressBook -> contacts[index].email);
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");

        //Function call
        edit_option(&addressBook -> contacts[index]);   
     }
     else if(e_searchChoice == 3)
     {
        user_esearch_mail:
         printf("Enter the mail to edit: ");
         fgets(var,sizeof(var),stdin); //Getting input from the user
         var[strcspn(var,"\n")] = '\0'; 


         //function call
        index = search_mail(addressBook, var);

        //Validation for name
        if(index == -1)
        {
            printf("No matches found, Try again!...\n"); //
            goto user_esearch_mail;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("      Name            Phoneno            email_Id\n");
        printf("%12s%18s%23s\n", addressBook -> contacts[index].name,  addressBook -> contacts[index].phone, addressBook -> contacts[index].email);
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");

        //Function call
        edit_option(&addressBook -> contacts[index]);   
     }
     else if(e_searchChoice == 4)
     {
        return;
     }
     else
     {
        printf("Invalid choice, Try again...\n");
        goto user_editcontact;
     }
    }

void deleteContact(AddressBook *addressBook, int d_search)
{
	/* Define the logic for deletecontact */
    user_deletecontact:
	/* Define the logic for Editcontact */
     char var[50]; //Declaring temporary variable
     int flag = 0;
     int index;
     //search function
     if(d_search == 1)
     {   
        user_dsearch_name:
         printf("Enter the Name to delete: ");
         getchar();
         fgets(var,sizeof(var),stdin); //Getting input from the user
         var[strcspn(var,"\n")] = '\0'; 

         flag = is_alpha(var); // function call 
         //for name validation
         if(flag)
         {
            printf("Invalid name, Try again...\n");
            goto user_dsearch_name;
         }
         //function call
        index = search_name(addressBook, var);

        //Validation for name
        if(index == -1)
        {
            printf("No matches found, Try again!...\n"); //
            goto user_dsearch_name;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("      Name            Phoneno            email_Id\n");
        printf("%12s%18s%23s\n", addressBook -> contacts[index].name,  addressBook -> contacts[index].phone, addressBook -> contacts[index].email);
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");

        //Function call
        delete_option(addressBook, index);   
     }
     else if(d_search == 2)
     {
        user_dsearch_number:
         printf("Enter the number to delete: ");
         fgets(var,sizeof(var),stdin); //Getting input from the user
         var[strcspn(var,"\n")] = '\0'; 

        //  flag = count_num(var); // function call 
        //  //for 10 number validation
         if(count_num(var) || is_digit(var))
          {
             printf("Invalid Number, Try again...\n");
             goto user_dsearch_number;
          }
       //function call
        index = search_number(addressBook, var);

        //Validation for name
        if(index == -1)
        {
            printf("No matches found, Try again!...\n"); //
            goto user_dsearch_number;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("      Name            Phoneno            email_Id\n");
        printf("%12s%18s%23s\n", addressBook -> contacts[index].name,  addressBook -> contacts[index].phone, addressBook -> contacts[index].email);
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");

        //Function call
        delete_option(addressBook, index);   
     }
     else if(d_search == 3)
     {
        user_dsearch_mail:
         printf("Enter the mail to delete: ");
         fgets(var,sizeof(var),stdin); //Getting input from the user
         var[strcspn(var,"\n")] = '\0'; 


         //function call
        index = search_mail(addressBook, var);

        //Validation for name
        if(index == -1)
        {
            printf("No matches found, Try again!...\n"); //
            goto user_dsearch_mail;
        }
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");
        printf("      Name            Phoneno            email_Id\n");
        printf("%12s%18s%23s\n", addressBook -> contacts[index].name,  addressBook -> contacts[index].phone, addressBook -> contacts[index].email);
        printf("------------------------------------------------------------\n");
        printf("------------------------------------------------------------\n");

        //Function call
        delete_option(addressBook, index);    
     }
     else if(d_search == 4)
     {
        return;
     }
     else
     {
        printf("Invalid choice, Try again...\n");
        goto user_deletecontact;
     }
   
}

int is_alpha(char *p) //For checking the valid name or not
{
    while(*p != '\0') //validation
    {
        if((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || *p == ' ')
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
    int count = 0; //initialize count from zero to check the length
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

int search_name(AddressBook *addressBook, char *name) //for checking the name is existing or not 
{
   for(int i = 0;i < addressBook -> contactCount;i++) //TO cheak everyname in address book 
   {
    if(strcmp(name,addressBook -> contacts[i].name) == 0) //Using strcmp() to compare the strings
    {
        return i;
    }
   }
   return -1;
}

int search_number(AddressBook *addressBook, char *number) //For checking the mobileno is existing or not
{
    for(int i = 0;i < addressBook -> contactCount;i++) //TO cheak everynumber in address book 
   {
    if(strcmp(number,addressBook -> contacts[i].phone) == 0) //Using strcmp() to compare the strings
    {
        return i;
    }
   }
   return -1;
}

int search_mail(AddressBook *addressBook, char *ID) //For checking the Mail_ID is existing or not
{
    for(int i = 0;i < addressBook -> contactCount;i++) //TO cheak everymail in address book 
   {
    if(strcmp(ID,addressBook -> contacts[i].email) == 0) //Using strcmp() to compare the strings
    {
        return i;
    }
   }
   return -1;
}

void edit_option(Contact *contact) //for show the edit option to the user
{   
    user_editoption:
    //getting the choice from user
    printf("Select the option to edit\n");
    printf("1. Edit name\n");
    printf("2. Edit Phone_no\n");
    printf("3. Edit Email\n");
    printf("4. Exit\n");
    printf("Enter the choice\n");
    int choice; //declaring variable to save the choice
    scanf("%d", &choice);
    
    char temp[50];
    int flag = 0;
    if(choice == 1)
    {   
        user_editname:
        printf("Enter the New name: ");
        getchar();
        fgets(temp,sizeof(temp),stdin);
        temp[strcspn(temp,"\n")] = '\0';

        //Function call
        flag = is_alpha(temp);

        //name validation 
        if(flag)
        {
            printf("Enter the valid new name\n");
            goto user_editname;
        }
        strcpy(contact -> name,temp);
        printf("Name Modified Successfully!\n");
    }
    else if(choice == 2)
    {
        user_editnumber:
        printf("Enter the New number: ");
        fgets(temp,sizeof(temp),stdin);
        temp[strcspn(temp,"\n")] = '\0';

        
        if(count_num(temp) || is_digit(temp))
        {
            printf("Enter the valid new number\n");
            goto user_editnumber;
        }
        strcpy( contact -> phone,temp);
        printf("Phone no Modified Successfully!\n");
    }
    else if(choice == 3)
    {
        user_editmail:
        printf("Enter the New mail_Td: ");
        fgets(temp,sizeof(temp),stdin);
        temp[strcspn(temp,"\n")] = '\0';

        //Function call
        flag = is_ID(temp);

        //name validation 
        if(flag)
        {
            printf("Enter the valid new mail ID\n");
            goto user_editmail;
        }
        strcpy(contact-> email,temp);
        printf("Email Id Modified Successfully!\n");
    }
    else if(choice == 4)
    {
        return;
    }
    else
    {
        printf("Invalid Choice, Try again...\n");
        goto user_editoption;
    }
}
  
void delete_option(AddressBook *addressBook, int index) //For shifting(deleting) the contacts
{
    char res; //Declaration
    printf("Are you sure want to delete? (Y or N):  "); //Asking user to confirm delete
    scanf("%c", &res);

    user_deleteopt:
    //Validation
    if(res == 'y' || res == 'Y') 
    {
        for(int i = index; i < addressBook -> contactCount - 1; i++)
        {
            addressBook -> contacts[i] = addressBook -> contacts[i + 1];
        }
    }
    else if(res == 'n' || res == 'N')
    {
        printf("Process Denied!...\n");
        return;
    }
    else
    {
        printf("Invalid Choice, Enter the valid choice\n");
        goto user_deleteopt;
    }

    addressBook -> contactCount--; //decremeting the contact count
}

