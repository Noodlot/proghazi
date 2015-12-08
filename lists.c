#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"
#include "bin.h"

/* Végigmegy a "studio" fésűs listán, és kiírja a stúdiók nevét. */

void filmgyarak(studiolistaelem *studiohead)
{
	studiolistaelem *s = studiohead;

	while (s != NULL)
	{
		printf("-%s\n", s->sadat.studioname);
		s = s->next;
	}

}

/* Végigmegy mind a kettŐ fésűs listán ("studio", "movie"), és ha egyezik az id, azaz a film az adott stúdióban készült, kiírja a stúdióval együtt. */

void studiofilmei(studiolistaelem *studiohead, movielistaelem *moviehead)
{
	studiolistaelem *s = studiohead;
	movielistaelem *m = moviehead;

	while (s != NULL)
	{

		while (m != NULL)
		{

			if (s->sadat.studioid == m->madat.id)
			{
				printf("-%s: ", s->sadat.studioname);
				printf("%s\n", m->madat.moviename);
			}

			m = m->NEXT;

		}

		m = moviehead;
		s = s->next;

	}

}

/* Végigmegy a "movie" fésűs listán, megvizsgálja, melyik a legnagyobb IMDB pontszám. Azután újból végigmegy a listán, és kiírja annak a filmnek a címét, amelyiknek a legnagyobb az IMDB pontja. */

void maximdb(movielistaelem *moviehead)
{
	movielistaelem *m = moviehead;
	double max = 0.0;

	while (m != NULL)
	{

		if (m->madat.imdb > max)
			max = m->madat.imdb;
		m = m->NEXT;
	}

	m = moviehead;

	while (m != NULL)
	{
		if (m->madat.imdb == max)
			printf("-%s\n", m->madat.moviename);
		m = m->NEXT;
	}

}

/* Egyszerű elemhozzáadás a "movie" fésűs listához. */

movielistaelem* filmhozzaadas(movielistaelem *moviehead, char *title, int year, double ajemdibi, char *rendezo, char *sztar, int azonosito)
{
	movielistaelem *p = (movielistaelem*)malloc(sizeof(movielistaelem));

	strcpy(p->madat.moviename, title);
	p->madat.made = year;
	p->madat.imdb = ajemdibi;
	strcpy(p->madat.dirname, rendezo);
	strcpy(p->madat.starname, sztar);
	p->madat.id = azonosito;
	p->NEXT = moviehead;
	moviehead = p;

	return moviehead;

}

/* Végigmegy a "movie" fésűs listán, megvizsgálja, hogy a kapott cím egyezik-e valamelyik listában szereplő címmel. Ha talált egyezést, kiírja a rendezője nevét. Ha nem, akkor kiírja, hogy nincs ilyen film. */

void kirendezte(movielistaelem *moviehead, char *title)
{
	movielistaelem *m = moviehead;
	int loop = 1;

	while (loop)
	{

		if (strcmp(m->madat.moviename, title) == 0)
		{
			printf("%s\n", m->madat.dirname);
			loop = 0;
		}

		if (m->NEXT == NULL)
			loop = 0;
		else
			m = m->NEXT;
	}

	if (loop)
		printf("Nincs ilyen film. Biztos vagy benne, hogy jo cimet adtal meg?\n");

}

/* Végigmegy a "movie" listán, és rendezi a listát az IMDB pontszámok szerint. A függvény a rendezett lista pointerjével tér vissza. */

movielistaelem *imdbsort(movielistaelem *current)
{
	movielistaelem *head = current;
	movielistaelem *insert = head;

	double tempimdb;
	int tempid, tempyear;
	char tempdir[50];
	char temptitle[50];
	char tempszereplo[50];

	current = current->NEXT;

	while (current != NULL)
	{
		insert = head;

		while (insert != current)
		{

			if (insert->madat.imdb > current->madat.imdb)
			{
				tempimdb = current->madat.imdb;
				tempid = current->madat.id;
				tempyear = current->madat.made;
				strcpy(tempdir, current->madat.dirname);
				strcpy(temptitle, current->madat.moviename);
				strcpy(tempszereplo, current->madat.starname);

				current->madat.imdb = insert->madat.imdb;
				current->madat.id = insert->madat.id;
				current->madat.made = insert->madat.made;
				strcpy(current->madat.dirname, insert->madat.dirname);
				strcpy(current->madat.moviename, insert->madat.moviename);
				strcpy(current->madat.starname, insert->madat.starname);

				insert->madat.imdb = tempimdb;
				insert->madat.id = tempid;
				insert->madat.made = tempyear;
				strcpy(insert->madat.dirname, tempdir);
				strcpy(insert->madat.moviename, temptitle);
				strcpy(insert->madat.starname, tempszereplo);
			}

			else
			{
				insert = insert->NEXT;
			}
		}

		current = current->NEXT;

	}

	return head;

}

/* Végigmegy a "movie" listán, és az IMDB pontszámoknak fenntartott tömböt feltölti pontszámokkal. A tömb indexe jelöli a stúdiót. 
   Majd az IMDB tömb elemeit elosztja az adott indexhez tartozó filmmennyiség tömb elemeivel. 
   Majd kiírja stúdiónként a hozzátartozó IMDB pontszámátlagot */

void atlagoljunk(studiolistaelem *studioheader, movielistaelem *movieheader, double tob[], int mennyi[], int size)
{
	movielistaelem *m = movieheader;
	studiolistaelem *s = studioheader;
	double *atlag = tob;
	int *annyi = mennyi;
	int i, n = size+1;

	while (m != NULL)
	{
		atlag[m->madat.id] = atlag[m->madat.id] + m->madat.imdb;
		m = m->NEXT;
	}

	m = movieheader;

	for (i = 0; i < n; i++)
	{
		atlag[i] = atlag[i] / annyi[i];
	}

	while (s != NULL)
	{
		printf("-%s: %lf\n", s->sadat.studioname, atlag[s->sadat.studioid]);
		s = s->next;
	}

	s = studioheader;

}
