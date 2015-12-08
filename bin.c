#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"
#include "bin.h"

int studioszam = 0;

void savetofile(studiolistaelem *eleje)
{
	studiolistaelem *akt = NULL;
	FILE *F = fopen("binarifile.dat", "wb");
	if (F == NULL)
		exit(1);

	for (akt = eleje; akt != NULL; akt = akt->next) {

		fwrite(&(akt->sadat), sizeof(studio), 1, F);
	}

	fflush(F);
	fclose(F);
}

studiolistaelem *loadfromfile(studiolistaelem *eleje)
{
	studio asdf;
	studiolistaelem *slista = NULL;
	studiolistaelem *uj;
	int n;

	FILE *F = fopen("binarifile.dat", "rb");
	if (F == NULL)
		exit(1);

	while (!feof(F)) 
	{
		n = fread(&asdf, sizeof(studio), 1, F);
		if (n == 1)
		{
			// A szokasos modon felvesszuk az uj adatokat a dinamikus listaba. Atadunk egy az
			// ideiglenes tarolo helyre mutato pointert, hogy onnan vegye az "add" az adatokat.
			uj = (studiolistaelem *)malloc(sizeof(studiolistaelem));
			strcpy(uj->sadat.studioname, asdf.studioname);
			uj->sadat.founded = asdf.founded;
			strcpy(uj->sadat.hq, asdf.hq);
			uj->sadat.studioid = asdf.studioid;
			if (uj->sadat.studioid > studioszam)
				studioszam++;
			uj->next = slista;
			slista = uj;

		}
	}

	fclose(F);

	eleje = slista;

	return eleje;
}
