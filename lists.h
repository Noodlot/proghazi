#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED

typedef struct studio
{																				//studio struktura
	char studioname[50];
	int founded;
	char hq[50];
	int studioid;

} studio;

typedef struct studiolistaelem 
{																				//studiolista
	studio sadat;
	struct studiolistaelem *next;

} studiolistaelem;

typedef struct movie 
{																				//film struktura
	char moviename[50];
	int made;
	double imdb;
	char dirname[50];
	char starname[50];
	int id;

} movie;

typedef struct movielistaelem 
{																				//filmlista
	movie madat;
	struct movielistaelem *NEXT;

} movielistaelem;

void filmgyarak(studiolistaelem *studiohead);

void studiofilmei(studiolistaelem *studiohead, movielistaelem *moviehead);

void maximdb(movielistaelem *moviehead);

movielistaelem* filmhozzaadas(movielistaelem *moviehead, char *title, int year, double ajemdibi, char *rendezo, char *sztar, int azonosito);

void kirendezte(movielistaelem *moviehead, char *title);

movielistaelem *imdbsort(movielistaelem *current);

void atlagoljunk(studiolistaelem *studioheader, movielistaelem *moviehead, double tob[], int mennyi[], int size);

#endif
