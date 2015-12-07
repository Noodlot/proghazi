#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED

/* STUDIO STUKTÚRA */

typedef struct studio
{
	char studioname[50];
	int founded;
	char hq[50];
	int studioid;

} studio;

/* STUDIO LISTA */

typedef struct studiolistaelem 
{
	studio sadat;
	struct studiolistaelem *next;

} studiolistaelem;

/* FILM STRUKTÚRA */

typedef struct movie 
{
	char moviename[50];
	int made;
	double imdb;
	char dirname[50];
	char starname[50];
	int id;

} movie;

/* FILM LISTA */

typedef struct movielistaelem 
{
	movie madat;
	struct movielistaelem *NEXT;

} movielistaelem;

/* FÜGGVÉNYEK */

void filmgyarak(studiolistaelem *studiohead);

void studiofilmei(studiolistaelem *studiohead, movielistaelem *moviehead);

void maximdb(movielistaelem *moviehead);

movielistaelem* filmhozzaadas(movielistaelem *moviehead, char *title, int year, double ajemdibi, char *rendezo, char *sztar, int azonosito);

void kirendezte(movielistaelem *moviehead, char *title);

movielistaelem *imdbsort(movielistaelem *current);

void atlagoljunk(studiolistaelem *studioheader, movielistaelem *moviehead, double tob[], int mennyi[], int size);

void savetofile(studiolistaelem *eleje);

studiolistaelem *loadfromfile(studiolistaelem *eleje);

#endif
