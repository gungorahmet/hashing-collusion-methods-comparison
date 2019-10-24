/* ***********************************************************************
 *    Author:       Ahmet Gungor
 *    Description:  Comparison of hashing and resolving with
 *
 *                  - Chaining
 *                  - Double Hashing
 *                  - Linear Probing
 *                  - Quadratic Probing
 *                  
 *    Start Date        : 22.10.2019
 *    Last Updated Date : 24.10.2019
 *
 */
 
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

bool is_prime_num(int);
int bind_from_file();
void draw_menu(int);
int hash_word(char[36]);
int hash_num(int);
void resolver_func(int, string);

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

bool is_prime_num(int sayi)
{
    for(int i = 2; i < sayi; i++)
    {
        if (sayi % i == 0)
            return false;
    }
    return true;
}

int bind_from_file()
{
    ifstream file;
    file.open("dictionary_tr_en.txt");
    while(file.good())
    {
        dictionary_file_full += file.get();
    }
    dictionary_file_full[dictionary_file_full.length()-1] = '\0';
    
    for (int i = 0; dictionary_file_full[i] != '\0'; i++)
        if (dictionary_file_full[i] == '\n')
            word_count++;
            
    optimum_value = word_count * 1.5;
    
    while(is_prime_num(optimum_value) == false)
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
                      "5.) Exit"
                     };
                      
    cout<<endl<<"\tMain Menu"<<endl;
    cout<<"   ------------------"<<endl;
    
    for (int i = 0; i < 5; i++)
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
int hash_word(char word[36])
{
    long sum = 0;
    
    for(int i = 0; i < strlen(word); i++)
        sum += (int)word[i];
    
    return sum % optimum_value;
}
int hash_num(int number)
{
    return (number * 2 + 1) % optimum_value;
}

void resolver_func(int choice, string resolver_type)
{
    
    int alloc_memory = optimum_value;
    if (choice == 0)
    {
        alloc_memory *= 2;
    }

    Unit table[alloc_memory];
    int second_base = optimum_value; // For Chaining
    
    string local_English_tmp,local_Turkish_temp;
    int first_base = 0;
    
    for(int i = 0; i < word_count; i++)
    {
        local_English_tmp = "";
        local_Turkish_temp = "";
        for(int j = 0; j < 36; j++)
        {
            local_English_tmp += dictionary_file_full[first_base];
            first_base++;
        }
        int k = 35;
        for(; local_English_tmp[k] == ' '; k--)
        {
        }
        local_English_tmp.resize(k + 1);
        
        while(dictionary_file_full[first_base] != '\n')
        {
            local_Turkish_temp+=dictionary_file_full[first_base];
            first_base++;
            if(dictionary_file_full[first_base] == '\0')
                break;
        }
        first_base++;
        
        strcpy(tmpEnglish,local_English_tmp.c_str());
        strcpy(tmpTurkish,local_Turkish_temp.c_str());
        
        if(table[hash_word(tmpEnglish)].full == true)
            collusion_count++;
        
        if(table[(hash_word(tmpEnglish))].full == false)
        {
            strcpy(table[(hash_word(tmpEnglish))].English,tmpEnglish);
            strcpy(table[(hash_word(tmpEnglish))].Turkish,tmpTurkish);
            table[(hash_word(tmpEnglish))].full = true;
        }
        else
        {
            if (choice == 0)
            {
                strcpy(table[second_base].English,tmpEnglish);
                strcpy(table[second_base].Turkish,tmpTurkish);
                table[second_base].full = true;
                table[(hash_word(tmpEnglish))].next = second_base;
                second_base++;
            }
            //TODO if (choice == 1) if (choice == 2) if (choice == 3)
        }
    }
    //TODO write_common_func(resolver)
    //ofstream Chaining_Dosya_Yaz("Chaining.bin",ios::binary);
    //Chaining_Dosya_Yaz.write((char *) &table,sizeof(table));
    //Chaining_Dosya_Yaz.close();
}

void resolver_choice(int choice)
{
    
    string resolvers[4] = {"Chaining", 
                           "Quadratic Probing", 
                           "Double Hashing", 
                           "Linear Probing",
                          };
    
    
    
    system("cls");
    cout<<"Process has been started.."<<endl;
    clock_t time_start;
    clock_t time_end;
    double the_time;
    
    time_start = clock();
    
    bind_from_file();
    
    cout<<resolvers[choice]<<" is chosen..."<<endl;
    
    
    //TODO run resolver_func(choice) and run init and result portion.
    //TODO Main part handle with logic.
    
    resolver_func(choice, resolvers[choice]);
    time_end = clock();
    cout<<"Process has been completed."<<endl<<endl;
    the_time = (double)(time_end - time_start) / CLOCKS_PER_SEC;
    cout<<"Taken Time : "<<the_time<<" seconds"<<endl;
    cout<<"Collusion Count : "<<collusion_count<<endl;
    cout<<"Created File Size : "<<sizeof(Unit)*optimum_value*2<<" byte"<<endl<<endl;
}
main()
{
    int choice = 0;
    int get_key;

    char search_word[36];


    while(1)
    {
        system("cls");
        draw_menu(choice);
        get_key = _getch();
        
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

        if (get_key == RIGHT_ARROW || get_key == ENTER)
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
        cout<<"Enter English word from dictionary: ";
        cin>>search_word;
        if (strcmp(search_word, "exit") == 0)
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
