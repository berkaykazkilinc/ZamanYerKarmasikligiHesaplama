#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TEXT_DOSYA "index.txt"

void ZamanKarmasikligi();
int YerKarmasikligi(char deneme[]);
void DosyaKontrol();

int main()
{
    char deneme[255];
    int yer_karmasikligi=0;
    FILE *dosya;
    if((dosya=fopen(TEXT_DOSYA,"r"))== NULL)
    {
        printf("Dosya Acilamadi");
        exit(1);
    }
    while(!feof(dosya))
    {
        fgets(deneme,255,dosya);
        yer_karmasikligi+=YerKarmasikligi(deneme);

    }
    printf("YER KARMASIKLIGI: %d\n",yer_karmasikligi);
    //ZamanKarmasikligi();
    //DosyaKontrol();

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
int YerKarmasikligi(char deneme[])
{
    char *parca;
    char kopya[255];
    int string_boyutu=0;
    int yer_karmasikligi=0;
    strcpy(kopya,deneme);
    parca=strtok(deneme," ");

    if(strcmp(parca,"int")==0 || strcmp(parca,"\tint")==0)
    {
        if(strstr(kopya,"main()")!=NULL)
        {
            return 0;
        }
        else
        {
            int i=0;
            int uzunluk=0;
            int virgul_sayisi=0;
            uzunluk=strlen(kopya);
            if(strstr(kopya,",")!=NULL)
            {
                for(i=0; i<uzunluk; i++)
                {
                    if(kopya[i]==',')
                    {
                        virgul_sayisi++;
                    }
                }
                printf("virgul sayisi: %d\n",virgul_sayisi);
                yer_karmasikligi=yer_karmasikligi+(virgul_sayisi+1)*4;
            }
            else
            {
                yer_karmasikligi++;
                yer_karmasikligi=yer_karmasikligi*4;
            }
        }


    }


    return yer_karmasikligi;

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
    if(kontrol==0)
    {
        printf("Dosya Icerigi Bos");
    }
    else
    {
        printf("Dosya Icerigi Mevcut");
    }

}
