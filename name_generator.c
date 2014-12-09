/*
 * name_generator.c
 *
 *  Created on: 05.12.2014
 *      Author: Georg
 */


#include <stdlib.h>
#include <string.h>
#include <ctype.h>


const char NamePrefix[][5] =
{
"",		"bel", 		"nar",		"",			"se",
"ev",	"theo",		"mar",		"res",		"ter",
"su",	"ga",		"kar",		"sah",		"sin",
"pro",	"man",		"el"
};

const char NameSuffix[][5] =
{

"", 		"us", 		"ix", 		"ox", 		"ith",
"ath", 		"um", 		"ator", 	"or", 		"axia",
"imus", 	"ais", 		"itur", 	"orex", 	"o",
"y",		"hein",		"rich",		"son",		"er",
"af",		"baum",		"beth",		"ne",		"olf",
"land"


};

const char NameStems[][10] =
{

"adur", 	"aes", 		"anim",	 	"apoll",	 	"imac",
"educ", 	"equis", 	"extr", 	"guius", 		"hann",
"equi", 	"amora",	 "hum", 	"iace", 		"ille",
"inept", 	"iuv", 		"obe", 		"ocul", 		"orbis",
"ra",		"isa",		"eodor",	"ina",			"paul",
"ge",		"org",		"horas",	"fram",			"kriss"

};


char* nameGenerate(char* Name)

{

	Name[0] = 0;


	if(!rand()%4)
		strcat(Name, NamePrefix[(rand() % 18)]);



	strcat(Name, NameStems[(rand() % 30)]);


	if(rand()%4)
		strcat(Name, NameSuffix[(rand() % 26)]);



	Name[0] = toupper(Name[0]);

	return Name;

}
