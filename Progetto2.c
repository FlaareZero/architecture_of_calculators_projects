#include <stdlib.h> // librerie standard per variabili e costanti generali
#include <stdio.h> // librerie standard per input-uscitaput
#include <errno.h> // carica la libreria relativa alle macro per gestioni di errore
#include <pthread.h> // carica la libreria relativa alle funzioni di threading dei dati:
#include <stdbool.h> // carica la libreria relativa alle funzioni per il tipo di dati Boolean
#include <unistd.h> // file di header per l'accesso alle API POSIX

#define MAX_VIV 20

#define nazione1_dichiarati 200
#define nazione2_dichiarati 100
#define nazione3_dichiarati 70

// con produzione_viveri intendiamo l'azienda che produrrà i vari viveri.
void *produzione_viveri(void *);
void *nazione1(void *);
void *nazione2(void *);
void *nazione3(void *);

pthread_mutex_t r3_mutex=PTHREAD_MUTEX_INITIALIZER;

int buffer[MAX_VIV];
int contatore = 0;
int entrata = 0;
int uscita = 0;


int nazione1_prodotti = 0; //numero di pacchetti prodotti per la nazione 1
int nazione2_prodotti = 0; //same, ma per la nazione 2
int nazione3_prodotti = 0; //same del same, ma per la nazione 3

void *produzione_viveri(void * id) {

    int c = 0;
    int prossimiPacchetti_prodotti = 0;

    int i = *(int *)id;

    while(true) {

    if (contatore == MAX_VIV) printf("Produzione dei viveri: buffer pieno!\n");

        pthread_mutex_lock(&r3_mutex);

        prossimiPacchetti_prodotti = c++;
        buffer[entrata] = prossimiPacchetti_prodotti;
        entrata = (entrata + 1);
        contatore++;

        printf("Produzione pacchetti in corso..: %d\n", prossimiPacchetti_prodotti);

        pthread_mutex_unlock(&r3_mutex);

        if (prossimiPacchetti_prodotti == MAX_VIV)
        break;


    }
}

void *nazione_1(void * id){


    int prossimiPacchetti_prodotti = 0;

    while(true) {
        while (contatore == 0) printf("\nNazione1: buffer vuoto\n");

        pthread_mutex_lock(&r3_mutex);

        prossimiPacchetti_prodotti = buffer[uscita];
        nazione1_prodotti+=prossimiPacchetti_prodotti;
        uscita = (uscita + 1) ;
        contatore--;
        printf("Nazione numero 1: %d\n", prossimiPacchetti_prodotti);

        pthread_mutex_unlock(&r3_mutex);

        if(nazione1_prodotti>=nazione1_dichiarati/3) {
          break;
        }

     }
}

void *nazione_2(void * id) {

    int prossimiPacchetti_prodotti = 0;


    while(true) {
        while (contatore == 0) printf("\nNazione numero 2: buffer vuoto\n");

        pthread_mutex_lock(&r3_mutex);

        prossimiPacchetti_prodotti = buffer[uscita];
        nazione2_prodotti+=prossimiPacchetti_prodotti;
        uscita = (uscita + 1) ;
        contatore--;
        printf("Nazione 2: %d\n", prossimiPacchetti_prodotti);
        pthread_mutex_unlock(&r3_mutex);

    if (nazione2_prodotti >= nazione2_dichiarati/3) break;


    }

}

void *nazione_3(void * id) {

    int prossimiPacchetti_prodotti = 0;

    while(true) {
        while (contatore == 0) printf("\nNazione 2: buffer vuoto");

        pthread_mutex_lock(&r3_mutex);

        prossimiPacchetti_prodotti = buffer[uscita];
        nazione3_prodotti+=prossimiPacchetti_prodotti;
        uscita = (uscita + 1) ;
        contatore--;
        printf("Nazione numero 2: %d\n", prossimiPacchetti_prodotti);

        pthread_mutex_unlock(&r3_mutex);


    if (nazione3_prodotti >= nazione3_dichiarati/3)
      break;


    }

}

int main() {
    pthread_t thread1, thread2, thread3, thread4;

    int totaleEffettivo = 0;

    int h1=0; //id dell'azionda finanziata da Hyiseria che distribuisce i viveri

    int n1=0; //id della prima nazione

    int n2=1; //id della seconda nazione

    int n3=2; //id della terza nazione

    if (pthread_create(&thread1, NULL,
                        produzione_viveri,
                        (void *)&h1)!=0)
                        perror("pthread_create"), exit(1);

    if (pthread_create(&thread2, NULL,
                        nazione1_prodotti,
                        (void *)&n1)!= 0)
                        perror("pthread_create"), exit(1);

    if (pthread_create(&thread3, NULL,
                        nazione2_prodotti,
                        (void *)&n2)!= 0)
                        perror("pthread_create"), exit(1);
    if (pthread_create(&thread4, NULL,
                        nazione3_prodotti,
                        (void *)&n3)!= 0)
                        perror("pthread_create"), exit(1);


    if (pthread_join(thread1, NULL) != 0)
        perror("pthread_join"), exit(1);
    
    if (pthread_join(thread2, NULL) != 0)
        perror("pthread_join"), exit(1);
    
    if (pthread_join(thread3, NULL) != 0)
        perror("pthread_join"), exit(1);
    
    if (pthread_join(thread4, NULL) != 0)
        perror("pthread_join"), exit(1);
    

        for(int j = 0;j<MAX_VIV;j++) totaleEffettivo+=j;

        int viveri_distribuiti = n1_p+n2_p+n3_p;

        printf("\n--------------------------------");
        printf("\ntotaleEffettivo pacchetti prodotti: %d",totaleEffettivo);
        printf("\nPacchetti distribuiti: %d",viveri_distribuiti);
        printf("\nPacchetti restanti: %d",totaleEffettivo-viveri_distribuiti);
        printf("\n--------------------------------");

        printf("\nNazione1 [pacchetti ricevute]: %d",nazione1_prodotti);
        printf("\nNazione2 [pacchetti ricevute]: %d",nazione2_prodotti);
        printf("\nNazione3 [pacchetti ricevute]: %d\n\n",nazione3_prodotti);

    return 0;

}
