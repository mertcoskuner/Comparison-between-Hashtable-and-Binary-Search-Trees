#ifndef _HASHTABLES_H
#define _HASHTABLES_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "strutils.h"
template <class HashedObj>
class HashTable
{
  public:
    explicit HashTable( const HashedObj & notFound, int size );
    HashTable( const HashTable & rhs ): ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
             array( rhs.array ), currentSize( rhs.currentSize ) { }

    bool find( HashedObj &firstName, HashedObj & lastName, HashedObj & phoneNumber, HashedObj & City ) const;

    void makeEmpty( );
    int nextPrime( int n ); 
    int size_return(); 
    void insert(  const HashedObj &firstName, const HashedObj & lastName, const HashedObj & phoneNumber, const  HashedObj & City, double uniqueness_count )  ;
    void remove( const HashedObj &firstName,const HashedObj & lastName,const HashedObj & phoneNumber, const HashedObj & City);
    void rehash_helper(HashTable<HashedObj> table);
    const HashTable & operator=(  HashTable & rhs );
    int array_size_help(); 
    enum EntryType { ACTIVE, EMPTY, DELETED };
    int uniq; 

    
  
private:
    struct HashEntry
    {
        HashedObj firstName;
        HashedObj lastName;
        HashedObj phoneNumber;
        HashedObj City;
        EntryType info;

         HashEntry( const HashedObj & firstname = HashedObj( ),const HashedObj & lastname = HashedObj( ),const HashedObj & phonenumber = HashedObj( ),const HashedObj & city = HashedObj( ),EntryType i = EMPTY )
                  : firstName( firstname ),lastName(lastname),  phoneNumber(phonenumber), City(city),  info( i ) { }
        
    };
    const HashEntry & operator=(  HashEntry & rhs )//deep copy
    {
        if ( this != &rhs )
        {
            
            if (rhs.isEmpty( ) ){
                return *this;
            }
            
            this->firstName   =  rhs.firstName ;
            this->lastName   =  rhs.lastName  ;
            this->phoneNumber  =  rhs.phoneNumber ;
            this->City   =  rhs.City ;
            this->info =rhs.info;
            
        }
      return *this;
    }
    int array_size ;
    vector<HashEntry> array;
    int currentSize;
    const HashedObj ITEM_NOT_FOUND;

    bool isActive( int currentPos ) const;
    int findPos( const HashedObj &firstName,const HashedObj & lastName,const HashedObj & phoneNumber, const HashedObj & City) const;
    void rehash(int uniqueness_count);
 };

#include "HashTables.cpp"
#endif

