/*
 * struct_patient_neu.c
 *
 *  Created on: 05.12.2014
 *      Author: Georg
 */


#include <stdio.h>
#include <string.h>
#include "struct_patient.h"
#define MAX 32


void print_Patient(struct patient patient)
{
	char string1[20];
	if (patient.sex == male)
		strcpy(string1, "männlich");

	else if (patient.sex == female)
		strcpy(string1, "weiblich");

	printf("Name: %s \tVorname: %s \tPatientenNr.: %d \n", patient.name,
			patient.surname, patient.pNumber);
	printf("Alter: %d \tGeschlecht: %s\n", patient.age, string1);
	printf("Groesse: %d cm \tGewicht: %.2f kg \n", patient.size, patient.mass);

	if (patient.sex == female)
	{
		if (patient.check.female->pregnant)
			printf("Schwangerschaftsstatus: schwanger \n");
		else
			printf("Schwangerschaftsstatus: nicht schwanger \n");

		if (patient.check.female->year > 1900)
			printf("Letzte Vorsorgeuntersuchung: %d.%d.%d \n",
					patient.check.female->day, patient.check.female->month,
					patient.check.female->year);
		else
			printf(
					"Letzte Vorsorgeuntersuchung: keine Vorsorgeuntersuchung stattgefundenn ");
	}

	else if (patient.sex == male)
	{
		if (patient.check.male->year > 1900)
			printf("Letzte Vorsorgeuntersuchung: %d.%d.%d \n",
					patient.check.male->day, patient.check.male->month,
					patient.check.male->year);
		else
			printf(
					"Letzte Vorsorgeuntersuchung: keine Vorsorgeuntersuchung stattgefundenn ");
	}
	printf("\n \n");
}
