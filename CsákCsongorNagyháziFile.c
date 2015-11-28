#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"

int main() 
{

/* DEKLARÁLÁS */

	studiolistaelem *slista = NULL;
	studiolistaelem *slistaptr;
	studio asdf;
	movielistaelem *mlista = NULL;
	movielistaelem *mlistaptr;
	movie fdsa;

	int studioszam = 0, i;
	int year, azon = 0;

	double ajemdibi = 0.0;

	char filmhozza[50];
	char rendezohozza[50];
	char szineszhozza[50];
	char *s = { "TwelveMonkeys" };

/* VÉGE:DEKLARÁLÁS*/

/* FILE BEOLVASÁS*/

	FILE *fm = fopen("Movies.txt", "r");
	FILE *fs = fopen("Studios.txt", "r");
	FILE *fki = fopen("Result.txt", "w");

	if (fs == NULL)
		exit(1);

	while (!feof(fs))
	{
		studiolistaelem *new = (studiolistaelem *)malloc(sizeof(studiolistaelem));
		fscanf(fs, "%s\n%d\n%s\n%d", asdf.studioname, &asdf.founded, asdf.hq, &asdf.studioid);
		strcpy(new->sadat.studioname, asdf.studioname);
		new->sadat.founded = asdf.founded;
		strcpy(new->sadat.hq, asdf.hq);
		new->sadat.studioid = asdf.studioid;
		if (new->sadat.studioid > studioszam)
			studioszam++;
		new->next = slista;
		slista = new;
	}

	slistaptr = slista;

/* ÁTLAGSZÁMÍTÁSHOZ */

	studioszam = studioszam + 1;

	double *atlaglista = (double *)malloc(studioszam* sizeof(double));
	for (i = 0; i < studioszam; i++) 
	{
		atlaglista[i] = 0.0;
	}

	int *hanyfilm = (int *)malloc(studioszam*sizeof(int));
	for (i = 0; i < studioszam; i++)
	{
		hanyfilm[i] = 0;
	}

/* VÉGE:ÁTLAG */

	if (fm == NULL)
		exit(1);

	while (!feof(fm))
	{
		movielistaelem *NEW = (movielistaelem *)malloc(sizeof(movielistaelem));
		fscanf(fm, "%s\n%d\n%lf\n%s\n%s\n%d\n", fdsa.moviename, &fdsa.made, &fdsa.imdb, fdsa.dirname, fdsa.starname, &fdsa.id);
		strcpy(NEW->madat.moviename, fdsa.moviename);
		NEW->madat.made = fdsa.made;
		NEW->madat.imdb = fdsa.imdb;
		strcpy(NEW->madat.dirname, fdsa.dirname);
		strcpy(NEW->madat.starname, fdsa.starname);
		NEW->madat.id = fdsa.id;
		NEW->NEXT = mlista;
		mlista = NEW;
		int tempid = fdsa.id;
		for (i = 1; i < studioszam+1; i++)
		{
			if (i == tempid)
			{
				hanyfilm[i]++;
			}
		}
	}

/* VÉGE:FILEBEOLVASÁS */

/* ELSŐ FELADAT */

	printf("\nElso feladat: Irjuk ki milyen studiók vannak!:\n\n");
	filmgyarak(slista);

/* MÁSODIK FELADAT */

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

/* ÖTÖDIK FELADAT */

	printf("\nOtodik feladat: Irjuk ki ki rendezte az alabbi filmet: (Adj meg egy filmet)!\n\n");
	kirendezte(mlista,s);

/* HATODIK FELADAT */

	printf("\nHatodik feladat: Rendezzük a filmeket IMDB pontszam szerint, majd írjuk ki egy file-ba rendezve a filmeket! Ezenkívül adjuk meg a stúdiók által elkészített filmek összesített IMDB átlagát.\n\n");
	imdbsort(mlista);
	atlagoljunk(slista, mlista, atlaglista, hanyfilm, studioszam);

/* FILEBA KIÍRÁS */

	if (fki == NULL)
		exit(1);
	while (mlista != NULL)
	{
		movielistaelem *p = mlista->NEXT;
		fprintf(fki, "%s\n%d\n%.1f\n%s\n%s\n%d\n", mlista->madat.moviename, mlista->madat.made, mlista->madat.imdb, mlista->madat.dirname, mlista->madat.starname, mlista->madat.id);
		mlista = p;
	}

/* LEZÁRÁS ÉS FELSZABADÍTÁS */

	free(slista);
	free(mlista);
	fclose(fki);
	fclose(fm);
	fclose(fs);
	return 0;
}

/* 
ELLENŐRZŐ KIÍRÁSOK

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
