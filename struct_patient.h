/*
 * struct_patient.h
 *
 *  Created on: 04.12.2014
 *      Author: Georg
 */

#ifndef STRUCT_PATIENT_NEU_H_
#define STRUCT_PATIENT_NEU_H_
#define MAX 32

enum SEX_type
{
	not_defined, male, female
};

struct date_male
{
	unsigned int day :5;
	unsigned int month :4;
	unsigned int year :12;
};

struct date_female
{
	unsigned int day :5;
	unsigned int month :4;
	unsigned int year :12;
	unsigned int pregnant :1;
};

union date
{
	struct date_male* male;
	struct date_female* female;
};

struct patient
{
	char name[MAX];
	char surname[MAX];
	enum SEX_type sex;
	int age;
	float mass;
	int size;
	unsigned int pNumber;
	union date check;
};

void print_Patient(struct patient patient);

#undef MAX
#endif /* STRUCT_PATIENT_NEU_H_ */
