#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#define TEXT_DOSYA "index.txt"



void ZamanKarmasikligi();
int YerKarmasikligi(char deneme[],FILE *kalinan_yer);
int YerKarmasikligiKontrol(int uzunluk,int byte,FILE *kalinan_yer,char dizi[]);
void DosyaKontrol();
void harcananZaman();

char sonuc_string[255];
char ilk_tutulan[255];

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
        fscanf(dosya,"%s",&deneme);
        yer_karmasikligi+=YerKarmasikligi(deneme,dosya);

    }
    DosyaKontrol();
    printf("YER KARMASIKLIGI: %s %d\n",sonuc_string,yer_karmasikligi);
    ZamanKarmasikligi();
    harcananZaman();

    return 0;
}
void ZamanKarmasikligi()
{
    int acilanParantez = 0, kapaliParantez = 0;
    int usSayisi = 0;
    int elde = 0;
    char deneme[50];
    char deneme2[50];
    FILE *dosya, *kalinanYer;
    fpos_t pos;
    if ((dosya = fopen(TEXT_DOSYA, "r")) == NULL)
    {
        printf("Dosya Acilamadi");
        exit(1);
    }
    while (!feof(dosya))
    {
        fscanf(dosya, "%s", &deneme);
        if (strstr(deneme, "for") != NULL || strstr(deneme, "while") != NULL || strstr(deneme, "do") != NULL)
        {
            kalinanYer = dosya;
            while (!feof(kalinanYer))
            {
                fscanf(kalinanYer, "%s", &deneme2);
                if (strstr(deneme2, "{") != NULL)
                {
                    acilanParantez += 1;
                }
                else if (strstr(deneme2, "}") != NULL)
                {
                    kapaliParantez += 1;
                }
                if (kapaliParantez != 0 && acilanParantez == kapaliParantez)
                {
                    elde = kapaliParantez;
                    if (elde >= usSayisi)
                    {
                        usSayisi = elde;
                    }
                    acilanParantez = 0;
                    kapaliParantez = 0;
                    elde = 0;
                }
            }
        }
    }

    if (usSayisi != 0)
    {
        printf("Big-O(n) = O(n^%d)\n", usSayisi);
    }
    else if (usSayisi == 0)
    {
        printf("Big-O(n) = O(1)\n");
    }
    fclose(dosya);
}
int YerKarmasikligi(char deneme[],FILE *kalinan_yer)
{
    int uzunluk=0,i=0,byte=0;
    int yer_karmasikligi=0;
    uzunluk=strlen(deneme);
    if(strcmp(deneme,"int")==0 || strstr(deneme,"(int")!=NULL)  //int kontrol
    {
       byte=4;
    }

    else if(strcmp(deneme,"float")==0 || strstr(deneme,"(float")!=NULL)  //float kontrol
    {
       byte=4;

    }
    else if(strcmp(deneme,"char")==0 || strstr(deneme,"(char")!=NULL)  //char kontrol
    {
        byte=1;

    }

    else if(strcmp(deneme,"double")==0 || strstr(deneme,"(double")!=NULL)  //double kontrol
    {
        byte=8;

    }
    else if(strcmp(deneme,"boolen")==0 || strstr(deneme,"(boolen")!=NULL)  //double kontrol
    {
        byte=1;

    }
    else if(strcmp(deneme,"short")==0 || strstr(deneme,"(short")!=NULL)  //double kontrol
    {
        byte=2;

    }
    else if(strcmp(deneme,"long")==0 || strstr(deneme,"(long")!=NULL)  //double kontrol
    {
        byte=4;
    }
    else
    {
        return 0;
    }
        yer_karmasikligi=YerKarmasikligiKontrol(uzunluk,byte,kalinan_yer,deneme);
        return yer_karmasikligi;

}

int YerKarmasikligiKontrol(int uzunluk,int byte,FILE *kalinan_yer,char dizi[])
{
        char dizi2[255];
        int i=0,virgul_sayisi=0,yer_karmasikligi=0;
        while(dizi[uzunluk]!='\n') //satýr sonuna kadar oku
        {
            fscanf(kalinan_yer,"%s",&dizi2);
            if(strstr(dizi2,"main()"))
            {
                return 0;
            }
            else
            {
                int uzunluk_dizi2=0,sol=0,sag=0;
                uzunluk_dizi2=strlen(dizi2);
                if(strstr(dizi2,"[")!=NULL && strstr(dizi2,"]")!=NULL)
                {

                    for(i=0; i<uzunluk_dizi2; i++)
                    {
                        if(dizi2[i]=='[')
                        {
                            sol++;
                        }
                        else if(dizi2[i]==']')
                        {
                            sag++;
                        }

                    }
                    if(sol==2 && sag==2)
                    {
                        sprintf(ilk_tutulan," %dn^2 +",byte);
                        strcat(sonuc_string,ilk_tutulan);
                    }
                    else
                    {
                        sprintf(ilk_tutulan," %d^n +",byte);
                        strcat(sonuc_string,ilk_tutulan);

                    }

                }
                else if(strstr(dizi2,",")!=NULL)
                {
                    for(i=0; i<uzunluk_dizi2; i++)
                    {
                        if(dizi2[i]==',')
                        {
                            virgul_sayisi++;
                        }
                    }
                    // printf("virgul sayisi: %d\n",virgul_sayisi);
                    yer_karmasikligi=yer_karmasikligi+(virgul_sayisi+1)*byte;
                }
                else
                {
                    yer_karmasikligi++;
                    yer_karmasikligi=yer_karmasikligi*byte;
                }

            }
            return yer_karmasikligi;
        }
}

void DosyaKontrol()
{
    FILE *dosya;
    char deneme[255];
    int kontrol=0;
    if((dosya=fopen(TEXT_DOSYA,"r"))== NULL)
    {
        printf("Dosya Acilamadi\n");
        exit(1);
    }
    fgets(deneme,255,dosya);
    kontrol=strlen(deneme);
    if(kontrol==0)
    {
        printf("Dosya Icerigi Bos\n");
    }
    else
    {
        printf("Dosya Icerigi Mevcut\n");
    }

}

void harcananZaman()
{
    int nSayisi = 0, sabitSayi = 0, eldeSayi = 0;
    int acilanParantez = 0, kapananParantez = 0;
    char deneme[50];
    char deneme2[50];
    char deneme3[50];
    FILE *dosya, *kalinanYer;
    dosya = fopen(TEXT_DOSYA, "r");
    while (!feof(dosya))
    {
        fscanf(dosya, "%s", &deneme);
        if (strstr(deneme, "for") != NULL || strstr(deneme, "while") != NULL || strstr(deneme, "do") != NULL)
        {
            kalinanYer = dosya;
            while (!feof(kalinanYer))
            {
                fscanf(kalinanYer, "%s", &deneme2);
                if (strstr(deneme2, "{") != NULL)
                {
                    acilanParantez += 1;
                }
                else if (strstr(deneme2, "}") != NULL)
                {
                    kapananParantez += 1;
                }
                if (acilanParantez == 0 || acilanParantez != kapananParantez)
                {
                    if (strstr(deneme2, "return") != NULL || strstr(deneme2, "=") != NULL)
                    {
                        nSayisi++;
                    }
                }
            }
        }
    }
    fclose(dosya);
    FILE *dosya2;
    dosya2 = fopen(TEXT_DOSYA, "r");
    while (!feof(dosya2))
    {
        fscanf(dosya2, "%s", &deneme3);
        if (strstr(deneme3, "return") != NULL || strstr(deneme3, "=") != NULL)
        {
            eldeSayi++;
        }
    }
    fclose(dosya2);
    if(nSayisi>0)
    {
    printf("Gecen Zaman: T(N) = %dN + %d\n", nSayisi, (eldeSayi - nSayisi));
    }else if (nSayisi==0)
    {
    printf("Gecen Zaman: T(N) =%d\n",(eldeSayi - nSayisi));
    }

}

