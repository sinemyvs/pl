#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ANAHTAR_SOZCUK 6
#define MAX_SATIR_UZUNLUGU 300


#define TIP_ALPHA 1
#define TIP_DIGIT 2
#define TIP_PUNCT 3
#define TIP_SPACE 4
#define TIP_UNDERLINE 5
#define TIP_UNARY 6
#define TIP_COMMENT 7
#define TIP_PREPROCESS 8
#define TIP_CLOSE 9

#define SOZCUKTIP_KONTROL 1
#define SOZCUKTIP_DATA 2
#define SOZCUKTIP_OZEL 3

#define ISLEMTIP_BILINMIYOR 1
#define ISLEMTIP_KONTROL 2
#define ISLEMTIP_TANIMLAMA 3
#define ISLEMTIP_ATAMA 4
#define ISLEMTIP_YORUM 5
#define ISLEMTIP_ONISLEM 6
#define ISLEMTIP_FONKSIYON 7
#define ISLEMTIP_BLOKSONU 8
#define ISLEMTIP_DONGU 9
#define ISLEMTIP_KOSUL 10
#define ISLEMTIP_SORGU 11
#define ISLEMTIP_CAGIRMA 12
#define ISLEMTIP_FONKSIYON_SONU 13


//#define ZAMANKARMASIKLIGI_

#define KONTROL_FOR 1
#define KONTROL_WHILE 2
#define KONTROL_DO 3
#define KONTROL_IF 4
#define KONTROL_ELSE 5
#define KONTROL_RETURN 6
#define KONTROL_CONTINUE 7
#define KONTROL_BREAK 8
#define KONTROL_FONKSIYON 9

//typedef enum  {Alpha = 0, Digit = 1, Punct = 2, Space = 3}KARAKTERTIP;


char sozcuk[100];
int satirKodAcikMi = 0;
char tanimlayicilar[][10] = {"int","char","double","float","signed","unsigned","void","short","long",""};
char kontrolSozcukleri[][10] = {"for","while","do","if","else","switch","case","return","continue","break",""};
//char esitlikler[][]={"=","-=","+=","*=","/=","%=",""};

int islemTipi=ISLEMTIP_BILINMIYOR;
char cCumlesi[300];

//int stackParantez[1000];

char Tn[1000];
char Sn[1000];
int Snsayi=0;
int Snparantez=0;
int maxDongu=0;
int snDongu=0;
int SnFaktor[10]= {0,0,0,0,0,0,0,0,0,0};
char fonksiyonIsmi[100];

/***************************/

char dosyaAdi[100];
FILE *dosyaPtr ;
char dosyaSatiri[300]="";
int dosyaAcikMi=0;
int satirPtr;
char On[10];
int Onfaktor=0;


int dosyaOku()
{

    printf("dosya adi : ");
    scanf("%s",&dosyaAdi);
    printf("%s\n",dosyaAdi);

    dosyaPtr = fopen(dosyaAdi,"r");

    if(dosyaPtr==NULL)
    {
        printf("Dosya acilirken hata meydana geldi.\n");
        return 0;
    }
    dosyaAcikMi=1;
}


int dosyaAcik()
{

    return dosyaAcikMi;
}

int dosyaKapat()
{
    fclose(dosyaPtr);
    dosyaAcikMi=0;
}

int dosyaSatirOku()
{
    if(fscanf(dosyaPtr,"%[^\n]\n",dosyaSatiri)==EOF)
    {
        dosyaAcikMi=0;
        return 0;
    }
    satirPtr=0;
}


void dosySatirYaz()
{
    printf("%s\n",dosyaSatiri);
}

/**************************/

char hataCumlesi[100]="";
int hataVarMi=0;

void hatakayit(char* mesaj )
{
    if(dosyaAcik())
    {
        strcpy(hataCumlesi,mesaj);
        hataVarMi=1;
    }
}

void hatakayit2(char* s,char c)
{

    char buffer[100];
    sprintf(buffer,"%s  : %c",s,c);
    hatakayit(buffer);
}

int hataVar()
{
    return hataVarMi;
}

void hataYaz()
{
    printf("\n %s \n",hataCumlesi);
}

/**************************/

int stack[1000];
int stackUzunluk=0;

void stackEkle(int islem)
{

    stack[stackUzunluk++] = islem;
    stack[stackUzunluk] = 0;
}


int stackCikar()
{

    if(stackUzunluk==0)
    {
        hatakayit("programda hata var");
        return;

    }
    return stack[--stackUzunluk] ;
}

/**************************/

void TnEkle(char* ek)
{

    strcat(Tn,ek);

}

void TnRecursionEkle()
{
    char buffer[10];
    int recurse= recursiveGetir();
    if(recurse==1)
    {
        TnEkle("+n");

    }
    if(recurse>1)
    {
        sprintf(buffer,"+%d^n",recurse);
        TnEkle(buffer);
    }
}

void SnOlustur(char* ek)
{

    strcat(Sn,ek);
}

void SnSifirla()
{
    strcpy(Sn,"");
    for(int i=0; i<10; i++)
    {
        SnFaktor[i]=0;
    }

}

void OnOlustur()
{
    if(Onfaktor>1)
    {
        printf("O(n) = %d^n\n",Onfaktor);

    }
    else if(maxDongu>1)
    {

        printf("O(n) = n^%d\n",maxDongu);
    }
    else if(maxDongu==1||Onfaktor==1)
    {
        printf("O(n) = n\n");
    }
    else
    {

        printf("O(n) = 1\n");
    }
    Onfaktor=0;

}

/****************************/

char getChar()
{

    return dosyaSatiri[satirPtr];
}

void sonraki()
{

    satirPtr++;
}

void boslukAtla()
{
    cCumlesiEkle(' ');
    while(dosyaAcik())
    {
        char c=getChar();

        if(isspace(c)==0 && c!=0 )
        {
            return;
        }
        if(c==0 )
        {
            dosyaSatirOku();
        }
        else
        {
            sonraki();
        }
    }
}

int karakterTipBul(char karakter)
{
    if(karakter=='_')
    {
        return TIP_UNDERLINE;
    }
    if(karakter=='+'||karakter=='-')
    {
        return TIP_UNARY;
    }
    if(karakter=='#')
    {
        return TIP_PREPROCESS;
    }
    if(karakter=='/')
    {
        return TIP_COMMENT;
    }
    if(karakter=='}')
    {
        return TIP_CLOSE;
    }
    if(isalpha(karakter)!=0)
    {
        return TIP_ALPHA;
    }
    if(isdigit(karakter)!=0)
    {
        return TIP_DIGIT;
    }
    if(ispunct(karakter)!=0)
    {
        return TIP_PUNCT;
    }
    if(isspace(karakter)!=0)
    {
        return TIP_SPACE;
    }
}

void isimAl()
{
    int ptr = 0;
    char c= getChar();
    while(isalnum(c)|| c=='_')
    {
        sozcuk[ptr++]=c;
        sonraki();
        cCumlesiEkle(c);
        c=getChar();
    }
    sozcuk[ptr]=0;

}

void isimKopyala(char* s)
{
    strcpy(s,sozcuk);
}

/*****************/


int recursiveler=0;

void recursiveSifirla()
{
    Onfaktor =recursiveler;
    recursiveler=0;
}

void fonkIsimAta(char* s)
{
    strcpy(fonksiyonIsmi,s);
}

char* fonksiyonIsmiGetir()
{
    return fonksiyonIsmi;
}

void fonksiyonIsmiYaz()
{
    printf("fonksiyon adi = %s\n",fonksiyonIsmiGetir());
}

int recursiveMi()
{
    if(strcmp(fonksiyonIsmi,sozcuk)==0)
    {
        return 1;
    }
    return 0;
}

void recursiveArttir()
{
    recursiveler++;
}

int recursiveGetir()
{
    return recursiveler;
}

/*****************/

void sayiAl()
{
    int ptr = 0;
    char c= getChar();
    while(isdigit(c))
    {
        sozcuk[ptr++]=c;
        sonraki();
        c=getChar();

    }
    sozcuk[ptr]=0;
}

void noktalamaAl()
{
    int ptr = 0;
    char c= getChar();
    while(ispunct(c))
    {
        sozcuk[ptr++]=c;
        sonraki();
        c=getChar();
    }
    sozcuk[ptr]=0;
}

int sozcukOku()
{
    char c=getChar();

    switch(karakterTipBul(c))
    {

    case TIP_ALPHA:
        isimAl();
        break;

    case TIP_DIGIT:
        sayiAl();
        break;

    case TIP_PUNCT:
        noktalamaAl();
        break;

    }
}

void sozcukYaz()
{

    printf("%s\n",sozcuk);

}


int sozcukTipi()
{

    int i=0;
    while(kontrolSozcukleri[i][0]!=0)
    {
        if(strcmp(sozcuk,kontrolSozcukleri[i])==0)
        {
            return SOZCUKTIP_KONTROL;
        }
        i++;
    }
    i=0;
    while(tanimlayicilar[i][0]!=0)
    {
        if(strcmp(sozcuk,tanimlayicilar[i])==0)
        {
            return SOZCUKTIP_DATA;
        }
        i++;
    }
    return SOZCUKTIP_OZEL;

}

void islemTipiAta(int tip)
{

    islemTipi = tip;

}

int islemTipiGetir()
{

    return islemTipi;

}

void cCumlesiBaslat(char * s)
{
    if (s==NULL)
    {

        strcpy(cCumlesi,sozcuk);
    }
    else
    {

        strcpy(cCumlesi,s);
    }
}

void cCumlesiEkle(char karakter)
{

    char array[2];
    array[0]=karakter;
    array[1]=0;
    strcat(cCumlesi,array);
}

/*******************/

int karakterKontrolu(char karakter)
{

    char c=getChar();
    if(c==karakter)
    {
        return 1;
    }
    return 0;
}

int karakterBulunduMu(char karakter)
{
    int b = karakterKontrolu(karakter);
    if (b == 0)
    {
        hatakayit2("aranan karakter bulunamadı ",karakter);
    }
    return b;
}

int karaktereGit(char karakter)
{

    char c;
    while (dosyaAcik())
    {
        c =getChar();
        if(c!=0)
        {
            cCumlesiEkle(c);
        }
        if(c==karakter)
        {
            return 1;
        }
        if (c==0)
        {
            dosyaSatirOku();
        }
        else
        {
            sonraki();
        }
    }
    hatakayit2("aranan karakter bulunamadı ",karakter);
}


int IsimBul()
{
    char c;
    while (dosyaAcik())
    {
        c =getChar();
        if(c!=0)
        {
            cCumlesiEkle(c);
        }
        if(isalpha(c)!=0)
        {
            isimAl();
            return 1;
        }
        if(c==';')
        {
            return 0;
        }
        if (c==0)
        {
            dosyaSatirOku();
        }
        else
        {
            sonraki();
        }
    }

    return 0;
}

/*************/

void onIslem()
{

    islemTipiAta(ISLEMTIP_ONISLEM);
    cCumlesiBaslat(dosyaSatiri);
    dosyaSatirOku();

}

void yorumIslem()
{

    islemTipiAta(ISLEMTIP_YORUM);

    sonraki();
    char c=getChar();

    if(c=='/')
    {
        cCumlesiBaslat(dosyaSatiri);
        dosyaSatirOku();
        return;
    }
    else if (c=='*')
    {
        sonraki();
        karaktereGit('*');
        sonraki();
        karakterBulunduMu('/');
    }
    else
    {
        hatakayit("aranan karakter bulunamadı");
    }

}


struct KontrolOpr
{
    char sozcuk[10];
    int islem;
    int blok;
};

struct KontrolOpr kontrolIslemleri [] =
{

    {"for",KONTROL_FOR,1},
    {"while",KONTROL_WHILE,1},
    {"do",KONTROL_DO,1},
    {"if",KONTROL_IF,1},
    {"else",KONTROL_ELSE,1},
    {"return",KONTROL_RETURN,0},
    {"continue",KONTROL_CONTINUE,0},
    {"break",KONTROL_BREAK,0},
    {"",0,0}

};


struct KontrolOpr kontrolIslemTipi()
{

    int i=0;
    while(kontrolIslemleri[i].sozcuk[0] != 0 )
    {
        if(strcmp(sozcuk,kontrolIslemleri[i].sozcuk)==0)
        {

            return kontrolIslemleri[i];
        }
        i++;
    }
    return ;

}

void recursiveBul()
{

    while(dosyaAcik())
    {
        if(IsimBul())
        {
            boslukAtla();
            if(karakterBulunduMu('('))
            {
                cCumlesiEkle('(');
                if(recursiveMi())
                {
                    recursiveArttir();
                }
            }
        }
        else
        {
            break;
        }
        sonraki();

    }
}


void kontrolIslemi()
{
    islemTipiAta(ISLEMTIP_KONTROL);
    struct KontrolOpr kontrol = kontrolIslemTipi();

    if(kontrol.blok==1)
    {
        stackEkle(kontrol.islem);
        recursiveSifirla();
    }

    switch(kontrol.islem)
    {
    case KONTROL_FOR :
        islemTipiAta(ISLEMTIP_DONGU);
        boslukAtla();
        karakterBulunduMu('(');
        karaktereGit(')');
        sonraki();
        boslukAtla();
        karaktereGit('{');
        TnEkle("n*(");
        Snparantez++;
        snDongu=1;

        break;

    case KONTROL_WHILE :
        islemTipiAta(ISLEMTIP_DONGU);
        boslukAtla();
        karakterBulunduMu('(');
        karaktereGit(')');
        boslukAtla();
        karaktereGit('{');
        TnEkle("log(n)+");
        SnOlustur("log(g)+");
        break;

    case KONTROL_DO :
        islemTipiAta(ISLEMTIP_DONGU);
        boslukAtla();
        karaktereGit('{');
        TnEkle("n*(");
        Snparantez++;
        snDongu=1;
        break;

    case KONTROL_IF :
        islemTipiAta(ISLEMTIP_KOSUL);
        boslukAtla();
        karakterBulunduMu('(');
        //karaktereGit(')');
        //boslukAtla();
        karaktereGit('{');

        break;

    case KONTROL_ELSE :
        islemTipiAta(ISLEMTIP_KOSUL);
        boslukAtla();
        karaktereGit('{');
        break;

    case KONTROL_RETURN :
        boslukAtla();

        while(dosyaAcik())
        {
            char c=getChar();
            if(c==';')
            {
                break;
            }

            if(IsimBul())
            {
                boslukAtla();
                if(karakterKontrolu('('))
                {
                    if(recursiveMi())
                    {
                        recursiveArttir();
                    }
                }
            }
            else
            {
                break;
            }
            sonraki();
        }
        //karaktereGit(';');
        TnEkle("+1");
        break;

    case KONTROL_CONTINUE :
        boslukAtla();
        karaktereGit(';');
        break;

    case KONTROL_BREAK :
        boslukAtla();
        karaktereGit(';');
        break;
    default :
        break;
    }
    sonraki();
    if(Snparantez>maxDongu)
    {
        maxDongu=Snparantez;
    }

}


struct DataYapisi
{
    char sozcuk[10];
    int boyut;
};
struct DataYapisi dataTurleri [] =
{

    {"int",sizeof(int)},
    {"char",sizeof(char)},
    {"double",sizeof(double)},
    {"float",sizeof(float)},
    {"signed",sizeof(signed)},
    {"unsigned",sizeof(unsigned)},
    {"long",sizeof(long)},
    {"short",sizeof(short)},
    {"",0}

};

int dataBoyu()
{
    int i=0;
    while (dataTurleri[i].boyut!=0)
    {
        if(strcmp(dataTurleri[i].sozcuk,sozcuk)==0)
        {
            return dataTurleri[i].boyut;
        }
        i++;
    }
    return -1;
}


void SnEkle(int uzunluk,int faktor)
{
    SnFaktor[faktor]+=uzunluk;
}

void SnYazdir()
{

    char yedek[100];
    for(int i=0; i<10; i++)
    {
        if(SnFaktor[i]!=0)
        {
            if(SnFaktor[i]==1)
            {
                if(i==1)
                {

                    sprintf(yedek,"+n");
                }
                else if(i==0)
                {
                    sprintf(yedek,"1");
                }
                else
                {
                    sprintf(yedek,"+n^%d",i);
                }
            }
            else
            {
                if(i==0)
                {
                    sprintf(yedek,"%d",SnFaktor[i]);
                }
                else if(i==1)
                {

                    sprintf(yedek,"+%d*n",SnFaktor[i]);
                }
                else
                {
                    sprintf(yedek,"+%d*n^%d",SnFaktor[i],i);
                }
            }


            strcat(Sn,yedek);
        }
    }
    if(Sn[0]==0)
    {
        strcpy(Sn,"0");
    }
    printf("S(n) = %s\n",Sn);
}

void TnYaz()
{
    printf("T(n) =  %s \n",Tn);
}


void Tnsifirla()
{
    strcpy(Tn,"");
}



void dataIslemi()
{
    char fonkIsmi[100];
    int factor=0;
    int boyut = dataBoyu();
    boslukAtla();
    isimAl();
    isimKopyala(fonkIsmi);
    boslukAtla();
    char c = getChar();
    if(c=='(')
    {
        fonkIsimAta(fonkIsmi);
        islemTipiAta(ISLEMTIP_FONKSIYON);
        karaktereGit('{');
        stackEkle(KONTROL_FONKSIYON);
        sonraki();
        recursiveler=0;
        Tnsifirla();
        SnSifirla();

    }
    else
    {
        islemTipiAta(ISLEMTIP_TANIMLAMA);
        while(dosyaAcik())
        {
            boslukAtla();
            c=getChar();
            if(c==';')
            {
                SnEkle(boyut,factor);
                sonraki();
                break;
            }
            else if(c==',')
            {
                SnEkle(boyut,factor);
                factor=0;
                if(IsimBul())
                {
                    boslukAtla();
                    if(karakterKontrolu('('))
                    {
                        if(recursiveMi())
                        {
                            recursiveArttir();
                        }
                    }
                }
                cCumlesiEkle(c);
                sonraki();
                boslukAtla();
                isimAl();

                continue;
            }
            else if(c=='[')
            {
                factor++;
            }
            sonraki();
            cCumlesiEkle(c);
        }
    }
}



void ozelIslemi()
{

    boslukAtla();
    char c= getChar();

    if(c=='=')
    {
        boslukAtla();
        islemTipiAta(ISLEMTIP_ATAMA);
        if(IsimBul())
        {
            cCumlesiEkle(c);
            boslukAtla();
            if(karakterKontrolu('('))
            {
                if(recursiveMi())
                {
                    recursiveArttir();
                }
            }
        }
        boslukAtla();
    }
    else if(c=='(')
    {
        boslukAtla();
        islemTipiAta(ISLEMTIP_CAGIRMA);
    }
    karaktereGit(';');
    sonraki();
    TnEkle("+1");
    Snsayi++;

}

void tekilIslem()
{
    islemTipiAta(ISLEMTIP_ATAMA);
    boslukAtla();
    karaktereGit(';');
    sonraki();
    TnEkle("+1");
    Snsayi++;
}

void kapamaIslemi()
{
    char nUst[10];
    sprintf(nUst, "%d", Snparantez);
    char nAlt[10]="n^";
    islemTipiAta(ISLEMTIP_BLOKSONU);
    int islem = stackCikar();

    if (islem==KONTROL_FONKSIYON)
    {
        islemTipiAta(ISLEMTIP_FONKSIYON_SONU);
        TnRecursionEkle();
        recursiveSifirla();
        boslukAtla();
    }
    if(islem==KONTROL_DO)
    {
        boslukAtla();
        TnRecursionEkle();
        isimAl();
        if(strcmp(sozcuk,"while"))
        {
            karaktereGit(';');
        }
        else
        {
            hatakayit("Aranan kelime bulunamadı");
        }
    }
    if((islem==KONTROL_FOR||islem==KONTROL_DO||islem==KONTROL_WHILE))
    {
        boslukAtla();
        TnRecursionEkle();
        TnEkle(")");

    }
    cCumlesiBaslat("}");
    sonraki();
    boslukAtla();
}


void komutAl()
{

    boslukAtla();

    char c = getChar();

    switch(karakterTipBul(c))
    {

    case TIP_UNDERLINE:
    case TIP_ALPHA:
        isimAl();
        cCumlesiBaslat(NULL);
        switch(sozcukTipi())
        {

        case SOZCUKTIP_KONTROL:
            kontrolIslemi();
            break;

        case SOZCUKTIP_DATA:
            dataIslemi();
            break;

        case SOZCUKTIP_OZEL:
            ozelIslemi();
            break;

        }
        break;

    case TIP_UNARY:

        tekilIslem();
        break;

    case TIP_COMMENT:

        yorumIslem();
        break;

    case TIP_PREPROCESS:

        onIslem();
        break;

    case TIP_CLOSE :
        kapamaIslemi();
        break;

    }
}


void islemTipiYaz()
{

    switch(islemTipi)
    {

    case ISLEMTIP_BILINMIYOR :
        printf("bilinmiyor");
        break;
    case ISLEMTIP_KONTROL :
        printf("kontrol");
        break;
    case ISLEMTIP_TANIMLAMA :
        printf("tanimlama");
        break;
    case ISLEMTIP_ATAMA :
        printf("atama");
        break;
    case ISLEMTIP_YORUM :
        printf("yorum");
        break;
    case ISLEMTIP_ONISLEM :
        printf("on islem");
        break;
    case ISLEMTIP_FONKSIYON :
        printf("fonksiyon");
        break;
    case ISLEMTIP_DONGU :
        printf("dongu");
        break;
    case ISLEMTIP_SORGU :
        printf("sorgu");
        break;
    case ISLEMTIP_KOSUL :
        printf("kosul");
        break;
    case ISLEMTIP_BLOKSONU :
        printf("blok bitimi");
        break;
    case ISLEMTIP_CAGIRMA :
        printf("fonksiyon cagirma");
        break;
    case ISLEMTIP_FONKSIYON_SONU :
        printf("fonksiyon bitimi");
        break;
    }
    printf("\n");
}

void komutYaz()
{

    printf("%s =>  ",cCumlesi);
    islemTipiYaz();

}



/***************************/



void test()
{
    dosyaOku();

    while(dosyaAcik())
    {

        dosyaSatirOku();
        dosySatirYaz();

    }
    dosyaKapat();

}
void test2()
{

    dosyaOku();

    while(dosyaAcik())
    {
        boslukAtla();
        sozcukOku();

        sozcukYaz();

    }
    dosyaKapat();

}

void karmasiklikYaz()
{

    printf("\n=================================================\n");
    fonksiyonIsmiYaz();
    TnYaz();
    OnOlustur();
    SnYazdir();
    printf("\n\n");

}

int main()
{

    dosyaOku();

    while(dosyaAcik()&& !hataVar())
    {
        boslukAtla();
        komutAl();
        komutYaz();

        if(!hataVar() && islemTipiGetir()==ISLEMTIP_FONKSIYON_SONU)
        {
            karmasiklikYaz();
            islemTipiAta(ISLEMTIP_BILINMIYOR);
        }

    }

    if(hataVar())
    {
        hataYaz();
    }

    dosyaKapat();



    return 0;
}
