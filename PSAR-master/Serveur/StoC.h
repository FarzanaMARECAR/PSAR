/**	StoC.h
 * 
 * Fichier Header avec les méthodes Serveurs liées aux services
 * 
 * Auteur : MARECAR Farzana
 * Projet : Entrepôt Réparti en mémoire
 * Responsable : SENS Pierre
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>




#define NB_PAGES 10//00000// On peut créer jusqu'à pow(2,50) pages dans une server consacré à cette tâche 
// mais nous allons tester dans le cadre du projet des serveurs offrants le stockage de 10 /00000 pages/données au plus


/**
 * Lors de l'allocation de pages pour le stockage de données
 * une structure comme celle-ci sera initialisée pour y contenir les informations
 **/
struct page{
	void* begin;			// Adresse de départ
	char* name;				// Si page vide/non utilisée, name = NULL
	struct client* lects;	// Lecteur(s) en cours de lecture
	int writer;
	struct page *next;		// Liste chaînée avec la page suivante indiquée
	pthread_mutex_t * mutex;
};


struct unusedPages{
	struct page *list;
	int nbUnused;
	pthread_mutex_t * mutex;
};
struct unusedPages* unused;


struct usedPages{
	struct page *list;
	int nbUsed;
	pthread_mutex_t * mutex;
};
struct usedPages* used;


struct client{
	int sock;
	struct client *next;
};


/** Fonctions d'initialisation de la mémoire serveur **/
int init_persistant();

/** Fonctions de tests sur les pages et users **/
struct page* getPage(char *name);
int isReader(struct page* p, int sock);
int removeReader(struct page* p, int sock);

/** Fonctions traitants les requêtes **/
char* p_create(char* name, char* val, int sock);
char* p_access_read(char *name, int sock);
char* p_access_readwrite(char *name, int sock);
char* p_release_read(char* name, int sock);
char* p_release_readwrite(char* name, int sock, char* buf);


