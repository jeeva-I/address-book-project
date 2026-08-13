#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook, int searchChoice);
int search_name(AddressBook*,char*);
int search_number(AddressBook*,char*);
int search_mail(AddressBook*,char*);
void editContact(AddressBook *addressBook, int);
void edit_option(Contact *contact);
void deleteContact(AddressBook *addressBook, int d_search);
void delete_option(AddressBook *addressBook, int index);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
