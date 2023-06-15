//
//  main.cpp
//  CS300-HW4
//
//  Created by Mert Coskuner on 8.05.2023.
//

#include <iostream>
#include "BST.h"
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "strutils.h"
#include "HashTables.h"

using namespace std;
using namespace std::chrono;

void file_read_and_create_BST_tree(string filename, BinarySearchTree<string> & new_BST_tree , ofstream & output ){
    ifstream  myFile(filename) ;
    string line;
    vector<string> variables;
    string myvar ;
    int index = 0 ;
    while(getline(myFile, line)){
        while(index != string::npos){
            index = line.find(" ") ;
            myvar = line.substr(0,index) ;
            line = line.substr(index+1 , line.length());
            variables.push_back(myvar) ;
        }
        new_BST_tree.insert(UpperString(variables[0]),UpperString(variables[1]),UpperString(variables[2]),variables[3]);

        variables.clear() ;
        index = 0 ;
    }
    myFile.close();

}


void  unique_word_count_for_ht(string word, vector<string> &uniqueness){
    bool check =true;
    for(int i= 0 ; i< uniqueness.size() ; i++){
        if(word == uniqueness[i] ){
            check= false;
        }
    }
    if(check){
        uniqueness.push_back(word);
    }

}


void file_read_and_create_HASH_TABLE(string filename,HashTable<string> &table){
    
    auto start = high_resolution_clock::now();
    vector<string> uniqueness;
    ifstream  myFile(filename) ;
    string line;
    vector<string> variables;
    string myvar ;
    int index = 0 ;
    while(getline(myFile, line)){
        while(index != string::npos){
            index = line.find(" ") ;
            myvar = line.substr(0,index) ;
            line = line.substr(index+1 , line.length());
            variables.push_back(myvar) ;
        }
        string collapse  = variables[0]+ variables[1] ;
        unique_word_count_for_ht(collapse , uniqueness );
        table.insert(UpperString(variables[0]),UpperString(variables[1]),UpperString(variables[2]),variables[3],uniqueness.size());
        variables.clear() ;
        index = 0 ;
    }
    cout<<endl;
    cout<<endl;
    cout<< "After preprocessing, the contact count is "<< uniqueness.size() << ". Current load ratio is " << (double)uniqueness.size()/ (double)table.array_size_help()<<endl ;
    cout<<endl ;
    cout<<endl; 
    
    myFile.close();
    table.uniq  = uniqueness.size();
}

void search( BinarySearchTree<string> BST,HashTable<string> New_table, ofstream & output ){
    string firstName,lastName, City, phoneNumber;
    string name;


    cout<<"Search for a contact: " ;
    cin.ignore();

    getline(cin, name);
    ToUpper(name);
    bool output_var= false ;
    cout<<endl;

    int index = name.find(" ") ;

        
    firstName = name.substr(0,index) ;
    lastName = name.substr(index+1 , name.length());
    cout<< "Searching an item in the phonebook (BST) . . ."<< endl ;
    cout<<endl;
    
    cout<<"Phonebook: Searching for: "<<"("<< UpperString(firstName) <<" "<< UpperString(lastName)<< ")" <<endl;

    cout<<"===================================="<<endl ;

    
    
    int k = 500;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        BST.find(firstName, lastName,phoneNumber,City,output, output_var);
    }
    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() - start);
    BST.find(firstName, lastName,phoneNumber,City,output, output_var);

    if (output_var){
        cout<< UpperString(firstName)<< " "<< UpperString(lastName)<<" "<< phoneNumber<<" "<< City<<endl ;
        cout<<endl;
        
        cout<<"BST Search Time: " <<BSTTime.count() / k<<endl;
        cout<<endl;

    }
    else{
        cout<<"Name not found!"<<endl;
        cout<<"BST Search Time: " <<"0"<<endl ;
        cout<<endl;
 

    }

   
    
    
    cout<< "Searching an item in the phonebook (HashTable) . . ."<< endl ;

    cout<<"Phonebook: Searching for: "<<"("<< UpperString(firstName) <<" " << UpperString(lastName)<< ")" <<endl;

    
    cout<<"===================================="<<endl ;
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        New_table.find(firstName, lastName,phoneNumber,City);
    }
    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() - start);
    New_table.find(firstName, lastName,phoneNumber,City);

    if(New_table.find(firstName, lastName,phoneNumber,City) != false ){
        
       
        cout<< UpperString(firstName)<< " "<< UpperString(lastName)<<" "<< phoneNumber<<" "<< City<<endl ;
        cout<<endl;
        cout<<"Hash Table Search Time: " <<HTTime.count() / k<<endl;
        cout<<"Speed up: "<< BSTTime/HTTime<<endl;
        cout<<endl;

    }
    else{
        cout<<"Name not found!"<<endl;
        cout<<endl;
        cout<<"Hash Table Search Time: " <<"0"<<endl;
        cout<<"Speed up: "<< "0";
        cout<<endl;
    }

    

}

void AddContact(BinarySearchTree<string> & BST,HashTable<string> &New_table){
    string firstName,lastName, City, phoneNumber;
    cout<< "Enter the information of the contact to be added:" <<endl;
    cout<<"Name: ";
    cin>> firstName>> lastName;
    ToUpper(firstName);
    ToUpper(lastName);
    cout<< endl;
    cout<<"Tel: ";
    cin>> phoneNumber ;
    cout<< endl;
    cout<<"City: ";
    cin>> City ;
    ToUpper(City);
    cout<< endl;
    cout<<"Adding an item to the phonebook BST . . ."<<endl;
    auto start_BST = high_resolution_clock::now();
    BST.insert(firstName, lastName, phoneNumber, City);
    auto stop_BST = high_resolution_clock::now();
    cout<<"===================================="<<endl ;
    cout<<"Contact has been added successfully to the BST"<<endl;
    cout<< endl;
    cout<< endl;
    cout<<"Adding an item to the phonebook (Hashtable)  . . ."<<endl;
    auto start_Hashtable = high_resolution_clock::now();
    New_table.insert(firstName, lastName, phoneNumber, City, New_table.uniq);
    auto stop_Hashtable = high_resolution_clock::now();
    cout<<"===================================="<<endl ;
    cout<<"Contact has been added successfully to the Hashtable"<<endl;
    cout<< endl;
    auto time_BST =duration_cast<nanoseconds>(stop_BST- start_BST);
    cout<<"Adding a contact to the Binary Tree took " <<time_BST.count()<<" nanoseconds. . ." <<endl;
    auto time_Hashtable =duration_cast<nanoseconds>(stop_Hashtable- start_Hashtable);
    cout<<"Adding a contact to the Hashtable took " <<time_Hashtable.count()<<" nanoseconds. . ." <<endl;
    cout<<"Speed up: "<< time_BST.count()/time_Hashtable.count()<<endl;
}
void DeleteContact_BST(BinarySearchTree<string> & BST ,HashTable<string> &table,ofstream & output ){
    string firstname,  lastname,phoneNumber,  city;
    
    cout<<"Deleting an item from the phonebook . . ."<<endl ;
    
    cout<<"Enter the fullname of the contact to be deleted: " ;
    cin>>firstname>>lastname ;
    ToUpper(firstname);
    ToUpper(lastname);
    cout<<endl;
    bool outputvar =false;


    BST.find(firstname, lastname, phoneNumber,  city, output, outputvar );

    if(outputvar && table.find(firstname, lastname,phoneNumber,city) != false ){
        auto start_BST = high_resolution_clock::now();
        BST.remove(firstname,lastname);
        auto stop_BST = high_resolution_clock::now();
        auto time_BST =duration_cast<nanoseconds>(stop_BST- start_BST);
        cout << "Deleted succcessfully. . .";
        cout<<endl;
        auto start_Hashtable = high_resolution_clock::now();
        table.remove(firstname,lastname,"","");
        auto stop_Hashtable = high_resolution_clock::now();
        auto time_Hashtable =duration_cast<nanoseconds>(stop_Hashtable- start_Hashtable);
        cout<<"Deletion from the Binary Tree took "<< time_BST.count()<< " nanoseconds. . ."<<endl ;
        cout <<endl;
        cout<<"Deletion from the Hashtable took "<< time_Hashtable.count()<< " nanoseconds. . ."<<endl ;
        cout <<endl;
  
    }
    else{
        cout<< "Not found" <<endl ;
        cout<<endl;
    }

}


int main(){
    string filename;
    HashTable<string> New_table("not found",53) ;
    BinarySearchTree<string> BST("-1")  ;
    ofstream  output;
    
    cout<<"Enter the file name: " ;
    cin>>filename;
    file_read_and_create_BST_tree( filename, BST , output );
    file_read_and_create_HASH_TABLE(filename, New_table);
    
    int choice =0  ;

    while(choice != 4 ){
        cout<<"Choose which action to perform from 1 to 6:"<<endl;
        cout<<"1 - Search a phonebook contact"<<endl;
        cout<<"2 - Adding a phonebook contact"<<endl;
        cout<<"3 - Deleting a phonebook contact"<<endl;
        cout<<"4 - Press 4 to exit"<<endl ;
        cin>>choice;
        cout <<endl;
        cout <<endl;
        if(choice == 1){
            search(BST,New_table,output);
            
        }
        else if(choice == 2 ){
            AddContact(BST,New_table);
            
        }
        else if(choice == 3 ){
            DeleteContact_BST(BST ,New_table,output );
        }
    }
    
    return 0;
    
}
