/*
 * schaltjahr.c
 *
 *  Created on: 05.12.2014
 *      Author: Georg
 */

#include "schaltjahr.h"

static int aussageA (int Jahr) /*übergib Jahreszahl*/
/*Jahr ist durch 4 teilbar*/
{
	return (Jahr % 4) == 0;
}

static int aussageB (int Jahr) /*übergib Jahreszahl*/
/*Jahreszahl ist duch 100 teilbar*/
{
	return (Jahr % 100)==0;
}

static int aussageC (int Jahr) /*übergib Jahreszahl*/
/* Jahr ist durch 400 teilbar*/
{
	return (Jahr % 400)==0;
}

int istSchaltjahr (int Jahr) /*übergib Jahreszahl*/
/* berechnet bool für Jahr ist Schaltjahr nach A&&!(B&&!C)*/
{
	return ( aussageA(Jahr) && !(aussageB(Jahr) && !(aussageC(Jahr))));
}
