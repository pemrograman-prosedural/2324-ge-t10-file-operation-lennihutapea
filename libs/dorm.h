#ifndef DORM_H
#define DORM_H

#include "gender.h"

typedef struct dorm_t
{
  char name[20];
  unsigned short capacity;
  gender_t gender;
  unsigned short residents_num;
} Dorm;

Dorm create_dorm ( char *_name, unsigned short _capacity, gender_t _gender );
short findDormIdx ( char* _name, Dorm *list, int length );
void print_dorm ( Dorm dorm_to_print );
void printDormDetails ( Dorm dorm_to_print );

#endif