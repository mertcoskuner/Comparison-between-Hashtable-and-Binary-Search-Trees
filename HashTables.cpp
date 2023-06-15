#include <iostream>
#include "BST.h"
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "strutils.h"
#include"HashTables.h"
#include <cmath>


/**
 * Construct the hash table.
 */
template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound,int size ): ITEM_NOT_FOUND( notFound ), array_size( nextPrime( size ) )
{
    for(int i = 0 ; i< array_size;  i++){array.push_back( HashEntry( "","","","", EMPTY ));}
    
}

template <class HashedObj>
int HashTable<HashedObj>::array_size_help(){
    return array.size();
}

int hash_func(  string  firstname, string  lastname , int tableSize ){
    int sum = 0  ;
    
    for(int i =0 ; i<firstname.length(); i++){
        sum+=(int)firstname[i];
    }
    
    for(int i =  0 ; i< lastname.length(); i++){
        sum+=(int)lastname[i];

    }
    int hash_val =  sum % tableSize ;
    return hash_val;
}

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime( int n )
{
    if ( n == 2 || n == 3 )
        return true;

    if ( n == 1 || n % 2 == 0 )
        return false;

    for ( int i = 3; i * i <= n; i += 2 )
         if ( n % i == 0 )
             return false;

    return true;
}


/**
    * Internal method to return a prime number
   * at least as large as n.  Assumes n > 0.
    */
template <class HashedObj>
int  HashTable<HashedObj>::nextPrime( int n )
   {
         if ( n % 2 == 0 )
             n++;

         for ( ; ! isPrime( n ); n += 2 )
              ;

         return n;
   }

template <class HashedObj>
int HashTable<HashedObj>::findPos( const HashedObj &firstName,const HashedObj & lastName,const HashedObj & phoneNumber, const HashedObj & City ) const
{
       int collisionNum = 0;
       int currentPos = hash_func(firstName,lastName,array.size( ));
       while ( array[ currentPos ].info != EMPTY && array[ currentPos ].firstName != firstName && array[currentPos].lastName != lastName )
       {
        currentPos += ++collisionNum ;  //add the difference
        if ( currentPos >= array.size( ) ){             // perform the mod
               currentPos = currentPos-array.size( );
        }          // if necessary
       }
       return currentPos;
}

/**
  * Return true if currentPos exists and is active.
  */
 template <class HashedObj>
 bool HashTable<HashedObj>::isActive( int currentPos ) const
 {
       return array[ currentPos ].info == ACTIVE;
 }


/**
 * Remove item x from the hash table.
 *  x has to be in the table
 */
template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj &firstName,const HashedObj & lastName,const HashedObj & phoneNumber, const HashedObj & City  )
{
      int currentPos = findPos( firstName,lastName,phoneNumber,City );
    if ( isActive( currentPos ) ){
        array[ currentPos ].info = DELETED;
    }
}

/**
 * Find item x in the hash table.
 * Return the matching item, or ITEM_NOT_FOUND, if not found.
 */
template <class HashedObj>
bool  HashTable<HashedObj>::find(  HashedObj &firstName, HashedObj & lastName, HashedObj & phoneNumber,  HashedObj & City  )const
{
    int currentPos = findPos( firstName,lastName,phoneNumber,City);
    if (isActive( currentPos )){
        firstName = array[ currentPos ].firstName ;
        lastName  = array[ currentPos ].lastName ;
        phoneNumber = array[ currentPos ].phoneNumber ;
        City  = array[ currentPos ].City ;
        return true; 
    }

     return   false ;
}

/**
  * Insert item x into the hash table. If the item is
  * already present, then do nothing.
  */
 template <class HashedObj>
 void HashTable<HashedObj>::insert(  const HashedObj &firstName, const HashedObj & lastName, const HashedObj & phoneNumber, const  HashedObj & City, double uniqueness_count )  
 {

          // Insert x as active
        int currentPos = findPos( firstName,lastName,phoneNumber,City );
         
        if ( isActive( currentPos ) ){
             return;
         }
        array[ currentPos ] = HashEntry( firstName,lastName,phoneNumber,City, ACTIVE );

         // enlarge the hash table if necessary
 
        if ((uniqueness_count/ array.size() > 0.9)){
             int prev_table_size = array.size();
             cout<<"rehashed..."<<endl;
             rehash(uniqueness_count);
             cout<<"previous table size: "<< prev_table_size<<","<< "new table size: "<<array.size()<<","<<" current unique word count "<< uniqueness_count<<endl;
             cout<<"current load factor: "<<uniqueness_count/ array.size()<<endl;

         }
      

 }

template <class HashedObj>
void HashTable<HashedObj>::rehash_helper(HashTable<HashedObj> table ){
    table.rehash();
}

template <class HashedObj>
int HashTable<HashedObj>::size_return(){
    return array.size(); 
}


/**
 * Expand the hash table.
 */
template <class HashedObj>
void HashTable<HashedObj>::rehash(int uniqueness_count )
{
    vector<HashEntry> oldArray = array;

    // Create new double-sized, empty table
    array.resize( nextPrime( 2 * oldArray.size( ) ) );
    for ( int j = 0; j < array.size( ); j++ )
         array[ j ].info = EMPTY;

    // Copy table over
    currentSize = 0;
    for ( int i = 0; i < oldArray.size( ); i++ )
        if ( oldArray[ i ].info == ACTIVE )
             insert( oldArray[ i ].firstName,oldArray[ i ].lastName,oldArray[ i ].phoneNumber,oldArray[ i ].City,uniqueness_count );
}



template <class HashedObj>
void HashTable<HashedObj>::makeEmpty(){
    (this->array).clear();
}

template <class HashedObj>
const HashTable<HashedObj> & HashTable<HashedObj>:: operator=(  HashTable<HashedObj> & rhs )//deep copy
{
    if ( this != &rhs )
    {
        makeEmpty();
        
        if (rhs.isEmpty( ) ){
            return *this;
        }
        
        this->array  =  rhs.array ;
        
    }
  return *this;
}





 

 





