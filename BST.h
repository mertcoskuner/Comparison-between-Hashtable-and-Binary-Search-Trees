#ifndef _BST_H
#define _BST_H
#include <fstream>
#include <iostream>
#include <vector>
#include "strutils.h"

using namespace std;
template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
    Comparable firstName;
    Comparable lastName ;
    Comparable phoneNumber;
    Comparable City;
    BinaryNode  *left;
    BinaryNode  *right;

    BinaryNode( const Comparable & firstname,const Comparable & lastname,
               const Comparable & phonenumber,const Comparable & city,
                  BinaryNode *lt, BinaryNode *rt )
                   : firstName( firstname ),lastName( lastname ),phoneNumber( phonenumber ),City( city ), left( lt ), right( rt ) { }
    
friend class BinarySearchTree<Comparable>;
};
template <class Comparable>
class BinarySearchTree
{
public:
      explicit BinarySearchTree( const Comparable & notFound );
      BinarySearchTree(  BinarySearchTree & rhs );
      ~BinarySearchTree( );
      const Comparable & findMin( ) const;
      const Comparable & findMax( ) const;
      void find(const Comparable & firstName,const Comparable & lastName, Comparable & phoneNumber,  Comparable & city,ofstream &output, bool &output_var  ) const;
      void find_partial( const Comparable & firstName,const Comparable & lastName , BinaryNode<Comparable> *BST, ofstream &output, bool &output_var) const;
      bool isEmpty( ) const;
      void printTree( ) const;
      void makeEmpty( );
      void insert(const Comparable & firstName,const Comparable & lastName,const Comparable & phoneNumber,const Comparable & City);
      void remove( const Comparable & firstName,const Comparable & lastName );
      int depth_for_BST(Comparable type ,BinaryNode<Comparable> * node ); 
      const BinarySearchTree & operator=(  BinarySearchTree & rhs );
    int depth_for_BST_helper(Comparable type ,BinarySearchTree<Comparable>  BST); 
    BinaryNode<Comparable> * cloneTree( BinaryNode<Comparable> * t ) const;
    void PreOrderPrintHelper(ofstream &output);
    void InOrderPrintHelper(ofstream &output);
    void DrawHelp(ofstream &output);
    bool check_balance_BST_helper(BinarySearchTree<Comparable> BST);
    BinaryNode<Comparable> * find( const Comparable & firstName,const Comparable & lastName , BinaryNode<Comparable> *t, bool &output_var) const;


private:
    BinaryNode<Comparable> *root;
    const Comparable ITEM_NOT_FOUND;

    const Comparable & elementAt( BinaryNode<Comparable> *t ) const;
    void insert( const Comparable & firstName,const Comparable & lastName,const Comparable & phoneNumber,const Comparable & City,
           BinaryNode<Comparable> * & t ) const;
    void remove(const Comparable & firstName,const Comparable & lastName, BinaryNode<Comparable> * & t )const;
    BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
    void makeEmpty( BinaryNode<Comparable> * & t ) const;
    void printTree( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;
    void PreOrderPrint(BinaryNode<Comparable> * BST,ofstream &output);
    void InOrderPrint(BinaryNode<Comparable> * BST,ofstream &output);
    void  Draw(BinaryNode<Comparable> * BST,string empty, ofstream &output,bool x,int count,bool isfirst);
    bool  check_balance_BST(BinaryNode<Comparable> * BST,BinarySearchTree<Comparable> BST1);
        };


#include "BST.cpp"
#endif
