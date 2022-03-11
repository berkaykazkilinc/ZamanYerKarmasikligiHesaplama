#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TEXT_DOSYA "index.txt"

void ZamanKarmasikligi();
void YerKarmasikligi();
void DosyaKontrol();

int main()
{
    //ZamanKarmasikligi();
    //YerKarmasikligi();
    DosyaKontrol();

    return 0;
}
void ZamanKarmasikligi()
{
    char deneme[255];
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
    printf("%s\n",deneme);
    int x=0,j=0,z=0;
    x=strlen(deneme);
    for(j=0; j<x-1; j++)
    {
        if(deneme[j]==',')
        {
            z++;
        }
        printf("|||||%d",z);
        printf("%c\n",deneme[0]);

    }


    fclose(dosya);
}
void YerKarmasikligi()
{
    FILE *dosya;
    char deneme[255];
    int string_boyutu=0;
    int yer_karmasikligi=0;
    if((dosya=fopen(TEXT_DOSYA,"r"))== NULL)
    {
        printf("Dosya Acilamadi");
        exit(1);
    }
    while(!feof(dosya))
    {
        fgets(deneme,255,dosya);
        if(strstr(deneme,"int")!=NULL)
        {
            /*string_boyutu=strlen(deneme);
            int i=0;
            for(i=0;i<string_boyutu;i++)
            {
                if(deneme[i]==',');
                {
                    //yer_karmasikligi++;
                }
                printf("%c",deneme[i]);
            }*/
            yer_karmasikligi+=1;
            // yer_karmasikligi=yer_karmasikligi*4;


        }
    }
    yer_karmasikligi=yer_karmasikligi*4;
    printf("%d",yer_karmasikligi);
}
void DosyaKontrol()
{
    FILE *dosya;
    char deneme[255];
    int kontrol=0;
    if((dosya=fopen(TEXT_DOSYA,"r"))== NULL)
    {
        printf("Dosya Acilamadi");
        exit(1);
    }
    fgets(deneme,255,dosya);
    kontrol=strlen(deneme);
    printf("%d",kontrol);
    if(kontrol==0)
    {
        printf("Dosya Icerigi Bos");
    }
    else
    {
        printf("Dosya Icerigi Mevcut");
    }

}
