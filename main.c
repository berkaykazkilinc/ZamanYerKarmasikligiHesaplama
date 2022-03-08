#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TEXT_DOSYA "index.txt"

void ZamanKarmasikligi();
void YerKarmasikligi();

int main()
{
    ZamanKarmasikligi();


    return 0;
}
void ZamanKarmasikligi(){
 char deneme[50];
    int n=0;
    FILE *dosya;
    fpos_t pos;
    if((dosya=fopen(TEXT_DOSYA,"r"))== NULL)
    {
        printf("Dosya Acilamadi");
        exit(1);
    }
    while(!feof(dosya))
    {
       fscanf(dosya,"%s",&deneme);
       //printf("%s ",deneme);
    if(strstr(deneme,"for(")!=NULL)
    {
        n+=1;
        fgetpos(dosya,&pos);
        printf("Dosyanin aktif konumu: %ld\n", pos);
    }
    if(strstr(deneme,"while(")!=NULL)
    {
        n+=1;
    }
    }
    /*if(strcmp(deneme,"for")==0)
    {
        n+=2;
    }*/
    if(n!=0)
    {
        printf("Big-O(n) = O(n^%d)\n",n);
    }
    printf("%s",deneme);
    fclose(dosya);
}
/*void YerKarmasikligi(){
    FILE *dosya;
    if((dosya=fopen(TEXT_DOSYA,"r"))== NULL)
    {
        printf("Dosya Acilamadi");
        exit(1);
    }
    while(!feof(dosya))
    {
       fscanf(dosya,"%s",&deneme);
       if(strstr(deneme,"int")!=NULL)
       {

       }
    }
}*/
