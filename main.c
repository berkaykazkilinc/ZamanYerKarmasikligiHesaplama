#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#define TEXT_DOSYA "index.txt"



void ZamanKarmasikligi();
int YerKarmasikligi(char deneme[],FILE *kalinan_yer);
void DosyaKontrol();
void Yazdir();
void harcananZaman();

char yerkarmasikligi_dizi_int[10];
char yerkarmasikligi_dizi_float[10];
char yerkarmasikligi_dizi_char[10];
char yerkarmasikligi_dizi_double[10];

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
    // printf("YER KARMASIKLIGI: %s + %s + %s + %s + %d\n",yerkarmasikligi_dizi_double,yerkarmasikligi_dizi_char,yerkarmasikligi_dizi_float,yerkarmasikligi_dizi_int,yer_karmasikligi);
    DosyaKontrol();
    printf("YER KARMASIKLIGI: ");
    Yazdir();
    printf(" %d\n",yer_karmasikligi);
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
    fclose(dosya);
}
int YerKarmasikligi(char deneme[],FILE *kalinan_yer)
{
    int uzunluk=0,i=0;
    int virgul_sayisi=0;
    int yer_karmasikligi=0;
    uzunluk=strlen(deneme);
    if(strcmp(deneme,"int")==0 || strstr(deneme,"(int")!=NULL)  //int kontrol
    {
        char deneme2[255];
        while(deneme[uzunluk]!='\n') //satýr sonuna kadar oku
        {
            fscanf(kalinan_yer,"%s",&deneme2);
            if(strstr(deneme2,"main()"))
            {
                return 0;
            }
            else
            {
                int uzunluk_deneme2=0,sol=0,sag=0;
                uzunluk_deneme2=strlen(deneme2);
                if(strstr(deneme2,"[")!=NULL && strstr(deneme2,"]")!=NULL)
                {

                    for(i=0; i<uzunluk_deneme2; i++)
                    {
                        if(deneme2[i]=='[')
                        {
                            sol++;
                        }
                        else if(deneme2[i]==']')
                        {
                            sag++;
                        }

                    }
                    if(sol==2 && sag==2)
                    {
                        strcpy(yerkarmasikligi_dizi_int,"4n^2");

                    }
                    else
                    {
                        strcpy(yerkarmasikligi_dizi_int,"4n");

                    }

                }
                else if(strstr(deneme2,",")!=NULL)
                {
                    for(i=0; i<uzunluk_deneme2; i++)
                    {
                        if(deneme2[i]==',')
                        {
                            virgul_sayisi++;
                        }
                    }
                    //printf("virgul sayisi: %d\n",virgul_sayisi);
                    yer_karmasikligi=yer_karmasikligi+(virgul_sayisi+1)*4;
                }
                else
                {
                    yer_karmasikligi++;
                    yer_karmasikligi=yer_karmasikligi*4;
                }

            }
            return yer_karmasikligi;
        }
    }
    if(strcmp(deneme,"float")==0 || strstr(deneme,"(float")!=NULL)  //float kontrol
    {
        char deneme2[255];
        while(deneme[uzunluk]!='\n') //satýr sonuna kadar oku
        {
            fscanf(kalinan_yer,"%s",&deneme2);
            if(strstr(deneme2,"main()"))
            {
                return 0;
            }
            else
            {
                int uzunluk_deneme2=0,sol=0,sag=0;
                uzunluk_deneme2=strlen(deneme2);
                if(strstr(deneme2,"[")!=NULL && strstr(deneme2,"]")!=NULL)
                {

                    for(i=0; i<uzunluk_deneme2; i++)
                    {
                        if(deneme2[i]=='[')
                        {
                            sol++;
                        }
                        else if(deneme2[i]==']')
                        {
                            sag++;
                        }

                    }
                    if(sol==2 && sag==2)
                    {
                        strcpy(yerkarmasikligi_dizi_float,"4n^2");

                    }
                    else
                    {
                        strcpy(yerkarmasikligi_dizi_float,"4n");

                    }

                }
                else if(strstr(deneme2,",")!=NULL)
                {
                    for(i=0; i<uzunluk_deneme2; i++)
                    {
                        if(deneme2[i]==',')
                        {
                            virgul_sayisi++;
                        }
                    }
                    // printf("virgul sayisi: %d\n",virgul_sayisi);
                    yer_karmasikligi=yer_karmasikligi+(virgul_sayisi+1)*4;
                }
                else
                {
                    yer_karmasikligi++;
                    yer_karmasikligi=yer_karmasikligi*4;
                }

            }
            return yer_karmasikligi;
        }
    }
    if(strcmp(deneme,"char")==0 || strstr(deneme,"(char")!=NULL)  //char kontrol
    {
        char deneme2[255];
        while(deneme[uzunluk]!='\n') //satýr sonuna kadar oku
        {
            fscanf(kalinan_yer,"%s",&deneme2);
            if(strstr(deneme2,"main()"))
            {
                return 0;
            }
            else
            {
                int uzunluk_deneme2=0,sol=0,sag=0;
                uzunluk_deneme2=strlen(deneme2);
                if(strstr(deneme2,"[")!=NULL && strstr(deneme2,"]")!=NULL)
                {

                    for(i=0; i<uzunluk_deneme2; i++)
                    {
                        if(deneme2[i]=='[')
                        {
                            sol++;
                        }
                        else if(deneme2[i]==']')
                        {
                            sag++;
                        }

                    }
                    if(sol==2 && sag==2)
                    {
                        strcpy(yerkarmasikligi_dizi_char,"n^2");

                    }
                    else
                    {
                        strcpy(yerkarmasikligi_dizi_char,"n");

                    }

                }
                else if(strstr(deneme2,",")!=NULL)
                {
                    for(i=0; i<uzunluk_deneme2; i++)
                    {
                        if(deneme2[i]==',')
                        {
                            virgul_sayisi++;
                        }
                    }
                    //printf("virgul sayisi: %d\n",virgul_sayisi);
                    yer_karmasikligi=yer_karmasikligi+(virgul_sayisi+1)*1;
                }
                else
                {
                    yer_karmasikligi++;
                    yer_karmasikligi=yer_karmasikligi*1;
                }

            }
            return yer_karmasikligi;
        }
    }

    if(strcmp(deneme,"double")==0 || strstr(deneme,"(double")!=NULL)  //double kontrol
    {
        char deneme2[255];
        while(deneme[uzunluk]!='\n') //satýr sonuna kadar oku
        {
            fscanf(kalinan_yer,"%s",&deneme2);
            if(strstr(deneme2,"main()"))
            {
                return 0;
            }
            else
            {
                int uzunluk_deneme2=0,sol=0,sag=0;
                uzunluk_deneme2=strlen(deneme2);
                if(strstr(deneme2,"[")!=NULL && strstr(deneme2,"]")!=NULL)
                {

                    for(i=0; i<uzunluk_deneme2; i++)
                    {
                        if(deneme2[i]=='[')
                        {
                            sol++;
                        }
                        else if(deneme2[i]==']')
                        {
                            sag++;
                        }

                    }
                    if(sol==2 && sag==2)
                    {
                        strcpy(yerkarmasikligi_dizi_double,"8n^2");

                    }
                    else
                    {
                        strcpy(yerkarmasikligi_dizi_double,"8n");

                    }

                }
                else if(strstr(deneme2,",")!=NULL)
                {
                    for(i=0; i<uzunluk_deneme2; i++)
                    {
                        if(deneme2[i]==',')
                        {
                            virgul_sayisi++;
                        }
                    }
                    //  printf("virgul sayisi: %d\n",virgul_sayisi);
                    yer_karmasikligi=yer_karmasikligi+(virgul_sayisi+1)*8;
                }
                else
                {
                    yer_karmasikligi++;
                    yer_karmasikligi=yer_karmasikligi*8;
                }

            }
            return yer_karmasikligi;
        }
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
void Yazdir()
{
    int uzunluk_int=0;
    int uzunluk_float=0;
    int uzunluk_char=0;
    int uzunluk_double=0;
    uzunluk_int=strlen(yerkarmasikligi_dizi_int);
    uzunluk_float=strlen(yerkarmasikligi_dizi_float);
    uzunluk_char=strlen(yerkarmasikligi_dizi_char);
    uzunluk_double=strlen(yerkarmasikligi_dizi_double);
    if(uzunluk_int>0)
    {
        printf("%s +",yerkarmasikligi_dizi_int);
    }

    if(uzunluk_float>0)
    {
        printf(" %s +",yerkarmasikligi_dizi_float);
    }

    if(uzunluk_char>0)
    {
        printf(" %s +",yerkarmasikligi_dizi_char);
    }

    if(uzunluk_double>0)
    {
        printf(" %s +",yerkarmasikligi_dizi_double);
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
    printf("Gecen Zaman: T(N) = %dN + %d\n", nSayisi, (eldeSayi - nSayisi));
}
