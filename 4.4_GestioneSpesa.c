// spesa, lista con inserimento in coda
// usa minimo spazio necessario per il nome
// 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L 50    // Lunghezza MAX nome prodotto

// definisco il tipo lista
typedef struct prodotto{
    float price;
    char name[L];
    struct prodotto *next;
} nodo;

void aggiungi_elemento(nodo** head);
void stampa_lista(nodo** head);

void rimuovi_elemento(nodo** head);
void stampa_scontrino(nodo** head);

void elimina_prodotto(nodo** head);
void svuota_carrello(nodo** head);

int main(){
    nodo *head = NULL;

    int scelta;
    printf("Benvenuto. ");
    do{
        system("CLS");
        printf("Selezionare una scelta:\n");
        printf(" 1 - Inserire prodotto nel carrello.\n");
        printf(" 2 - Stampa a video tutti gli articoli del carrello.\n");
        printf(" 3 - Stampa scontrino.\n");           //           ( + elimino quelli sotto 1 euro).
        printf(" 4 - Elimina un prodotto dal carrello.\n");
        printf("   - - - - - - - - - - - - - - - - - - \n");
        printf(" 9 - Elimina TUTTO dal carrello.\n");
        printf(" 0 - Esci\n");
        printf("Inserire il valore corrispondente alla scelta: ");
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                // Inserire prodotto nel carrello.
                aggiungi_elemento(&head);
                break;
            case 2:
                // Stampa tutti gli articoli nel carrello.
                stampa_lista(&head);
                break;
            case 3:
                // Stampa scontrino ( + elimino quelli sotto 1 euro).
                //rimuovi_elemento(&head);                                           // ---------------------------- OFF
                stampa_scontrino(&head);
                break;  
            case 4:
                elimina_prodotto(&head);
                break;
            case 9:
                svuota_carrello(&head);
                break;
            case 0:
                //Esci
                printf("Arrivederci.\n");
                break;
            default:
                printf("Errore. Il valore inserito non e' valido.\n");
                stampa_scontrino(&head); // stampo prima di perdere tutto
                scelta = 0;
                break;
        }   
    } while(scelta > 0);
    
    svuota_carrello(&head);
    
    return 0;
}

// ------------------------------------------------------------------

void aggiungi_elemento(nodo** head){
    char nome[L];
    float prezzo;
    nodo *p = (nodo *) malloc(sizeof(nodo));
    if(p == NULL){
        printf("Errore nell'allocazione dinamica.");
    }
    printf("Inserire il nome del prodotto: ");
    scanf("%s", nome);
    printf("Prezzo prodotto: ");
    scanf("%f", &prezzo);
    strcpy(p->name, nome);
    p->price = prezzo;
    
    p->next = NULL;
    
    if(*head == NULL){ // primo elemento
        *head = p;
    } else { // qualsiasi altro elemento
        nodo *last;
        last = *head;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = p;
    }
}

void stampa_lista(nodo** head){
    nodo *aux = *head;
    while(aux != NULL){
        printf("%10s\teuro %3.2f\n", aux->name, aux->price);
        aux = aux->next;
    }
    printf("\n\n");
    system("PAUSE");
}

void rimuovi_elemento(nodo** head){
    // rimuovo tutti gli elementi con prezzo sotto 1
    int ok = 0;
    nodo *curr = *head;
    nodo *prev = NULL;
    if(curr == *head && curr->price <= 1){  // primo elemento
        *head = curr->next;
        free(curr);
    }
    while(curr->next != NULL){
        prev = curr;
        curr = curr->next;
        if(curr->price <= 1){ // qualsiasi altro
            prev->next = curr->next;
            free(curr);
        }
    }
    
    if(curr == NULL){
        printf("Curr va a null :)");
    }
    if(ok == 0){
        printf("Non ho trovato il prodotto cercato. ");
    }
    system("PAUSE");
    
}


void stampa_scontrino(nodo** head){
    FILE *scontrino = fopen("files/scontrino.txt", "w");
    float tot=0;
    nodo *aux = *head;
    while(aux != NULL){
        fprintf(scontrino, "%10s\teuro %3.2f\n", aux->name, aux->price);
        tot += aux->price;
        aux = aux->next;
    }
    fprintf(scontrino, "\nTotale: %3.2f euro", tot);
    fclose(scontrino);
    printf("\nHo stampato lo scontrino. ");
    system("PAUSE");
}

void elimina_prodotto(nodo** head){
    char nome[L];
    int ok = 0;
    printf("Inserire il nome del prodotto da eliminare: ");
    scanf("%s", nome);
    
    if(*head == NULL){  // lista vuota
        return;
    }
    nodo *curr = *head;
    nodo *prev = NULL;
    
    // tutti gli altri elementi
    while(curr != NULL){
        if(strcmp(curr->name, nome) == 0){ 
            if(curr == *head){
                *head = curr->next;
                free(curr);
            } else {
                prev->next = curr->next;
                free(curr);
            }
            ok++;
        }
        prev = curr;
        curr = curr->next; 
    }
    if(ok != 0){
        printf("Ho rimosso %d oggetti dalla lista. ", ok);
    } else {
        printf("Non ho trovato l'elemento da eliminare.");
    }
    system("PAUSE");
}

void svuota_carrello(nodo** head){
    nodo *aux = *head;
    printf("Svuoto il carrello ");
    
    while(aux != NULL){
        printf(".");
        *head = aux->next;
        free(aux);
        aux = *head;
    }
    printf(" Ho svuotato il carrello. HEAD = %d\n", *head);
    system("PAUSE");
}