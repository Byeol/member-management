#ifndef __PERSON_H__
#define __PERSON_H__

#define name_maxchar 10
#define address_maxchar 100
#define phone_maxchar 100

typedef struct _PERSON {
	int memberId;
	char name[name_maxchar];
	char address[address_maxchar];
	char phone[phone_maxchar];
} PERSON;

#endif