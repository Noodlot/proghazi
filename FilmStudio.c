#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"

int main() 
{

/* DEKLARALAS */

	studiolistaelem *slistatxt = NULL;
	studiolistaelem *slista = NULL;
	studiolistaelem *uj;
	studio asdf;

	movielistaelem *mlista = NULL;
	movielistaelem *mlistaptr;
	movielistaelem *NEW;
	movie fdsa;

	int studioszam = 0, i;
	int year, azon = 0;
	int *hanyfilm;
	int tempid;

	double ajemdibi = 0.0;
	double *atlaglista;

	char filmhozza[50];
	char rendezohozza[50];
	char szineszhozza[50];
	char *s = { "TwelveMonkeys" };

/* VEGE:DEKLARALAS*/

/* FILE BEOLVASAS*/

	FILE *fm = fopen("Movies.txt", "r");
	FILE *fs = fopen("Studios.txt", "r");
	FILE *fki = fopen("Result.txt", "w");

	if (fs == NULL)
		exit(1);

	while (!feof(fs))
	{
		uj = (studiolistaelem *)malloc(sizeof(studiolistaelem));
		fscanf(fs, "%s\n%d\n%s\n%d", asdf.studioname, &asdf.founded, asdf.hq, &asdf.studioid);
		strcpy(uj->sadat.studioname, asdf.studioname);
		uj->sadat.founded = asdf.founded;
		strcpy(uj->sadat.hq, asdf.hq);
		uj->sadat.studioid = asdf.studioid;
		if (uj->sadat.studioid > studioszam)
			studioszam++;
		uj->next = slistatxt;
		slistatxt = uj;
	}

/* ATLAGSZAMITASHOZ */

	studioszam = studioszam + 1;

	atlaglista = (double *)malloc(studioszam* sizeof(double));
	for (i = 0; i < studioszam; i++) 
	{
		atlaglista[i] = 0.0;
	}

	hanyfilm = (int *)malloc(studioszam*sizeof(int));
	for (i = 0; i < studioszam; i++)
	{
		hanyfilm[i] = 0;
	}

/* VEGE:ATLAG */

	if (fm == NULL)
		exit(1);

	while (!feof(fm))
	{
		NEW = (movielistaelem *)malloc(sizeof(movielistaelem));
		fscanf(fm, "%s\n%d\n%lf\n%s\n%s\n%d\n", fdsa.moviename, &fdsa.made, &fdsa.imdb, fdsa.dirname, fdsa.starname, &fdsa.id);
		strcpy(NEW->madat.moviename, fdsa.moviename);
		NEW->madat.made = fdsa.made;
		NEW->madat.imdb = fdsa.imdb;
		strcpy(NEW->madat.dirname, fdsa.dirname);
		strcpy(NEW->madat.starname, fdsa.starname);
		NEW->madat.id = fdsa.id;
		NEW->NEXT = mlista;
		mlista = NEW;
		tempid = fdsa.id;
		for (i = 1; i < studioszam+1; i++)
		{
			if (i == tempid)
			{
				hanyfilm[i]++;
			}
		}
	}

/* VEGE:FILEBEOLVASAS */

/* STUDIOTXT FILE KIMENTESE BINARISBA, MAJD A BINARISBOL A STUDIOLISTA LETREHOZASA */

	//savetofile(slistatxt);
	slista = loadfromfile(slista);

/* ELSO FELADAT */

	printf("\nElso feladat: Irjuk ki milyen studiOk vannak!:\n\n");
	filmgyarak(slista);

/* MASODIK FELADAT */

	printf("\nMasodik feladat: Irjuk ki studionkent a filmeket!:\n\n");
	studiofilmei(slista, mlista);

/* HARMADIK FELADAT */

	printf("\nHarmadik feladat: Irjuk ki a maximalis Imdb pontszammal rendelkezo filmet!:\n\n");
	maximdb(mlista);

/* NEGYEDIK FELADAT */

	printf("\nNegyedik feladat: adjunk hozza egy filmet!:\n");
	printf("De elobb add meg a film cimet(max 49), aztan a gyartasi evet(egesz), imdb pontszamot(tort), rendezonevet(max 49), foszereplo nevet(max 49), filmgyar azonositojat(1-6)! (enterrel valaszdd el oket)  PLS :3 : \n");
	scanf("%s\n%d\n%lf\n%s\n%s\n%d", filmhozza, &year, &ajemdibi, rendezohozza, szineszhozza, &azon);

	for (i = 1; i < studioszam+1; i++)
	{
		if (i == azon)
		{
			hanyfilm[i]++;
		}
	}

	mlista = filmhozzaadas(mlista, filmhozza, year, ajemdibi, rendezohozza, szineszhozza, azon);
	mlistaptr = mlista;

/* OTODIK FELADAT */

	printf("\nOtodik feladat: Irjuk ki ki rendezte az alabbi filmet: (Adj meg egy filmet)!\n\n");
	kirendezte(mlista,s);

/* HATODIK FELADAT */

	printf("\nHatodik feladat: Rendezzuk a filmeket IMDB pontszam szerint, majd irjuk ki egy file-ba rendezve a filmeket! Ezenkivul adjuk meg a studiok altal elkeszitett filmek osszesitett IMDB atlaat.\n\n");
	imdbsort(mlista);
	atlagoljunk(slista, mlista, atlaglista, hanyfilm, studioszam);

/* FILEBA KIIRÁS */

	if (fki == NULL)
		exit(1);
	while (mlista != NULL)
	{
		movielistaelem *p = mlista->NEXT;
		fprintf(fki, "%s\n%d\n%.1f\n%s\n%s\n%d\n", mlista->madat.moviename, mlista->madat.made, mlista->madat.imdb, mlista->madat.dirname, mlista->madat.starname, mlista->madat.id);
		mlista = p;
	}

/* LEZARAS ÉS FELSZABADITAS */

	free(slista);
	free(mlista);
	fclose(fki);
	fclose(fm);
	fclose(fs);
	return 0;
}

/* 
ELLENORZŐ KIIRASOK

while (mlista != NULL)
{
	movielistaelem *p = mlista->NEXT;
	printf("%s\n%d\n%.1f\n%s\n%s\n%d\n", mlista->madat.moviename, mlista->madat.made, mlista->madat.imdb, mlista->madat.dirname, mlista->madat.starname, mlista->madat.id);
	mlista = p;
}

mlista = mlistaptr;


for (i = 1; i < studioszam; i++)
{
printf(" %d,", hanyfilm[i]);
}
for (i = 1; i < studioszam; i++)
{
printf(" %lf,", atlaglista[i]);
}
*/
