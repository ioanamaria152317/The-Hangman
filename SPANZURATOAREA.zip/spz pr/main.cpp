#include <iostream>
#include <fstream>   ///pt fisiere
#include <conio.h>   /// pt getch
#include <windows.h>
#include <winbgim.h>
#include <graphics.h>
#include <cstring>    ///pt caractere
#include <cstdlib>
#include <ctime>      ///pt rand
#include "mmsystem.h"
using namespace std;
void categorii();
void meniuPrincipal();
void version();
int sunet=1;
char numeFisier[100];
char caractereFolosite[100];
char literanoua[5];
const int maxGreseli=6;
int nrCuvinte;
int fr[123]; ///vector de frecventa pt nr de aparitii

struct punct
{
    int x,y;
};
struct dreptunghi
{
    punct SS,DJ;
};
struct Buton
{
    dreptunghi D;
    int culoare;
    char text[30];
} Buton[5];
bool apartine(int x,int y,int x1,int y1,int x2,int y2)
{
    return x>=x1 && x<=x2 && y>=y1 && y<=y2;
}
void play(char nume[1000])
{
    if(sunet)
    {
        PlaySound(nume, NULL, SND_FILENAME|| SND_ASYNC || SND_LOOP);
    }
    else
    {
        PlaySound(0,0,0);
    }
}
void Loading_Game()      //bara de loading
{
    play("start.wav");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(RED);
    outtextxy(399,300, "SPANZURATOAREA");
    rectangle(280,390,480,410);
    setcolor(RED);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(RED);
    outtextxy(379,386,"LOADING");
    settextstyle(MONO_FONT, HORIZ_DIR, 3);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(RED);
    outtextxy(390,600,"PROIECT REALIZAT DE");
    outtextxy(390,630,"PAULIUC IOANA MARIA");

    for(int i=0; i<=200; i++)
    {
        line(280+i,390,280+i,410);
        delay(40);
    }
    cleardevice();
}
void toString(int x,char s[3])   //convertirea in char pt outtext
{
    if(x<6)
    {
        x=x+48;
        s[0]=x;
        s[1]='\0';
    }
}
void WaitForClick(int &x,int &y)   //functia pentru click
{
    int clicked=0;
    while(!clicked)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            clicked=1;
        }
    }
}
void gameplay()                   //functia pentru joc, tema 1
{
    readimagefile("fundal.jpg",0,0,800,800);
    srand(time(NULL));   ///ca sa dea un alt cuvant de fiecare data
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(100, 50, 250, 55);      ///pt spanzuratoare
    bar(250,50,255,70);
    bar(100, 50, 105, 350);
    bar(50, 350, 180, 355);
    ifstream fin(numeFisier);
    int i, randomIndex=1+rand()%nrCuvinte; ///nr generat random intre 1 si nr de cuvinte din fisier

    char selectie[101],cuvant[101],criptare[202],criptareFaraSpatii[101];
    char caractereFolosite[100];
    strcpy(caractereFolosite, " ");
    caractereFolosite[0]=' '; ///un spatiu la inceput
    caractereFolosite[1]='\0'; ///final de sir

    for(i=0; i<=122; i++)  ///pt resetarea vectorului la inceputul fiecarui joc
    {
        fr[i]=0;
    }
    for(i=1; i<=randomIndex; i++) ///citim linie cu linie pana la randomIndex
    {
        fin.getline(selectie,101);
    }

    int lungime=strlen(selectie);
    for(i=0; i<lungime*2; i++)
    {
        if(i%2==1)
        {
            if(isalpha(selectie[i/2])) ///verificam daca e litera
                criptare[i]='_';
            else
                criptare[i]=selectie[i/2];  ///ex: la capitale cand avem St. ...
        }
        else if(i%2==0)
            criptare[i]=' ';
    }
    criptare[lungime*2]='\0';    ///pentru a marca finalul

    int nrGreseli=0;
    int spanzurat=0;
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    if(lungime<=11)                  //modificarea fontului in functie de lungimea cuvantului
    {
        settextstyle(EUROPEAN_FONT,0,18);
    }
    else
        settextstyle(EUROPEAN_FONT,0,17-(lungime-11)/3);
    setcolor(BLACK);
    setbkcolor(RGB(255,254,231)); ///RED GREEN BLUE
    setfillstyle(SOLID_FILL, RGB(255,254,231));
    bar(0,400,800,800);
    outtextxy(400,600,criptare);

    cout<<nrGreseli<<endl;
    cout<<criptare;
    while(spanzurat==0)
    {
        settextjustify(LEFT_TEXT, LEFT_TEXT);
        settextstyle(EUROPEAN_FONT,0,5);
        outtextxy(200,700,caractereFolosite);
        int c=getch();   ///apasam pe tastatura
        char litera; ///caracter

        if((c>=97 && c<=122) || (c>=65 && c<=90)) ///pt ca in ascii lui a ii coresp 97 si lui z 122; apoi avem pt majuscule, sa le transf in litere mici
        {

            if(c>=65 && c<=90) ///pt majusucule
            {
                c=c+32; ///le transforma in litere mici
                litera= (char) c;
            }
            else
            {
                litera=(char)c;
            }

            if(fr[c]==0)
            {
                if(strchr(selectie, litera)|| strchr(selectie,toupper(litera)) )  ///prima aparitie in cuvant
                {
                    fr[c]++;
                    for(i=0; i<lungime; i++)
                    {
                        if(selectie[i]==litera || selectie[i]==toupper(litera))
                            criptare[2*i+1]=selectie[i];  ///punem litera la locul ei
                        play("literacorecta.wav");
                    }
                    system("cls"); ///face sa dispara ce aveam pe fereastra curenta si apar modif
                    cout<<nrGreseli<<endl;
                    char nrGreseliText[2];
                    toString(nrGreseli,nrGreseliText);
                    setcolor(BLACK);
                    outtextxy(600,500,nrGreseliText);
                    settextjustify(CENTER_TEXT, CENTER_TEXT);

                    if(lungime<=11)
                    {
                        settextstyle(EUROPEAN_FONT,0,18);
                    }
                    else
                        settextstyle(EUROPEAN_FONT,0,17-(lungime-11)/3);
                    setcolor(BLACK);
                    setbkcolor(RGB(255,254,231)); ///RED GREEN BLUE
                    setfillstyle(SOLID_FILL, RGB(255,254,231));
                    bar(0,400,800,800);
                    outtextxy(400,600,criptare);
                    cout<<criptare<<endl;
                    for(i=0; i<lungime; i++)
                    {
                        criptareFaraSpatii[i]=criptare[2*i+1];
                    }
                    criptareFaraSpatii[lungime]='\0';
                    if(strcmp(selectie,criptareFaraSpatii)==0) ///compara ordinea alfabetica si nu tb sa fie vreo dif
                    {
                        play("start.wav");
                        cout<<"Ai Castigat!"<<endl;
                        setcolor(BLACK);
                        settextstyle(EUROPEAN_FONT,0,3);
                        outtextxy(600,500,nrGreseliText);
                        outtextxy(670,500,"greseli");
                        strcpy(caractereFolosite, "");
                        outtextxy(393,670,"Ai castigat!"); ///yayy
                        spanzurat=1; ///se termina while-ul
                    }

                }
                else
                {
                    fr[c]++;
                    char literanoua[5]; // pt strcat
                    literanoua[0]=c;
                    literanoua[1]=' ';
                    literanoua[2]='\0';
                    strcat(caractereFolosite,literanoua);
                    nrGreseli++;
                    system("cls");
                    cout<<nrGreseli<<endl;
                    settextjustify(CENTER_TEXT, CENTER_TEXT);
                    if(lungime<=11)
                    {
                        settextstyle(EUROPEAN_FONT,0,18);
                    }
                    else
                        settextstyle(EUROPEAN_FONT,0,17-(lungime-11)/3);
                    setcolor(BLACK);
                    setbkcolor(RGB(255,254,231)); ///RED GREEN BLUE
                    setfillstyle(SOLID_FILL, RGB(255,254,231));
                    bar(0,400,800,800);
                    outtextxy(400,600,criptare);
                    cout<<criptare;
                    setfillstyle(SOLID_FILL, BLACK);
                    setlinestyle(SOLID_LINE,0,6);
                    if(nrGreseli==1)             //se deseneaza partile corpului in functie de numarul de greseli
                    {
                        fillellipse(250,100,30,30);
                        play("cap.wav");
                    }
                    else if(nrGreseli==2)
                    {
                        bar(248,130,253,250);
                        play("trunchi.wav");
                    }
                    else if(nrGreseli==3)
                    {
                        line(250,250,200,310);
                        play("mana1.wav");
                    }
                    else if(nrGreseli==4)
                    {
                        line(250,250,300,310);
                        play("mana2.wav");
                    }
                    else if(nrGreseli==5)
                    {
                        line(250,150,200,210);
                        play("picior1.wav");
                    }
                    if(nrGreseli==maxGreseli)
                    {
                        line(250,150,300,210);
                        play("picior2end.wav");
                        spanzurat=1;
                        settextjustify(LEFT_TEXT, LEFT_TEXT);
                        settextstyle(EUROPEAN_FONT,0,4);
                        outtextxy(200,670,caractereFolosite);
                        cout<<endl<<"Ai Pierdut! Cuvantul era: "<<selectie<<"!""";
                        strcpy(caractereFolosite, "");
                        outtextxy(100,450,"Cuvantul era");
                        outtextxy(348,450,selectie);
                        settextjustify(CENTER_TEXT, CENTER_TEXT);
                        settextstyle(MONO_FONT,0,6);
                        outtextxy(600,350,"YOU LOST!");
                    }
                }
            }
            else
            {
                cout<<"Ai folosit litera deja!"<<endl;
            }
        }
        else
        {
            cout<<endl<<"CARACTER NEPERMIS"<<'\n';
        }
    }
    Buton[2].D.SS.x = 210;
    Buton[2].D.DJ.x = 538;
    Buton[2].D.SS.y = 715;
    Buton[2].D.DJ.y = 760;
    setbkcolor(RGB(189, 188, 168));
    bar(Buton[2].D.SS.x, Buton[2].D.SS.y, Buton[2].D.DJ.x, Buton[2].D.DJ.y);
    settextstyle(MONO_FONT,0,6);
    setcolor(BLACK);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    strcpy(Buton[2].text, "PLAY AGAIN");
    outtextxy(375, 750, Buton[2].text);
    int clickedbuton=0;
    while(!clickedbuton)
    {
        int x,y;
        WaitForClick(x,y);
        if(apartine(x,y,210,720,530,750))
        {
            clickedbuton=1;
            categorii();
        }
    }
}
void categorii()                //functia pentru categorii, tema 1
{
    int clickedCategorie=0;
    strcpy(caractereFolosite, " ");
    readimagefile("categorii.jpg",0,0,800,800);
    Buton[1].D.SS.x = 335;
    Buton[1].D.DJ.x = 466;
    Buton[1].D.SS.y = 732;
    Buton[1].D.DJ.y = 782;
    setbkcolor(RGB(189, 188, 168));
    bar(Buton[1].D.SS.x, Buton[1].D.SS.y, Buton[1].D.DJ.x, Buton[1].D.DJ.y);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(MONO_FONT,0,6);
    setcolor(BLACK);
    strcpy(Buton[1].text, "BACK");
    outtextxy(400, 770, Buton[1].text);
    while (!clickedCategorie)
    {
        int x,y;
        WaitForClick(x,y);
        if(apartine(x,y,335,732,466,782)) //back
        {
            clickedCategorie=1;
            meniuPrincipal();
        }
        if(apartine(x,y,66,158,406,244)) //instrumente
        {
            clickedCategorie=1;
            play("start.wav");
            strcpy(numeFisier,"instrumente.txt"); //mai intai sterge, apoi adauga
            nrCuvinte=37;
            gameplay();
        }
        if(apartine(x,y,67, 279,407, 361)) //capitale
        {
            clickedCategorie=1;
            play("start.wav");
            strcpy(numeFisier,"capitalele lumii.txt");
            nrCuvinte=111;
            gameplay();
        }
        if(apartine(x,y,65,395,406,479)) //craciun
        {
            clickedCategorie=1;
            play("start.wav");
            strcpy(numeFisier,"craciun.txt");
            nrCuvinte=31;
            gameplay();
        }
        if(apartine(x,y,64,508,404,598))   //domenii
        {
            clickedCategorie=1;
            play("start.wav");
            strcpy(numeFisier,"domenii.txt");
            nrCuvinte=21;
            gameplay();
        }
        if(apartine(x,y,67,631,405, 716))  //cuvinte diverse
        {
            clickedCategorie=1;
            play("start.wav");
            strcpy(numeFisier,"cuvinteeee.txt");
            nrCuvinte=57;
            gameplay();
        }
        if(apartine(x,y,431,160,768, 244))  //bauturi
        {
            clickedCategorie=1;
            play("start.wav");
            strcpy(numeFisier,"bauturi.txt");
            nrCuvinte=37;
            gameplay();
        }
        if(apartine(x,y,430,275,767,361)) //genuri muzicale
        {
            clickedCategorie=1;
            play("start.wav");
            strcpy(numeFisier,"genuri muzicale.txt");
            nrCuvinte=24;
            gameplay();
        }
        if(apartine(x,y,430,391,770,480))  //insecte
        {
            clickedCategorie=1;
            play("start.wav");
            strcpy(numeFisier,"Insecte.txt");
            nrCuvinte=24;
            gameplay();
        }
        if(apartine(x,y,431,512,771,596))  //animale
        {
            clickedCategorie=1;
            play("start.wav");
            strcpy(numeFisier,"Animale.txt");
            nrCuvinte=43;
            gameplay();
        }
        if(apartine(x,y,430,632,770,714))  //sporturi
        {
            clickedCategorie=1;
            play("start.wav");
            strcpy(numeFisier,"Sporturi.txt");
            nrCuvinte=41;
            gameplay();
        }
    }
}
void meniuPrincipal()           //meniu principal, tema 1
{
    int clickedButton=0;
    readimagefile("maniu.jpg",0,0,800,800);
    Buton[1].D.SS.x = 5;
    Buton[1].D.DJ.x = 120;
    Buton[1].D.SS.y = 20;
    Buton[1].D.DJ.y = 60;
    setbkcolor(RGB(189, 188, 168));
    bar(Buton[1].D.SS.x, Buton[1].D.SS.y, Buton[1].D.DJ.x, Buton[1].D.DJ.y);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(MONO_FONT,0,6);
    setcolor(BLACK);
    strcpy(Buton[1].text, "BACK");
    outtextxy(70,50, Buton[1].text);
    while (!clickedButton)
    {
        int clickedButton=0;
        int x,y;
        WaitForClick(x,y);
        if(apartine(x,y,5,20,120,60))  //back
        {
            clickedButton=1;
            version();
        }
        if (apartine(x,y,227,240,570,325)) //start
        {
            clickedButton=1;
            categorii();
        }
        if(apartine(x,y,227,379,572,471))   //reguli
        {
            clickedButton=1;
            readimagefile("reguli.jpg",0,0,800,800);
            Buton[1].D.SS.x = 650;
            Buton[1].D.DJ.x = 780;
            Buton[1].D.SS.y = 732;
            Buton[1].D.DJ.y = 770;
            setbkcolor(RGB(189, 188, 168));
            bar(Buton[1].D.SS.x, Buton[1].D.SS.y, Buton[1].D.DJ.x, Buton[1].D.DJ.y);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(MONO_FONT,0,6);
            setcolor(BLACK);
            strcpy(Buton[1].text, "BACK");
            outtextxy(715,768, Buton[1].text);
            int clickedBack=0;
            while(!clickedBack)
            {
                int clickedBack=0;
                int x,y;
                WaitForClick(x,y);
                if(apartine(x,y,650,732,780,770))
                {
                    clickedBack=1;
                    meniuPrincipal();
                }
            }
        }
        if(apartine(x,y,228,518,571,606))     //setari
        {
            clickedButton=1;
            readimagefile("sunet1.jpg",0,0,800,800);
            Buton[1].D.SS.x = 650;
            Buton[1].D.DJ.x = 780;
            Buton[1].D.SS.y = 732;
            Buton[1].D.DJ.y = 770;
            setbkcolor(RGB(189, 188, 168));
            bar(Buton[1].D.SS.x, Buton[1].D.SS.y, Buton[1].D.DJ.x, Buton[1].D.DJ.y);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(MONO_FONT,0,6);
            setcolor(BLACK);
            strcpy(Buton[1].text, "BACK");
            outtextxy(715,768, Buton[1].text);

            int clickedsunet=0;

            while(!clickedsunet)
            {
                int clickedsunet=0;
                int x,y;
                WaitForClick(x,y);

                if (sunet)
                {

                    if(apartine(x,y,241,264,558,528))
                    {
                        clickedsunet=1;
                        sunet=0;
                        readimagefile("sunetoff1.jpg",0,0,800,800);
                        Buton[1].D.SS.x = 650;
                        Buton[1].D.DJ.x = 780;
                        Buton[1].D.SS.y = 732;
                        Buton[1].D.DJ.y = 770;
                        setbkcolor(RGB(189, 188, 168));
                        bar(Buton[1].D.SS.x, Buton[1].D.SS.y, Buton[1].D.DJ.x, Buton[1].D.DJ.y);
                        settextjustify(CENTER_TEXT, CENTER_TEXT);
                        settextstyle(MONO_FONT,0,6);
                        setcolor(BLACK);
                        strcpy(Buton[1].text, "BACK");
                        outtextxy(715,768, Buton[1].text);
                        cout<<sunet;
                    }

                }
                else
                {
                    if(apartine(x,y,241,264,558,528))
                    {
                        clickedsunet=1;
                        sunet=1;
                        readimagefile("sunet1.jpg",0,0,800,800);
                        Buton[1].D.SS.x = 650;
                        Buton[1].D.DJ.x = 780;
                        Buton[1].D.SS.y = 732;
                        Buton[1].D.DJ.y = 770;
                        setbkcolor(RGB(189, 188, 168));
                        bar(Buton[1].D.SS.x, Buton[1].D.SS.y, Buton[1].D.DJ.x, Buton[1].D.DJ.y);
                        settextjustify(CENTER_TEXT, CENTER_TEXT);
                        settextstyle(MONO_FONT,0,6);
                        setcolor(BLACK);
                        strcpy(Buton[1].text, "BACK");
                        outtextxy(715,768, Buton[1].text);
                        cout<<sunet;
                    }
                }
                if(apartine(x,y,650,732,780,770))  //back
                {
                    clickedsunet=1;
                    meniuPrincipal();
                }
            }
        }
        if (apartine(x,y,227,657,570,744)) //iesire
        {
            exit(1);
            //return 0;
        }
    }
}
void startHorror()     //functia pentru joc, tema 2
{
    readimagefile("spz.jpg",0,0,800,800);
    strcpy(numeFisier,"horror.txt");
    nrCuvinte=20;
    srand(time(NULL));   ///ca sa dea un alt cuvant de fiecare data
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    bar(100, 50, 250, 55);      ///pt spanzuratoare
    bar(250,50,255,70);
    bar(100, 50, 105, 350);
    bar(50, 350, 180, 355);
    ifstream fin(numeFisier);
    int i, randomIndex=1+rand()%nrCuvinte; ///nr generat random intre 1 si nr de cuvinte din fisier

    char selectie[101],cuvant[101],criptare[202],criptareFaraSpatii[101];
    char caractereFolosite[100];
    strcpy(caractereFolosite, " ");
    caractereFolosite[0]=' '; ///un spatiu la inceput
    caractereFolosite[1]='\0'; ///final de sir

    for(i=0; i<=122; i++)
    {
        fr[i]=0;
    }
    for(i=1; i<=randomIndex; i++) ///citim linie cu linie pana la randomIndex
    {
        fin.getline(selectie,101);
    }

    int lungime=strlen(selectie);
    //memset(criptare, '_', lungime);      ///pune carac pe toata lungimea cuv
    for(i=0; i<lungime*2; i++)
    {
        if(i%2==1)
        {
            if(isalpha(selectie[i/2]))
                criptare[i]='_';
            else
                criptare[i]=selectie[i/2];
        }

        else if(i%2==0)
            criptare[i]=' ';
    }
    criptare[lungime*2]='\0';    ///pentru a marca finalul

    int nrGreseli=0;
    int spanzurat=0;
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    if(lungime<=11)
    {
        settextstyle(EUROPEAN_FONT,0,18);
    }
    else
        settextstyle(EUROPEAN_FONT,0,17-(lungime-11)/3);
    setcolor(RED);
    setbkcolor(BLACK); ///RED GREEN BLUE
    setfillstyle(SOLID_FILL, BLACK);
    bar(300,600,400,400);
    outtextxy(400,600,criptare);

    cout<<nrGreseli<<endl;
    cout<<criptare;
    while(spanzurat==0)
    {
        settextjustify(LEFT_TEXT, LEFT_TEXT);
        settextstyle(EUROPEAN_FONT,0,5);
        outtextxy(200,700,caractereFolosite);
        int c=getch();   ///apasam pe tastatura
        char litera;

        if((c>=97 && c<=122) || (c>=65 && c<=90)) ///pt ca in ascii lui a ii coresp 97 si lui z 122; apoi avem pt majuscule, sa le transf in litere mici
        {

            if(c>=65 && c<=90) ///pt majusucule
            {
                c=c+32; ///le transforma in litere mici
                litera= (char) c;
            }
            else
            {
                litera=(char)c;
            }

            if(fr[c]==0)
            {
                if(strchr(selectie, litera)|| strchr(selectie,toupper(litera)) )  ///prima aparitie in cuv
                {
                    fr[c]++;
                    for(i=0; i<lungime; i++)
                    {
                        if(selectie[i]==litera || selectie[i]==toupper(litera))
                            criptare[2*i+1]=selectie[i];  ///punem litera la locul ei
                        play("literacorecta.wav");
                    }
                    system("cls"); ///face sa dispara ce aveam pe fereastra curenta si apar modif
                    cout<<nrGreseli<<endl;
                    char nrGreseliText[2];
                    toString(nrGreseli,nrGreseliText);
                    setcolor(BLACK);
                    outtextxy(600,500,nrGreseliText);
                    settextjustify(CENTER_TEXT, CENTER_TEXT);

                    if(lungime<=11)
                    {
                        settextstyle(EUROPEAN_FONT,0,18);
                    }
                    else
                        settextstyle(EUROPEAN_FONT,0,17-(lungime-11)/3);
                    setcolor(RED);
                    setbkcolor(BLACK);
                    setfillstyle(SOLID_FILL,BLACK);
                    bar(0,400,800,800);
                    outtextxy(400,600,criptare);
                    cout<<criptare<<endl;
                    for(i=0; i<lungime; i++)
                    {
                        criptareFaraSpatii[i]=criptare[2*i+1];
                    }
                    criptareFaraSpatii[lungime]='\0';
                    if(strcmp(selectie,criptareFaraSpatii)==0) ///compara ordinea alfabetica si nu tb sa fie vreo dif
                    {
                        cout<<"Ai Castigat!"<<endl;
                        play("start.wav");
                        setcolor(RED);
                        settextstyle(EUROPEAN_FONT,0,3);
                        outtextxy(600,500,nrGreseliText);
                        outtextxy(670,500,"greseli");
                        strcpy(caractereFolosite, "");
                        outtextxy(393,670,"Ai castigat!"); ///yayy
                        spanzurat=1; ///se termina while-ul
                    }

                }
                else
                {
                    fr[c]++;
                    char literanoua[5]; // pt strcat
                    strcpy(literanoua,"");
                    literanoua[0]=c;
                    literanoua[1]=' ';
                    literanoua[2]='\0';
                    strcat(caractereFolosite,literanoua);
                    nrGreseli++;
                    system("cls");
                    cout<<nrGreseli<<endl;
                    settextjustify(CENTER_TEXT, CENTER_TEXT);
                    if(lungime<=11)
                    {
                        settextstyle(EUROPEAN_FONT,0,18);
                    }
                    else
                        settextstyle(EUROPEAN_FONT,0,17-(lungime-11)/3);
                    setcolor(RED);
                    setbkcolor(BLACK); ///RED GREEN BLUE
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(0,400,800,800);
                    outtextxy(400,600,criptare);
                    cout<<criptare;
                    setfillstyle(SOLID_FILL, RED);
                    setlinestyle(SOLID_LINE,0,6);
                    if(nrGreseli==1)
                    {
                        fillellipse(250,100,30,30);
                        play("cap.wav");
                    }
                    else if(nrGreseli==2)
                    {
                        bar(248,130,253,250);
                        play("trunchi.wav");
                    }
                    else if(nrGreseli==3)
                    {
                        line(250,250,200,310);
                        play("mana1.wav");
                    }
                    else if(nrGreseli==4)
                    {
                        line(250,250,300,310);
                        play("mana2.wav");
                    }
                    else if(nrGreseli==5)
                    {
                        line(250,150,200,210);
                        play("picior1.wav");
                    }
                    if(nrGreseli==maxGreseli)
                    {
                        line(250,150,300,210);
                        play("picior2end.wav");
                        spanzurat=1;
                        settextjustify(LEFT_TEXT, LEFT_TEXT);
                        settextstyle(EUROPEAN_FONT,0,4);
                        outtextxy(200,670,caractereFolosite);
                        cout<<endl<<"Ai Pierdut! Cuvantul era: "<<selectie<<"!""";
                        strcpy(caractereFolosite, "");
                        outtextxy(100,450,"Cuvantul era");
                        outtextxy(348,450,selectie);
                        settextjustify(CENTER_TEXT, CENTER_TEXT);
                        settextstyle(MONO_FONT,0,6);
                        outtextxy(600,350,"YOU LOST!");
                    }
                }
            }
            else
            {
                cout<<"Ai folosit litera deja!"<<endl;
            }
        }
        else
        {
            cout<<endl<<"CARACTER NEPERMIS"<<'\n';
        }
    }
    Buton[2].D.SS.x = 210;
    Buton[2].D.DJ.x = 538;
    Buton[2].D.SS.y = 715;
    Buton[2].D.DJ.y = 760;
    setbkcolor(RGB(250, 90, 81));
    bar(Buton[2].D.SS.x, Buton[2].D.SS.y, Buton[2].D.DJ.x, Buton[2].D.DJ.y);
    settextstyle(MONO_FONT,0,6);
    setcolor(RED);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    strcpy(Buton[2].text, "PLAY AGAIN");
    outtextxy(375, 750, Buton[2].text);
    int clickedbuton=0;
    while(!clickedbuton)
    {
        int clickedbuton=0;
        int x,y;
        WaitForClick(x,y);
        if(apartine(x,y,210,720,530,750))
        {
            clickedbuton=1;
            version();;
        }
    }
}
void meniuPrincipal2()    //meniu principal, tema 2
{
    readimagefile("START.jpg",0,0,800,800);
    int clickedButton2=0;
    while (!clickedButton2)
    {
        int clickedButton2=0;
        int x,y;
        WaitForClick(x,y);
        if (apartine(x,y,351,358,448,386))
        {
            clickedButton2=1;
            startHorror();
        }
        if(apartine(x,y,343,412,456,439))
        {
            clickedButton2=1;
            readimagefile("REGULI2.jpg",0,0,800,800);
            Buton[1].D.SS.x = 650;
            Buton[1].D.DJ.x = 780;
            Buton[1].D.SS.y = 732;
            Buton[1].D.DJ.y = 770;
            setbkcolor(RGB(189, 188, 168));
            bar(Buton[1].D.SS.x, Buton[1].D.SS.y, Buton[1].D.DJ.x, Buton[1].D.DJ.y);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(MONO_FONT,0,6);
            setcolor(BLACK);
            strcpy(Buton[1].text, "BACK");
            outtextxy(715,768, Buton[1].text);
            int clickedBack2=0;
            while(!clickedBack2)
            {
                int clickedBack2=0;
                int x,y;
                WaitForClick(x,y);
                if(apartine(x,y,650,732,780,770))
                {
                    clickedBack2=1;
                    meniuPrincipal2();
                }
            }
        }
        if(apartine(x,y,345,468,455,496))
        {
            clickedButton2=1;
            readimagefile("sunet2.jpg",0,0,800,800);
            Buton[1].D.SS.x = 650;
            Buton[1].D.DJ.x = 780;
            Buton[1].D.SS.y = 732;
            Buton[1].D.DJ.y = 770;
            setbkcolor(BLACK);
            bar(Buton[1].D.SS.x, Buton[1].D.SS.y, Buton[1].D.DJ.x, Buton[1].D.DJ.y);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            settextstyle(MONO_FONT,0,6);
            setcolor(RED);
            strcpy(Buton[1].text, "BACK");
            outtextxy(715,768, Buton[1].text);

            int clickedsunet1=0;

            while(!clickedsunet1)
            {
                int clickedsunet1=0;
                int x,y;
                WaitForClick(x,y);

                if (sunet)
                {

                    if(apartine(x,y,241,264,558,528))
                    {
                        clickedsunet1=1;
                        sunet=0;
                        readimagefile("sunetoff2.jpg",0,0,800,800);
                        Buton[1].D.SS.x = 650;
                        Buton[1].D.DJ.x = 780;
                        Buton[1].D.SS.y = 732;
                        Buton[1].D.DJ.y = 770;
                        setbkcolor(BLACK);
                        bar(Buton[1].D.SS.x, Buton[1].D.SS.y, Buton[1].D.DJ.x, Buton[1].D.DJ.y);
                        settextjustify(CENTER_TEXT, CENTER_TEXT);
                        settextstyle(MONO_FONT,0,6);
                        setcolor(RED);
                        strcpy(Buton[1].text, "BACK");
                        outtextxy(715,768, Buton[1].text);
                    }
                }
                else
                {
                    if(apartine(x,y,241,264,558,528))
                    {
                        clickedsunet1=1;
                        sunet=1;
                        readimagefile("sunet2.jpg",0,0,800,800);
                        Buton[1].D.SS.x = 650;
                        Buton[1].D.DJ.x = 780;
                        Buton[1].D.SS.y = 732;
                        Buton[1].D.DJ.y = 770;
                        setbkcolor(BLACK);
                        bar(Buton[1].D.SS.x, Buton[1].D.SS.y, Buton[1].D.DJ.x, Buton[1].D.DJ.y);
                        settextjustify(CENTER_TEXT, CENTER_TEXT);
                        settextstyle(MONO_FONT,0,6);
                        setcolor(RED);
                        strcpy(Buton[1].text, "BACK");
                        outtextxy(715,768, Buton[1].text);
                        cout<<sunet;
                    }
                }
                if(apartine(x,y,650,732,780,770))
                {
                    clickedsunet1=1;
                    meniuPrincipal2();
                }
            }
        }
        if(apartine(x,y,362,572,447,604))
        {
            clickedButton2=1;
            version();
        }
        if(apartine(x,y,352,518,453,547))
        {
            clickedButton2=1;
            exit(1);
        }
    }
}
void version()             //alegerea temei
{
    readimagefile("spanzuratoarea.jpg",0,0,800,800);
    for(int i=0; i<=122; i++)
    {
        fr[i]=0;
    }
    int x,y;
    WaitForClick(x,y);
    int clickedVersion=0;
    while(!clickedVersion)
    {
        int clickedVersion=0;
        if(apartine(x,y,131,477,670,508))
        {
            clickedVersion=1;
            meniuPrincipal();
        }
        if(apartine(x,y,174,563,621,592))
        {
            clickedVersion=1;
            meniuPrincipal2();
        }
    }
}
int main()
{
    initwindow(800,800);
    Loading_Game();
    delay(200);
    version();
    getch();
    closegraph();
    return 0;
}
