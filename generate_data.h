/*
 * generate_data.h
 *
 *  Created on: 04.12.2014
 *      Author: Georg
 */

#ifndef GENERATE_DATA_H_
#define GENERATE_DATA_H_


char* randName(char nameGen[32]);

int height(int age, int sex);

float mass(int height);

unsigned int checkYear(int age, int sex);

unsigned int isPregnant(int age);

unsigned int checkMonth(unsigned int year);

unsigned int checkDay(unsigned int year, unsigned int month);

#endif /* GENERATE_DATA_H_ */
