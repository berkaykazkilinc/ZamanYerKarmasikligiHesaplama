// YASAR BERKAY KAZKILINC 200201019			KAGAN CAN KABA 200201049

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
void HarcananZaman2();
char sonuc_string[255];
char ilk_tutulan[255];
char t_sonuc_string[255];
char t_ilk_tutulan[255];
int sayacx=0;
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
    // harcananZaman();
    HarcananZaman2();
    if(sayacx>0)
    {
        printf("T(N) KARMASIKLIGI: %s %d\n",t_sonuc_string,sayacx);
    }
    else
    printf("T(N) KARMASIKLIGI: %s \n",t_sonuc_string);
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
    else if(strcmp(deneme,"boolen")==0 || strstr(deneme,"(boolen")!=NULL)  //boolen kontrol
    {
        byte=1;

    }
    else if(strcmp(deneme,"short")==0 || strstr(deneme,"(short")!=NULL)  //short kontrol
    {
        byte=2;

    }
    else if(strcmp(deneme,"long")==0 || strstr(deneme,"(long")!=NULL)  //long kontrol
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

void HarcananZaman2()
{
    int for_sayaci=0,cost=0;
    int acilanParantez=0 , kapaliParantez=0;
    int while_sayaci=0;
    FILE *dosya, *kalinanYer;
    dosya = fopen(TEXT_DOSYA, "r");
    char txt[255];
    char kalinan[255];
    while (!feof(dosya))
    {
        fgets(txt,255,dosya);
        if(strstr(txt,"for (")!=NULL)
        {
            for_sayaci++;
            kalinanYer = dosya;
            while (!feof(kalinanYer))
            {
                fgets(kalinan,255,kalinanYer);
                if(strstr(kalinan,"for (") == NULL && (strstr(kalinan, "return") != NULL || strstr(kalinan, "=") != NULL))
                {
                    cost++;
                }
                if (strstr(kalinan, "{") != NULL)
                {
                    acilanParantez += 1;
                }
                if (strstr(kalinan, "}") != NULL)
                {
                    kapaliParantez += 1;
                }
                if(strstr(kalinan,"for (")!=NULL)
                {
                    for_sayaci++;
                }
                if(strstr(kalinan,"while (")!=NULL)
                {
                    while_sayaci++;
                }
                if (kapaliParantez != 0 && acilanParantez == kapaliParantez)
                {
                    sprintf(t_ilk_tutulan," (2n+2)^%d +",for_sayaci);
                    strcat(t_sonuc_string,t_ilk_tutulan);
                    if(while_sayaci>0)
                    {
                        sprintf(t_ilk_tutulan," (n+1)^%d +",while_sayaci);
                        strcat(t_sonuc_string,t_ilk_tutulan);
                    }
                    if(cost>0)
                    {
                        sprintf(t_ilk_tutulan," %d*n +",cost);
                        strcat(t_sonuc_string,t_ilk_tutulan);
                    }
                    cost=0;
                    for_sayaci=0;
                    while_sayaci=0;
                    acilanParantez=0;
                    kapaliParantez=0;
                    break;
                }
            }
        }
        if(strstr(txt,"while (")!=NULL)
        {
            while_sayaci++;
            kalinanYer = dosya;
            while (!feof(kalinanYer))
            {
                fgets(kalinan,255,kalinanYer);
                if(strstr(kalinan,"for (") == NULL && (strstr(kalinan, "return") != NULL || strstr(kalinan, "=") != NULL))
                {
                    cost++;
                }
                if (strstr(kalinan, "{") != NULL)
                {
                    acilanParantez += 1;
                }
                if (strstr(kalinan, "}") != NULL)
                {
                    kapaliParantez += 1;
                }
                if(strstr(kalinan,"for (")!=NULL)
                {
                    for_sayaci++;
                }
                if(strstr(kalinan,"while (")!=NULL)
                {
                    while_sayaci++;
                }
                if (kapaliParantez != 0 && acilanParantez == kapaliParantez)
                {
                    sprintf(t_ilk_tutulan," (n+1)^%d +",while_sayaci);
                    strcat(t_sonuc_string,t_ilk_tutulan);
                    if(for_sayaci>0)
                    {
                        sprintf(t_ilk_tutulan," (2n+2)^%d +",for_sayaci);
                        strcat(t_sonuc_string,t_ilk_tutulan);
                    }
                     if(cost>0)
                    {
                        sprintf(t_ilk_tutulan," %d*n +",cost);
                        strcat(t_sonuc_string,t_ilk_tutulan);
                    }
                    cost=0;
                    for_sayaci=0;
                    while_sayaci=0;
                    acilanParantez=0;
                    kapaliParantez=0;
                    break;
                }
            }
        }
        if((strstr(txt,"for (") == NULL && strstr(txt,"while (") == NULL) && (strstr(txt, "return") != NULL || strstr(txt, "=") != NULL))
        {
            sayacx++;
        }

    }
}

