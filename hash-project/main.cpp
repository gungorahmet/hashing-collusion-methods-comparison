#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define ESC 0x1b
#define ENTER 0xd
#define UP_ARROW 0x48
#define DOWN_ARROW 0x50
#define RIGHT_ARROW 0x4d

using namespace std;

int word_count = 1, optimum_value = 0, collusion_count = 0;
string dictionary_file_full;

// According to the case, characters has max 36 and 68.
// Not requested as pointer.

char tmpEnglish[36], tmpTurkish[68];

class Unit
{
    public:
        char English[36], Turkish[68];
        bool full;
        int next;
        
        Unit()
        {
            next = -1;
            full = false;
        }
};

//void normalize_Turkish_characters(char []);
//void Chaining();
//void Chaining_Oku(char[36]);
//void Quadratic_Probing();
//void Quadratic_Oku(char[36]);
//void Double_Hashing();
//void Double_Oku(char[36]);
//void Linear_Probing();
//void Linear_Oku(char[36]);
bool asal_mi(int);
bool asal_mi(int sayi)
{
    for(int i=2; i<sayi; i++)
    {
        if (sayi%i==0)
            return false;
    }
    return true;
}
//int hash(char[36]);
//int hash2(int);
void draw_menu(int);
int basla();
int basla()
{
    ifstream file;
    file.open("dictionary_tr_en.txt");
    while(file.good())
    {
        dictionary_file_full+=file.get();
    }
    dictionary_file_full[dictionary_file_full.length()-1]='\0';
    
    for (int i=0; dictionary_file_full[i]!='\0'; i++)
        if (dictionary_file_full[i]=='\n')
            word_count++;
            
    optimum_value = word_count * 1.5;
    
    while(asal_mi(optimum_value)==false)
    {
        optimum_value++;
    }
    file.close();
}
void draw_menu(int choice)
{ 
    string menu[5] = {"1.) Chaining", 
                      "2.) Quadratic Probing", 
                      "3.) Double Hashing", 
                      "4.) Linear Probing", 
                      "5.) Cikis"
                     };
                      
    cout<<endl<<"\tMain Menu"<<endl;
    cout<<"   ------------------"<<endl;
    
    for (int i=0; i<5; i++)
    {
        cout<<"  ";

        if (choice == i)
        {
            cout<< (char)16 << " "<< menu[i]<< endl;
        }
        else
        {
            cout<<"  "<<menu[i]<<endl;
        }
    }

}

void resolver_choice(int choice)
{
    
    string resolvers[4] = {"Chaining", 
                           "Quadratic Probing", 
                           "Double Hashing", 
                           "Linear Probing",
                          };
    
    
    
    system("cls");
    cout<<"islem basladi"<<endl;
    clock_t time_start;
    clock_t time_end;
    double the_time;
    
    time_start = clock();
    
    basla();
    
    cout<<resolvers[choice]<<" Secildi..."<<endl;
    
    
    //TODO run resolver_func(choice) and run init and result portion.
	//TODO Main part handle with logic.
    //Chaining();
    time_end = clock();
    cout<<"islem bitti"<<endl;
    the_time = (double)(time_end - time_start) / CLOCKS_PER_SEC;
    cout<<"Olusturma Suresi : "<<the_time<<" saniye"<<endl;
    cout<<"Cakisma Sayisi : "<<collusion_count<<endl;
    cout<<"Olusturulan file Boyutu : "<<sizeof(Unit)*optimum_value*2<<" byte"<<endl;
}
main()
{
    int choice = 0;
    int get_key;
    clock_t time_start;
    clock_t time_end;
    double the_time;
    char search_word[36];


    while(1)
    {
        system("cls");
        draw_menu(choice);
        get_key = getch();
        
        if (get_key == DOWN_ARROW)
        {
            if (choice == 4)
                choice = 0;
            else
                choice++;
        }
        else if (get_key == UP_ARROW)
        {
            if (choice == 0)
                choice = 4;
            else
                choice--;
        }
       else if (get_key == ESC)
           return 0;

        if (get_key==RIGHT_ARROW || get_key==ENTER)
        {
		   if (choice == 4)
           	  return 0;
           	  
            system("cls");
			resolver_choice(choice);
			break;
        }
    }
    while(1)
    {
        cout<<"Kelime Giriniz : ";
        gets(search_word);
        if (strcmp(search_word,"cikis")==0)
            return 0;


      // switch(choice)
      // {
          // case 1:
          // {
              // Chaining_Oku(search_word);
          // }break;
          // case 2:
          // {
              // Quadratic_Oku(search_word);
          // }break;
          // case 3:
          // {
              // Double_Oku(search_word);
          // }break;
          // case 4:
          // {
              // Linear_Oku(search_word);
          // }break;
      // }
    }
}
