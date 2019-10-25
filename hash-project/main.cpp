/* ***********************************************************************
 *    Author:       Ahmet Gungor
 *    Description:  Comparison of hashing and resolving with
 *
 *                  - Double Hashing
 *                  - Chaining
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
void resolver_func(int);

int word_count = 1, collusion_count = 0;
long int optimum_value = 0;
string dictionary_file_full;

string resolvers[4] = {"Chaining", 
                       "Quadratic Probing", 
                       "Double Hashing", 
                       "Linear Probing",
                      };

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

void normalize_Turkish_characters(char []);
void chaining_reader(char[36], int choice);
void quadratic_reader(char[36], int choice);
void double_reader(char[36], int choice);
void linear_reader(char[36], int choice);

bool is_prime_num(int num)
{
    for(int i = 2; i < num; i++)
    {
        if (num % i == 0)
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

void resolver_func(int choice)
{
    
    int alloc_memory = optimum_value;
    if (choice == 0)
    {
        alloc_memory *= 2;
    }

    Unit table[alloc_memory];
    int second_base = optimum_value; // For Chaining
    
    string local_English_tmp,local_Turkish_tmp;
    int first_base = 0;
    
    for(int i = 0; i < word_count; i++)
    {
        local_English_tmp = "";
        local_Turkish_tmp = "";
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
            local_Turkish_tmp += dictionary_file_full[first_base];
            first_base++;
            if(dictionary_file_full[first_base] == '\0')
                break;
        }
        first_base++;
        
        strcpy(tmpEnglish,local_English_tmp.c_str());
        strcpy(tmpTurkish,local_Turkish_tmp.c_str());
        
        if(table[hash_word(tmpEnglish)].full == true)
            collusion_count++;
        
        if (choice == 0)
        {
            if(table[(hash_word(tmpEnglish))].full == false)
            {
                strcpy(table[(hash_word(tmpEnglish))].English,tmpEnglish);
                strcpy(table[(hash_word(tmpEnglish))].Turkish,tmpTurkish);
                table[(hash_word(tmpEnglish))].full = true;
            }
            else
            {
                    strcpy(table[second_base].English,tmpEnglish);
                    strcpy(table[second_base].Turkish,tmpTurkish);
                    table[second_base].full = true;
                    table[(hash_word(tmpEnglish))].next = second_base;
                    second_base++;
                //TODO if (choice == 1) if (choice == 2) if (choice == 3)
            }
        }
        else if (choice == 1)
        {
            for(long m = 0; m < optimum_value; m++)
            {
                if(table[(hash_word(tmpEnglish) + m * m) % optimum_value].full == false)
                {
                    strcpy(table[(hash_word(tmpEnglish) + m * m) % optimum_value].English, tmpEnglish);
                    strcpy(table[(hash_word(tmpEnglish) + m * m) % optimum_value].Turkish, tmpTurkish);
                    table[(hash_word(tmpEnglish) + m * m) % optimum_value].full = true;
                    break;
                }
            }
        }
        else if (choice == 2)
        {
            if(table[(hash_word(tmpEnglish))].full == false)
            {
                strcpy(table[(hash_word(tmpEnglish))].English,tmpEnglish);
                strcpy(table[(hash_word(tmpEnglish))].Turkish,tmpTurkish);
                table[(hash_word(tmpEnglish))].full = true;
            }
            else
            {
                int num = hash_word(tmpEnglish);
                while(table[num].full == true)
                {
                    num = hash_num(num);
                }
                strcpy(table[num].English, tmpEnglish);
                strcpy(table[num].Turkish, tmpTurkish);
                table[num].full = true;
            }
        }
        else if (choice == 3)
        {
            for(int m = 0; m < optimum_value; m++)
            {
                if(table[(hash_word(tmpEnglish) + m) % optimum_value].full == false)
                {
                    strcpy(table[(hash_word(tmpEnglish) + m) % optimum_value].English, tmpEnglish);
                    strcpy(table[(hash_word(tmpEnglish) + m) % optimum_value].Turkish, tmpTurkish);
                    table[(hash_word(tmpEnglish) + m) % optimum_value].full = true;
                    break;
                }
        }
        }
    }
    string binary_file_name = resolvers[choice] + ".bin";
    
    ofstream write_to_bin_file(binary_file_name.c_str(), ios::binary);
    write_to_bin_file.write((char *) &table,sizeof(table));
    write_to_bin_file.close();
}

void resolver_choice(int choice)
{
    
    system("cls");
    cout<<"Process has been started.."<<endl;
    clock_t time_start;
    clock_t time_end;
    double the_time;
    
    time_start = clock();
    
    bind_from_file();
    
    cout<<resolvers[choice]<<" is chosen..."<<endl;
    
    //TODO Main part handle with logic.
    
    resolver_func(choice);
    time_end = clock();
    cout<<"Process has been completed."<<endl<<endl;
    the_time = (double)(time_end - time_start) / CLOCKS_PER_SEC;
    cout<<"Taken Time : "<<the_time<<" seconds"<<endl;
    cout<<"Collusion Count : "<<collusion_count<<endl;
    
    int file_size = optimum_value;
    if (choice == 0)
        file_size *= 2;
    
    cout<<"Created File Size : "<<sizeof(Unit) * file_size * 2<<" byte"<<endl<<endl;
}
void normalize_Turkish_characters(char word[])
{
     int count = 0;
     int tmp;
     for(int i = 0; i < strlen(word); i++)
     {
       tmp = (int)word[i];
       if(tmp == -4)
         cout<<"u";
       else if(tmp == -3)
         cout<<"i";
       else if(tmp == -2)
         cout<<"s";
       else if(tmp == -16)
         cout<<"g";
       else if(tmp == -25)
         cout<<"c";
       else if(tmp == -10)
         cout<<"o";
       else if(tmp == -57)
         cout<<"C";
       else if(tmp == -48)
         cout<<"G";
       else if(tmp == -35)
         cout<<"I";
       else if(tmp == -42)
         cout<<"O";
       else if(tmp == -34)
         cout<<"S";
       else if(tmp == -36)
         cout<<"U";
       else
         cout<<word[i];
    
       count++;
     }
     cout<<endl;
}

void chaining_reader(char word[36], int choice)
{
    Unit read_unit;
    string binary_file_name = resolvers[choice] + ".bin";
    ifstream read_binary_file(binary_file_name.c_str() , ios::binary);
    read_binary_file.seekg(sizeof(Unit)*hash_word(word));
    read_binary_file.read((char *)&read_unit, sizeof(Unit));
    if (read_unit.full==false)
    {
        cout<<"Word not found"<<endl;
        read_binary_file.close();
        return;
    }
    if(strcmp(word,read_unit.English)==0)
    {
        normalize_Turkish_characters(read_unit.Turkish);
        read_binary_file.close();
        return;
    }
    int num=0;
    while(read_unit.next!=-1)
    {
        num=read_unit.next;
        read_binary_file.seekg(sizeof(Unit)*num);
        read_binary_file.read((char *)&read_unit, sizeof(Unit));
        if(strcmp(word,read_unit.English)==0)
        {
            normalize_Turkish_characters(read_unit.Turkish);
            read_binary_file.close();
            return;
        }
    }
    read_binary_file.close();
    cout<<"Word not found"<<endl;
}

void quadratic_reader(char word[36], int choice)
{
    Unit read_unit;
    string binary_file_name = resolvers[choice] + ".bin";
    ifstream read_binary_file(binary_file_name.c_str() , ios::binary);
    for(int m=0; m<optimum_value; m++)
    {
        read_binary_file.seekg(sizeof(Unit)*((hash_word(word)+m*m)%optimum_value));
        read_binary_file.read((char *)&read_unit, sizeof(Unit));
        if (read_unit.full==false)
        {
            cout<<"Word not found"<<endl;
            read_binary_file.close();
            return;
        }
        if(strcmp(word,read_unit.English)==0)
        {
            normalize_Turkish_characters(read_unit.Turkish);
            read_binary_file.close();
            return;
        }
    }
    read_binary_file.close();
    cout<<"Word not found"<<endl;
}

void double_reader(char word[36], int choice)
{
    Unit read_unit;
    string binary_file_name = resolvers[choice] + ".bin";
    ifstream read_binary_file(binary_file_name.c_str() , ios::binary);
    read_binary_file.seekg(sizeof(Unit)*hash_word(word));
    read_binary_file.read((char *)&read_unit, sizeof(Unit));
    if (read_unit.full==false)
    {
        cout<<"Word not found"<<endl;
        read_binary_file.close();
        return;
    }
    if(strcmp(word,read_unit.English)==0)
    {
        normalize_Turkish_characters(read_unit.Turkish);
        read_binary_file.close();
        return;
    }
    int num=hash_word(word);
    while(1)
    {
        num=hash_num(num);
        read_binary_file.seekg(sizeof(Unit)*num);
        read_binary_file.read((char *)&read_unit, sizeof(Unit));
        if(read_unit.full==false)
        {
            cout<<"Word not found"<<endl;
            read_binary_file.close();
            return;
        }
        if(strcmp(word,read_unit.English)==0)
        {
            normalize_Turkish_characters(read_unit.Turkish);
            read_binary_file.close();
            return;
        }
    }
    read_binary_file.close();
    cout<<"Word not found"<<endl;
}

void linear_reader(char word[36], int choice)
{
    Unit read_unit;
    string binary_file_name = resolvers[choice] + ".bin";
    ifstream read_binary_file(binary_file_name.c_str() , ios::binary);
    for(int m = 0; m < optimum_value; m++)
    {
        read_binary_file.seekg(sizeof(Unit) * ((hash_word(word) + m) % optimum_value));
        read_binary_file.read((char *)&read_unit, sizeof(Unit));
        if (read_unit.full == false)
        {
            cout<<"Word not found"<<endl;
            read_binary_file.close();
            return;
        }
        if(strcmp(word, read_unit.English)==0)
        {
            normalize_Turkish_characters(read_unit.Turkish);
            read_binary_file.close();
            return;
        }
    }
    read_binary_file.close();
    cout<<"Kelime Bulunamadi"<<endl;
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
            
            cout<<"Enter English word from dictionary: ";
            cin>>search_word;

        
            switch(choice)
            {
                case 0:
                {
                    chaining_reader(search_word, choice);
                }break;
                case 1:
                {
                    quadratic_reader(search_word, choice);
                }break;
                case 2:
                {
                    double_reader(search_word, choice);
                }break;
                case 3:
                {
                    linear_reader(search_word, choice);
                }break;
            }
            cout<<endl<<endl<<"Please press any key to exit";
            _getch();
            break;
        }
    }
}
