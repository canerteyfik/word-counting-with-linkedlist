#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<locale.h>
typedef struct n
{
    int adet;
    char kelime[100];
    struct n *next;
} node;
int adet_bul(char kelime[100]);
void yazdir(node *r);
node * basa_ekle(node *r,char kelime[100],int adet);
void araya_ekle(node *iter,char kelime[100],int adet);
void sona_ekle(node *iter,char kelime[100],int adet);
node *sirali_ekle(node *r,char kelime[100],int adet);

int main()
{
    setlocale(LC_ALL,"Turkish");
    char kelime[100];
    node *root=NULL;
    FILE *metin=fopen("metin.txt","r");
    if(metin==NULL){
        printf("*********************************\n");
        printf("*********DOSYA ACILAMADI*********\n");
        printf("*********************************\n");
        return 0;
    }
    while(!feof(metin))
    {
        int adet;
        strcpy(kelime,"");
        fscanf(metin,"%s",kelime);
        //KELIMENIN BOS OLMASI DURUMUNU KONTROL EDER
        if(strcmp(kelime,"")!=0)
        {
            int i;
            //KELIMLENIN HARFLERINI KUCULTUR
            for(i=0; i<strlen(kelime); i++)
            {
                if(kelime[i]>='A' && kelime[i]<='Z')
                {
                    kelime[i]=tolower(kelime[i]);
                }
            }
            adet=adet_bul(kelime);
            root=sirali_ekle(root,kelime,adet);
        }
    }
    yazdir(root);
    fclose(metin);
    return 0;
}
void yazdir(node *r)
{
    node * iter=r;
    int i=1;
    while(iter!=NULL)
    {
        printf("%d  :%d  :%s\n",i,iter->adet,iter->kelime);
        iter=iter->next;
        i++;
    }
}
int adet_bul(char kelime[100])
{
    char kelime_2[100];
    int adet=0;
    FILE *metin=fopen("metin.txt","r");
    while(!feof(metin))
    {
        strcpy(kelime_2,"");
        fscanf(metin,"%s",kelime_2);
        if(strcmp(kelime_2,"")!=0)
        {
            int i;
            for(i=0; i<strlen(kelime_2); i++)
            {
                if(kelime_2[i]>='A' && kelime_2[i]<='Z')
                {
                    kelime_2[i]=tolower(kelime_2[i]);
                }
            }
            if(strcmp(kelime,kelime_2)==0)
            {
                adet++;
            }
        }
    }
    fclose(metin);
    return adet;
}

node * basa_ekle(node *r,char kelime[100],int adet)
{
    node *tmp=(node*)malloc(sizeof(node));
    strcpy(tmp->kelime,kelime);
    tmp->adet=adet;
    tmp->next=r;
    return tmp;
}
void araya_ekle(node *iter,char kelime[100],int adet)
{
    node *tmp=(node*)malloc(sizeof(node));
    strcpy(tmp->kelime,kelime);
    tmp->adet=adet;
    tmp->next=iter->next;
    iter->next=tmp;
}
void sona_ekle(node *iter,char kelime[100],int adet)
{
    node *tmp=(node*)malloc(sizeof(node));
    strcpy(tmp->kelime,kelime);
    tmp->adet=adet;
    iter->next=tmp;
    tmp->next=NULL;
}
node *sirali_ekle(node *r,char kelime[100],int adet)
{
    //EGER LÝSTE BOS ISE YENI BIR DUGUM OLUSTURUR
    if(r==NULL)
    {
        r=(node*)malloc(sizeof(node));
        strcpy(r->kelime,kelime);
        r->adet=adet;
        r->next=NULL;
        return r;
    }
    //EGER SORGULATILAN KELIME ROOT ILE AYNI ISE BASKA ISLEM YAPMADAN GERI DONER
    if(strcmp(r->kelime,kelime)==0)
    {
        return r;
    }
    //LISTENIN SONUNA YADA ITERDEN SONRAKI ELEMAN KELIMEYE ESIT OLANA KADAR LISTEDE ILERLER
    node *iter=r;
    while(iter->next!=NULL && strcmp(iter->next->kelime,kelime)!=0)
    {
        iter=iter->next;
    }
    //EGER KELIME LISTEYE DAHA ONCE EKLENMIS ISE BIR SEY YAPMADAN GERI DONER
    if(iter->next!=NULL)
    {
        if(strcmp(iter->next->kelime,kelime)==0)
        {
            return r;
        }
    }
    //KELIME LISTEDE YOKSA NEREYE EKLENCEGINI TESPIT ETME ISLEMLERI YAPILIR
    iter=r;
    if(adet > r->adet)
    {
        //EGER ADET ILK ELEMANDAN BUYUK ISE BASA EKLENIR DOLAYISIYLA ROOT DEGISIR
        r=basa_ekle(r,kelime,adet);
        return r;
    }
    //LISTENIN SONUNDA KADAR VAYA ADET OLARAK KENDINDEN KUCUK ADETE SAHIP BIR DUGUM BULANA KADAR ILERLER
    while(iter->next!=NULL && iter->next->adet >=adet)
    {
        iter=iter->next;
    }
    if(iter->next==NULL)
    {
        //LISTENIN SONUNA VARILDIYSA ADET SAYISI AZ OLDUGUNDAN SONA EKLENIR
        sona_ekle(iter,kelime,adet);
        return r;
    }
    //EGER ADET SAYISI ORTADA BIR YERE EKLENMESINI GEREKTIRIYOR ISE ORTAYA EKLENIR
    araya_ekle(iter,kelime,adet);
    return r;
}
