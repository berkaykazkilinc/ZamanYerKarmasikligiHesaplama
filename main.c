#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TEXT_DOSYA "index.txt"


void ZamanKarmasikligi();
int YerKarmasikligi(char deneme[]);
void DosyaKontrol();
void Yazdir();

char yerkarmasikligi_dizi_int[10];
char yerkarmasikligi_dizi_float[10];
char yerkarmasikligi_dizi_char[10];
char yerkarmasikligi_dizi_double[10];
char *birlesik;

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
    // printf("YER KARMASIKLIGI: %s + %s + %s + %s + %d\n",yerkarmasikligi_dizi_double,yerkarmasikligi_dizi_char,yerkarmasikligi_dizi_float,yerkarmasikligi_dizi_int,yer_karmasikligi);
    DosyaKontrol();
    printf("YER KARMASIKLIGI: ");
    Yazdir();
    printf(" %d\n",yer_karmasikligi);
    ZamanKarmasikligi();


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
int YerKarmasikligi(char deneme[])
{
    char *parca;
    char kopya[255];
    int string_boyutu=0;
    int yer_karmasikligi=0;
    strcpy(kopya,deneme);
    parca=strtok(deneme," ");

    if(strcmp(parca,"int")==0 || strcmp(parca,"\tint")==0)      // INT KONTROL
    {
        if(strstr(kopya,"main()")!=NULL)
        {
            return 0;
        }
        else
        {
            int i=0;
            int sol=0,sag=0;
            int uzunluk=0;
            int virgul_sayisi=0;
            uzunluk=strlen(kopya);
            if(strstr(kopya,"[")!=NULL && strstr(kopya,"]")!=NULL)
            {
                for(i=0; i<uzunluk; i++)
                {
                    if(kopya[i]=='[')
                    {
                        sol++;
                    }
                    else if(kopya[i]==']')
                    {
                        sag++;
                    }

                }
                if(sol==2 && sag==2)
                {
                    strcpy(yerkarmasikligi_dizi_int,"4n^2");
                    return 0;
                }
                else
                {
                    strcpy(yerkarmasikligi_dizi_int,"4n");
                    return 0;
                }

            }
            else if(strstr(kopya,",")!=NULL)
            {
                for(i=0; i<uzunluk; i++)
                {
                    if(kopya[i]==',')
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


    }
    if(strcmp(parca,"float")==0 || strcmp(parca,"\tfloat")==0)      // FLOAT KONTROL
    {

        int i=0;
        int sol=0,sag=0;
        int uzunluk=0;
        int virgul_sayisi=0;
        uzunluk=strlen(kopya);
        if(strstr(kopya,"[")!=NULL && strstr(kopya,"]")!=NULL)
        {
            for(i=0; i<uzunluk; i++)
            {
                if(kopya[i]=='[')
                {
                    sol++;
                }
                else if(kopya[i]==']')
                {
                    sag++;
                }

            }
            if(sol==2 && sag==2)
            {
                strcpy(yerkarmasikligi_dizi_float,"4n^2");
                return 0;
            }
            else
            {
                strcpy(yerkarmasikligi_dizi_float,"4n");
                return 0;
            }

        }
        else if(strstr(kopya,",")!=NULL)
        {
            for(i=0; i<uzunluk; i++)
            {
                if(kopya[i]==',')
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
    if(strcmp(parca,"char")==0 || strcmp(parca,"\tchar")==0)        // CHAR KONTROL
    {

        int i=0;
        int sol=0,sag=0;
        int uzunluk=0;
        int virgul_sayisi=0;
        uzunluk=strlen(kopya);
        if(strstr(kopya,"[")!=NULL && strstr(kopya,"]")!=NULL)
        {
            for(i=0; i<uzunluk; i++)
            {
                if(kopya[i]=='[')
                {
                    sol++;
                }
                else if(kopya[i]==']')
                {
                    sag++;
                }

            }
            if(sol==2 && sag==2)
            {
                strcpy(yerkarmasikligi_dizi_char,"n^2");
                return 0;
            }
            else
            {
                strcpy(yerkarmasikligi_dizi_char,"n");
                return 0;
            }

        }
        else if(strstr(kopya,",")!=NULL)
        {
            for(i=0; i<uzunluk; i++)
            {
                if(kopya[i]==',')
                {
                    virgul_sayisi++;
                }
            }
           // printf("virgul sayisi: %d\n",virgul_sayisi);
            yer_karmasikligi=yer_karmasikligi+(virgul_sayisi+1)*1;
        }
        else
        {
            yer_karmasikligi++;
            yer_karmasikligi=yer_karmasikligi*1;
        }



    }
    if(strcmp(parca,"double")==0 || strcmp(parca,"\tdouble")==0)      // DOUBLE KONTROL
    {

        int i=0;
        int sol=0,sag=0;
        int uzunluk=0;
        int virgul_sayisi=0;
        uzunluk=strlen(kopya);
        if(strstr(kopya,"[")!=NULL && strstr(kopya,"]")!=NULL)
        {
            for(i=0; i<uzunluk; i++)
            {
                if(kopya[i]=='[')
                {
                    sol++;
                }
                else if(kopya[i]==']')
                {
                    sag++;
                }

            }
            if(sol==2 && sag==2)
            {
                strcpy(yerkarmasikligi_dizi_double,"8n^2");
                return 0;
            }
            else
            {
                strcpy(yerkarmasikligi_dizi_double,"8n");
                return 0;
            }

        }
        else if(strstr(kopya,",")!=NULL)
        {
            for(i=0; i<uzunluk; i++)
            {
                if(kopya[i]==',')
                {
                    virgul_sayisi++;
                }
            }
         //   printf("virgul sayisi: %d\n",virgul_sayisi);
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
