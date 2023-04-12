// ppm.c
// Řešení IJC-DU1, příklad b) 28.2.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0


#include "ppm.h"

/*
 * Načtení PPM Obrázku do struktury ppm
*/

struct ppm *ppm_read(const char *filename){
    char buff[16];
    struct ppm *obr;
    FILE *fp = fopen(filename, "rb");
    if(!fp){
        warning("ppm_read: Soubor nelze otevřít.\n");
        return(NULL);
    }
    if (!fgets(buff, sizeof(buff), fp)) {
        warning("ppm_read: Soubor nelze přečíst.\n");
        fclose(fp);
        return(NULL);
    }
    if(buff[0] != 'P' && buff[1] != '6'){
        warning("ppm_read: Špatný formát souboru.\n");
        fclose(fp);
        return(NULL);
    }
    int x, y, barva;
    if (fscanf(fp, "%d %d\n%d\n",&x,&y,&barva) != 3){
        warning("ppm_read: Špatný formát souboru.\n");
        fclose(fp);
        return(NULL);
    }
    obr = malloc(3*x*y+sizeof(struct ppm));
    if(obr == NULL){
        warning("ppm_read: Chyba v alokaci.\n");
        fclose(fp);
        return(NULL);
    }
    obr->xsize = x;
    obr->ysize = y;

    int znak;
    for (size_t i = 0;(znak = fgetc(fp) )!= EOF;i++) {
        obr->data[i] = znak;
    }
    
    fclose(fp);
    return obr;
}

/*
 * Uvolnění struktury ppm
*/
void ppm_free(struct ppm *p){
     if (p != NULL){
        free(p);
     }
}
