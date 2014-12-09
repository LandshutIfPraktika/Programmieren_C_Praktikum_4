/*
 * main.c
 *
 *  Created on: 04.12.2014
 *      Author: Georg
 */

#include "struct_patient.h"
#include "generate_data.h"
#include "name_generator.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define DB_SIZE 100
/*für verschieden große Datenbanken*/

struct patient patient_db[DB_SIZE];
/*globales array für DB_SIZE Patienten*/

struct date_male* initialise_male(int age)
{
	struct date_male* pointer;
	pointer = malloc(sizeof(struct date_male));
	pointer->year = checkYear(age, male);
	pointer->month = checkMonth(pointer->year);
	pointer->day = checkDay(pointer->year, pointer->month);
	return pointer;
}

struct date_female* initialise_female(int age)
{
	struct date_female* pointer;
	pointer = malloc(sizeof(struct date_female));
	pointer->year = checkYear(age, female);
	pointer->month = checkMonth(pointer->year);
	pointer->day = checkDay(pointer->year, pointer->month);
	pointer->pregnant = isPregnant(age);
	return pointer;
}

void free_patient(struct patient patient)
{
	if (patient.sex == female)
		free(patient.check.female);

	if (patient.sex == male)
		free(patient.check.male);
}

void free_db(struct patient patient_db[])
{
	int i;
	for (i = 0; i < DB_SIZE; i++)
	{
		free_patient(patient_db[i]);
	}
}

/*Initialisiert den Vektor patient_db mit
 * DB_SIZE Zufallsgenerierten Patientendaten
 */
void initialise_db(struct patient patient_db[])
{
	srand((unsigned) time(NULL));

	int i = 0;
	char *nameGen;
	nameGen = calloc(32, sizeof(char));
	for (i = 0; i < DB_SIZE; i++)
	{
		patient_db[i].pNumber = i;

		strcpy(patient_db[i].name, nameGenerate(nameGen));

		strcpy(patient_db[i].surname, nameGenerate(nameGen));

		patient_db[i].age = rand() % 100;

		if (rand() % 2)
		{
			patient_db[i].sex = female;
			patient_db[i].check.female = initialise_female(patient_db[i].age);
		}

		else
		{
			patient_db[i].sex = male;
			patient_db[i].check.male = initialise_male(patient_db[i].age);
		}

		patient_db[i].size = height(patient_db[i].age, patient_db[i].sex);

		patient_db[i].mass = mass(patient_db[i].size);

	}
	free(nameGen);
}

float compute_bmi(struct patient patient)
{
	float bmi, mass, size;
	mass = patient.mass;
	size = patient.size / 100.0;
	bmi = mass / (size * size);
	return bmi;
}

float compute_bmip(struct patient *patient)
{
	float bmi, mass, size;
	mass = patient->mass;
	size = patient->size / 100.0;
	bmi = mass / (size * size);
	return bmi;
}

/*Durchsucht patient_db nach allen Patienten mit
 * bmi<20 und bmi>24 und speichert die Position
 * in entweder obeseI[] oder anorexiaI[] die zugeh�rigen
 * BMI Werte werden in obeseF[] bzw. anorexiaF[] an selber
 * Stelle gespeichert.
 * Im Anschluss werden die Patienten nach �bergewicht bzw.
 * Untergewicht sortiert ausgegeben
 */
void identify_risk(struct patient patient_db[])
{
	int i, j = 0, k = 0, obeseI[DB_SIZE], anorexiaI[DB_SIZE];
	float bmi, obeseF[DB_SIZE], anorexiaF[DB_SIZE];

	for (i = 0; i < DB_SIZE; i++)
	{
		bmi = compute_bmi(patient_db[i]);

		if (bmi < 20)
		{
			anorexiaI[k] = i;
			anorexiaF[k] = bmi;
			k++;
		}
		if (bmi > 25)
		{
			obeseI[j] = i;
			obeseF[j] = bmi;
			j++;
		}
	}
	printf("Risikogruppe \"Anorexia:\":\n");

	for (i = 0; i < k; i++)
	{
		printf("%s, %s\t BMI: %f \n", patient_db[anorexiaI[i]].name,
				patient_db[anorexiaI[i]].surname, anorexiaF[i]);
	}
	printf("\n \nRisikogruppe \"Obesitas:\":\n");

	for (i = 0; i < j; i++)
	{
		printf("%s, %s \t BMI: %f \n", patient_db[obeseI[i]].name,
				patient_db[obeseI[i]].surname, obeseF[i]);
	}
	printf("\n \n \n");
}

/*Siehe identify_risk()
 * Der einzige unterschied ist das mit pointern
 * übergeben und gearbeitet wird
 */
void identify_risk_group(struct patient *patient_db, int size)
{
	int i, j = 0, k = 0, obeseI[size], anorexiaI[size];
	float bmi, obeseF[size], anorexiaF[size];

	for (i = 0; i < size; i++)
	{
		bmi = compute_bmip(patient_db + i);

		if (bmi < 20)
		{
			anorexiaI[k] = i;
			anorexiaF[k] = bmi;
			k++;
		}
		if (bmi > 25)
		{
			obeseI[j] = i;
			obeseF[j] = bmi;
			j++;
		}
	}
	printf("Risikogruppe \"Anorexia:\":\n");

	for (i = 0; i < k; i++)
	{
		printf("%s, %s\t BMI: %f \n", (patient_db + anorexiaI[i])->name,
				(patient_db + anorexiaI[i])->surname, anorexiaF[i]);
	}
	printf("\n \nRisikogruppe \"Obesitas:\":\n");

	for (i = 0; i < j; i++)
	{
		printf("%s, %s \t BMI: %f \n", (patient_db + obeseI[i])->name,
				(patient_db + obeseI[i])->surname, obeseF[i]);
	}
	printf("\n \n \n");
}

/*Durchsucht nach check.female->pregnant
 * und gibt alle Treffer aus
 */
void identify_pregnant(struct patient patient_db[])
{
	int i;
	printf("Alle schwangeren Patientinnen: \n");
	for (i = 0; i < DB_SIZE; i++)
	{
		if (patient_db[i].sex == female)
		{
			if (patient_db[i].check.female->pregnant)
				printf("%s, %s \n", patient_db[i].name, patient_db[i].surname);
		}
	}
	printf("\n \n");
}

/*Das selbe wie bei identify_risk nur das nach Patienten
 * gesucht wird die seit 10 Jahren nichtmehr bei der Vorsorge
 * waren.
 * Ausgabe nach Frauen und Männern getrennt
 */
void identify_screening(struct patient patient_db[])
{
	int i, j = 0, k = 0, maleI[DB_SIZE], femaleI[DB_SIZE];
	for (i = 0; i < DB_SIZE; i++)
	{
		if ((patient_db[i].sex == female) && patient_db[i].age >= 30
				&& (2014 - patient_db[i].check.female->year) >= 10)
		{
			femaleI[j] = i;
			j++;
		}
		else if ((patient_db[i].sex == male) && patient_db[i].age >= 50
				&& (2014 - patient_db[i].check.male->year) >= 10)
		{
			maleI[k] = i;
			k++;
		}
	}
	printf("weibliche Vorsorgemuffel:\n \n");

	for (i = 0; i < j; i++)
	{
		printf("%s, %s\n", patient_db[femaleI[i]].name,
				patient_db[femaleI[i]].surname);
	}
	printf("\n \n \nmaennliche Vorsorgemuffel:\n \n");

	for (i = 0; i < k; i++)
	{
		printf("%s, %s\n", patient_db[maleI[i]].name,
				patient_db[maleI[i]].surname);
	}
	printf("\n \n \n");
}

/*sucht nach einem bestimmten Namen und gibt alle
 * Patienten mit diesem vollst�ndig aus
 */
void find_name(struct patient patient_db[])
{
	char nameSearch[32];
	int i, k = 0, match[DB_SIZE];
	printf("Name: \n");
	scanf("%s", nameSearch);
	for (i = 0; i < DB_SIZE; i++)
	{
		if (strcmp(nameSearch, patient_db[i].name) == 0)
		{
			match[k] = i;
			k++;
		}
	}

	for (i = 0; i < k; i++)
	{
		print_Patient(patient_db[match[i]]);
	}
}

int main_menu(void)
{
	int i;
	printf(
			"\n\n1. Alle Risikopatienten identifizieren \n"
					"2. Alle Risikopatienten identifizieren (ab Patient Nummer x) \n"
					"3. Alle schwangeren Patientinnen ausgeben \n"
					"4. Alle Patienten ausgeben, die in den letzten 10 Jahren keine Vorsorgeuntersuchung hatten \n"
					"5. Alle Patienten mit einem einzugebenden Namen ausgeben \n \n"
					"0. Programm beenden \n \n");

	scanf("%d", &i);

	return i;
}

int main(void)
{

	initialise_db(patient_db);

	printf("Anzahl der zu initialisierenden Patienten: ");

	int choice, start, anzahl;

	do
	{
		do
		{
			choice = main_menu();
			if (choice == 1705)
				break;
		} while (choice < 0 && choice > 5);
		switch (choice)
		{
		case 1:
		{
			identify_risk(patient_db);
			break;
		}
		case 2:
		{
			do
			{
				printf("Startnummer: \n");
				scanf("%d", &start);
				printf("Anzahl: \n");
				scanf("%d", &anzahl);
			} while (start < 1 || start > 100 || anzahl > (DB_SIZE + 1 - start));
			identify_risk_group(patient_db + start - 1, anzahl);
			break;
		}
		case 3:
		{
			identify_pregnant(patient_db);
			break;
		}
		case 4:
		{
			identify_screening(patient_db);
			break;
		}
		case 5:
		{
			find_name(patient_db);
			break;
		}
		case 1705:
		{
			free_db(patient_db);
			initialise_db(patient_db);
			break;
		}

		default:
		{
			break;
		}
		}

	} while (choice);

	free_db(patient_db);
	printf("0");

	return 0;
}
