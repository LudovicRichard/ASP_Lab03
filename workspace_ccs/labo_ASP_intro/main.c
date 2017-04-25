/*---------------------------------------------------------------------------------------
* But               : Petit programme pour etre charge dans le micro et affiche avec dump
* Auteur            : Evangelina LOLIVIER-EXLER
* Date              : 29.07.2008
* Version           : 1.0
* Fichier           : demo.c
*----------------------------------------------------------------------------------------*/
#include "cfg.h"
#include "stddefs.h"


/* Global variables */

vulong AppStack_svr[APPSTACKSIZE/4];
vulong AppStack_irq[APPSTACKSIZE/4];
int t[8];


/* main */
int main(void)
{

	int i;

	for (i=0;i<8;i++)
	{
		t[i] = i*(i-4);
	}

	while (1);

	return(0);
}
