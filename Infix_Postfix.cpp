#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <math.h>

using namespace std;

const int maxlegth=20;
typedef string elementtype;
typedef int position;

class Stos//tablicowa implementacja stosu
{
    elementtype S[maxlegth] ;
    position Top;//szczyt stosu

    public:
        Stos()
        {
            Top=-1;
        }
        void Push(elementtype x)
        {
            if(Top+1<maxlegth)
            {
                Top++;
                S[Top]=x;
            }
        }
        bool Empty()
        {
            if(Top==-1)
                return true;
            else
                return false;
        }
        void Pop()
        {
            if(!Empty())
            {
                Top--;
            }
        }
        elementtype TopElem()
        {
            if(!Empty())
            {
                return S[Top];
            }
            else
                return NULL;
        }
        void Makenull()
        {
            while(Top!=-1)
            {
                Top--;
            }
        }
        void Print()
        {
            int i=Top;
            while(i!=-1)
            {
                cout<<S[i]<<endl;
                i--;
            }
        }
};

bool operand(string x)//sprawdzanie czy dany znak to operand
{
    if(((x.compare("/")) == 0)||((x.compare("+")) == 0)||((x.compare("-")) == 0)||((x.compare("*")) == 0)||((x.compare("^")) == 0)||((x.compare(")")) == 0)||((x.compare("(")) == 0))
        return false;
    else
        return true;
}

int operacja(int x,int y,string opera)//wybór operacji zale¿nie od operatora
{
    if(opera.compare("/")==0)
        return x/y;
    else if(opera.compare("+")==0)
        return x+y;
    else if(opera.compare("-")==0)
        return x-y;
    else if(opera.compare("*")==0)
        return x*y;
    else if(opera.compare("^")==0)
        return pow(x,y);
    else
        return 0;

}
int priorytet(string opera)//przypisanie odpowiedniego priorytetu dla dzia³añ
{
    if(opera.compare("/")==0)
        return 2;
    else if(opera.compare("+")==0)
        return 3;
    else if(opera.compare("-")==0)
        return 3;
    else if(opera.compare("*")==0)
        return 2;
    else if(opera.compare("^")==0)
        return 1;
    else
        return 0;

}

void wart_onp()
{
    Stos *s1 = new Stos();
    string wpis;
    string cos;
    getline (cin,cos);
    getline (cin,wpis);
    vector < string > dane;

    string word = "";
    string x;
    for ( x : wpis)
    {
       if (x == ' ')
       {
           dane.push_back( word );
           word = "";
       }
       else
       {
           word = word + x;
       }

    }

    dane.push_back( word);
    string arg1;
    string arg2;
    int nr1;
    int nr2;
    char buffer[20];
    int buf;
    for (int it =0; it != dane.size(); it++)
    {

        if(operand(dane[it])&&(dane[it].compare("~")!=0))
        {
            s1->Push(dane[it]);
        }
        else if(((dane[it].compare("~")) == 0))
        {

            arg1=s1->TopElem();
            s1->Pop();
            int nr1 = (-atoi(arg1.c_str()));
            itoa(nr1,buffer,10);
            s1->Push(buffer);
        }
        else
        {
            arg2=s1->TopElem();
            s1->Pop();
            int nr2 = (atoi(arg2.c_str()));
            arg1=s1->TopElem();
            s1->Pop();
            int nr1 = (atoi(arg1.c_str()));
            buf=operacja(nr1,nr2,dane[it]);
            itoa(buf,buffer,10);
            s1->Push(buffer);
        }
    }
    cout<<s1->TopElem()<<endl;
}


void na_onp()
{
    Stos *s1 = new Stos();
    string wpis;
    string cos;
    getline (cin,cos);
    getline (cin,wpis);
    vector < string > dane;
    string word = "";
    string x;
    for ( x : wpis)
    {
       if (x == ' ')
       {
           dane.push_back( word );
           word = "";
       }
       else
       {
           word = word + x;
       }
    }
    dane.push_back( word);


    string arg1;
    string arg2;
    int nr1;
    int nr2;
    char buffer[20];
    int buf[20];
    int pojemnosc=0;
    for (int it =0; it != dane.size(); it++)
    {
        if(operand(dane[it])&&((dane[it].compare("~"))!= 0))
        {
            cout<<dane[it]<<" ";
        }
        else if(((dane[it].compare("~"))== 0))
        {
            if(dane[it+1].compare("(")==0)
            {
                s1->Push(dane[it]);
            }
            else
            {
                cout<<dane[it+1]<<" "<<dane[it]<<" ";
                it++;
            }
        }
        else
        {
            if(dane[it].compare("(")==0)
            {
                s1->Push(dane[it]);
            }
            else if(dane[it].compare(")")==0)
            {
                while(s1->TopElem().compare("(")!=0)
                {
                    cout<<s1->TopElem()<<" ";
                    s1->Pop();
                    pojemnosc--;
                }
                s1->Pop();
            }
            else
            {
                if(pojemnosc==0)
                {
                    s1->Push(dane[it]);
                    pojemnosc++;
                    buf[pojemnosc]=priorytet(dane[it]);
                }
                else
                {
                    while((buf[pojemnosc]<=priorytet(dane[it]))&&(pojemnosc>=1))
                    {
                        if(s1->TopElem().compare("(")==0)
                            break;
                        cout<<s1->TopElem()<<" ";
                        s1->Pop();
                        pojemnosc--;
                    }
                    s1->Push(dane[it]);
                    pojemnosc++;
                    buf[pojemnosc]=priorytet(dane[it]);
                }
            }
        }
    }
    while(!s1->Empty())
    {
        cout<<s1->TopElem()<<" "    ;
        s1->Pop();
    }
    cout<<endl;
}


int main()
{
    int s;
    while(1)
    {
        cout<<"Witaj w kalkulatorze onp!"<<endl;
        cout<<"1. Oblicz wartosc wyrazenia w onp."<<endl;
        cout<<"2. Przekonwertuj wyrazenie na onp"<<endl;
        cout<<"3. Wyjscie"<<endl;
    cin>>s;
    switch (s)
    {

        case 1:
            wart_onp();
            break;
        case 2:
            na_onp();
            break;
        case 3:
            exit(0);
        default:
            cout<<"zly numer! wybierz jeszcze raz!"<<endl;
            break;
    }
    }
    return 0;
}
