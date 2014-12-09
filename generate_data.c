/*
 * generate_data.c
 *
 *  Created on: 05.12.2014
 *      Author: Georg
 */


#include <stdlib.h>
#include "schaltjahr.h"
#include "generate_data.h"
#include "struct_patient.h"

/*char* randName(char nameGen[32])
{
	int randNumb, j;
	randNumb = (rand() % 8) + 3;
	for (j = 0; j <= randNumb; j++)
	{
		if (j == 0)
			nameGen[j] = (rand() % 24) + 65;
		else
		{
			nameGen[j] = (rand() % 24) + 97;
		}
	}
	nameGen[randNumb] = '\0';
	return nameGen;
}
*/
int height(int age, int sex)
{
	int size;
	if (age <= 16)
	{
		size = age * 9 + 15 + rand() % 20;
	}
	else if (age > 16 && sex == male)
	{
		size = 160 + rand() % 20 + rand() % 20;
	}
	else if (age > 16 && sex == female)
	{
		size = 150 + rand() % 20 + rand() % 10 + rand() % 10;
	}
	if (age >= 75)
	{
		size = size - (age - 75);
	}
	return size;
}

float mass(int height)
{
	int weight;

	weight = (((((float) height) / 100.0) * (((float) height) / 100.0))
			* (15 + (rand() % 10) + (rand() % 10)));
	if (weight < 1)
		weight = 1.0;
	return weight;
}

unsigned int checkYear(int age, int sex)
{
	unsigned int year = 1900, i;
	if (sex == female && age >= 30)
	{
		if(rand()%2)
		{
			year = 2014 - (age - 30);
			for (i = 0; i <= 1 + ((age - 30) % 10); i++)
			{
				year = year + rand() % 10 +1 ;
			}
		}
	}
	if (sex == male && age >= 50)
	{
		if(rand()%2)
		{
			year = 2014 - (age - 50);
			for (i = 0; i <= 1 + ((age - 50) % 10); i++)
			{
				year = year + rand() % 10 +1;
			}
		}
	}
	if (year > 2014)
		year = 2014;

	return year;
}

unsigned int isPregnant(int age)
{
	if (age >= 11 && age <= 25)
	{
		if ((rand() % 100 >= (100 / 16 * age - 1000 / 16)) && rand() % 4 == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (age > 25 && age <= 55)
	{
		if ((rand() % 100 >= (-100 / 30 * age + 550 / 3)) && rand() % 4 == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

unsigned int checkMonth(unsigned int year)
{
	if (year > 1900)
				return 1 + rand() % 12;

	else return 1;
}

unsigned int checkDay(unsigned int year, unsigned int month)
{
	if (year<=1900)
		{
		if ((month <= 7 && month % 2) || (month >= 8 && !(month % 2)))
			return rand()%31 +1;

		else if (month == 2)
		{
			if (istSchaltjahr(year))
				return rand()%29 +1;

			else
				return rand()%28+1;
		}
		else
			return rand()%30+1;
		}
	else
		return 1;
}

