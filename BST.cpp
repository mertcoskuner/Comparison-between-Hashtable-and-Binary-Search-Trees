#include <iostream>
#include "BST.h"
#include <fstream>
#include <string>
#include <vector>
#include "strutils.h"
using namespace std;
/**
  * Construct the tree.
  */
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable & notFound ) :
    ITEM_NOT_FOUND( notFound ), root( NULL ){}


template <class Comparable>
bool BinarySearchTree<Comparable>:: isEmpty( ) const{
    if(root==NULL){
        return true;
    }
    return false; 
}
/**
  * Find item x in the tree.
  * Return the matching item or ITEM_NOT_FOUND if not found.
  */
template <class Comparable>
void BinarySearchTree<Comparable>::find( const Comparable & firstName,const Comparable & lastName,  Comparable & phoneNumber,  Comparable & city, ofstream &output, bool &outputvar ) const
{
    if(lastName == "" && find( firstName,lastName, root, outputvar ) == NULL){
        find_partial(firstName,lastName, root, output ,outputvar);
    }
    else{
        BinaryNode<string> * info = find( firstName,lastName, root, outputvar ) ;
        if(outputvar==true){
            city = info->City;
            phoneNumber = info->phoneNumber;
        }
      
    }
    

}

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::find( const Comparable & firstName,const Comparable & lastName , BinaryNode<Comparable> *t, bool &outputvar ) const
{
    while( t != NULL ){
        if( firstName < t->firstName && lastName == t->lastName ){
            t = t->left;
        }
           
        else if( firstName == t->firstName && lastName < t->lastName ){
            t = t->left;
        }
            
        else if( firstName < t->firstName && lastName < t->lastName ){
            t = t->left;  // insert at the left or
        }
           
        else if( firstName < t->firstName && lastName > t->lastName ){
            t = t->left;
        }
            
        
        else if(firstName > t->firstName && lastName > t->lastName  ){
            t = t->right;// right subtree
        }
            
        else if(firstName > t->firstName && lastName == t->lastName  ){
            t = t->right;// right subtree
        }
            
        else if(firstName == t->firstName && lastName > t->lastName  ){
            t = t->right;// right subtree
        }
            
        else if(firstName > t->firstName && lastName < t->lastName  ){
            t = t->right;
        }
           
        else{
            outputvar =true ;
            return t;    // Match
        }

        
    }
    return NULL;   // No match
}


template <class Comparable>
void BinarySearchTree<Comparable>::find_partial( const Comparable & firstName,const Comparable & lastName , BinaryNode<Comparable> *BST, ofstream &output, bool &output_var) const
{
    if (BST == NULL){
        return;}
    
    if(BST->firstName.substr(0,(firstName.length()))== firstName){
        output << BST -> firstName<< " "<<BST -> lastName<< " " << BST -> phoneNumber<< " " << BST -> City<<endl  ;
        cout << BST -> firstName<< " "<<BST -> lastName<< " " << BST -> phoneNumber<< " " << BST -> City<<endl  ;
        output_var =true;

    }
        /*  left subtree */
    find_partial(firstName, lastName ,BST->left,output,output_var);
        /*  right subtree */
    find_partial(firstName, lastName ,BST->right,output,output_var);
    
}
/**
  * Find the smallest item in the tree.
  * Return smallest item or ITEM_NOT_FOUND if empty.
  */

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin( ) const
{
    return elementAt( findMin( root ) );
}
/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <class Comparable>
BinaryNode<Comparable> *
BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t )const
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}
/**
  * Find the smallest item in the tree.
  * Return smallest item or ITEM_NOT_FOUND if empty.
  */
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const
{
    return elementAt( findMax( root ) );
}
/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <class Comparable>
BinaryNode<Comparable> *
BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t )const
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}
/**
  * Insert x into the tree; duplicates are ignored.
  */
template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & firstName,const Comparable & lastName,const Comparable & phoneNumber,const Comparable & City)
{
    insert(firstName,lastName, phoneNumber,City, root );
}
/**
         * Internal method to insert into a subtree.
         * x is the item to insert.
         * t is the node that roots the tree.
         * Set the new root.
         */
template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & firstName,const Comparable & lastName,const Comparable & phoneNumber,const Comparable & City,BinaryNode<Comparable> * & t ) const
{
    if( t == NULL ) //  create a new node at the right place
        t = new BinaryNode<Comparable>( firstName,lastName,phoneNumber,City, NULL, NULL );
    else if( firstName < t->firstName && lastName == t->lastName )
        insert( firstName,lastName,phoneNumber,City, t->left );
    else if( firstName == t->firstName && lastName < t->lastName )
        insert( firstName,lastName,phoneNumber,City, t->left );
    else if( firstName < t->firstName && lastName < t->lastName )
        insert( firstName,lastName,phoneNumber,City, t->left );  // insert at the left or
    else if( firstName < t->firstName && lastName > t->lastName )
        insert( firstName,lastName,phoneNumber,City, t->left );
    
    
    else if(firstName > t->firstName && lastName > t->lastName  )
        insert( firstName,lastName,phoneNumber,City, t->right );// right subtree
    else if(firstName > t->firstName && lastName == t->lastName  )
        insert( firstName,lastName,phoneNumber,City, t->right );// right subtree
    else if(firstName == t->firstName && lastName > t->lastName  )
        insert( firstName,lastName,phoneNumber,City, t->right );// right subtree
    else if(firstName > t->firstName && lastName < t->lastName  )
        insert( firstName,lastName,phoneNumber,City, t->right );
    
    else
        ;  // Duplicate; do nothing
}
/**
  * Remove x from the tree. Nothing is done if x is not found.
  */
 template <class Comparable>
 void BinarySearchTree<Comparable>::remove( const Comparable & firstName,const Comparable & lastName )
 {
        remove( firstName,lastName, root );
 }
/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & firstName,const Comparable & lastName, BinaryNode<Comparable> * & t )const
{
    if( t == NULL )
        return;   // Item not found; do nothing
    
    else if( firstName < t->firstName && lastName == t->lastName )
        remove( firstName,lastName, t->left );
    else if( firstName == t->firstName && lastName < t->lastName )
        remove( firstName,lastName, t->left );
    else if( firstName < t->firstName && lastName < t->lastName )
        remove( firstName,lastName, t->left );
    else if( firstName < t->firstName && lastName > t->lastName )
        remove( firstName,lastName, t->left );

    
    else if(firstName > t->firstName && lastName > t->lastName  )
        remove( firstName,lastName, t->right );
    else if(firstName > t->firstName && lastName == t->lastName  )
        remove( firstName,lastName, t->right );
    else if(firstName == t->firstName && lastName > t->lastName  )
        remove( firstName,lastName, t->right );
    else if(firstName > t->firstName && lastName < t->lastName  )
        remove( firstName,lastName, t->right );


    else if( t->left != NULL && t->right != NULL ) // Two children
   {
       t->firstName = findMin( t->right )->firstName;
       t->lastName = findMin( t->right )->lastName;
       remove( t->firstName, t->lastName, t->right );
   }
   else // one or no children
   {
       BinaryNode<Comparable> *oldNode = t;
       t = ( t->left != NULL ) ? t->left : t->right;
       delete oldNode;
   }
}

/**
  * Make the tree logically empty.
  */
 template <class Comparable>
 void BinarySearchTree<Comparable>::makeEmpty( )
 {
      makeEmpty( root );
 }


/**
 * Internal method to make subtree empty.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::
makeEmpty( BinaryNode<Comparable> * & t ) const
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}
/**
  * Print the tree contents in sorted order.
  */
 template <class Comparable>
 void BinarySearchTree<Comparable>::printTree( ) const
 {
     if( isEmpty( ) )
         cout << "Empty tree" << endl;
     else
         printTree( root );
 }

/**
  * Destructor for the tree.
  */
 template <class Comparable>
 BinarySearchTree<Comparable>::~BinarySearchTree( )
 {
     makeEmpty( );
 }


/**
* Internal method to print a subtree rooted at t in sorted order.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::printTree( BinaryNode<Comparable> * t ) const
{
      if ( t != NULL )
      {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
      }
}

/**
 * Internal method to clone subtree.
 */
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::clone( BinaryNode<Comparable> * t ) const
{
    if ( t == NULL )
        return NULL;
    else
        return new BinaryNode<Comparable>( t->firstName,t->lastName,t->phoneNumber,t->City,clone(t->left),clone(t->right));
}

template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::cloneTree( BinaryNode<Comparable> * t ) const
{
    if ( t == NULL ){
        return NULL;}
    BinaryNode<Comparable> * new_r = clone(t);
    new_r->left = cloneTree(t->left);
    new_r->right = cloneTree(t->right);
    return new_r;
}


template <class Comparable>
const BinarySearchTree<Comparable> & BinarySearchTree<Comparable>:: operator=(  BinarySearchTree<Comparable> & rhs )//deep copy
{
      if ( this != &rhs )
      {
           makeEmpty();
          if ( rhs.isEmpty( ) ){
              return *this;}
          root  =  cloneTree(rhs.root) ;
    }
    return *this;
}
/**
  * Copy constructor.
  */
 template <class Comparable>
 BinarySearchTree<Comparable>::BinarySearchTree(  BinarySearchTree<Comparable> & rhs ) :root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
 {
     *this = rhs;
 }

template <class Comparable>
int BinarySearchTree<Comparable>:: depth_for_BST(Comparable type ,BinaryNode<Comparable> * node){
    int length_for_left_side = 0 , length_for_right_side= 0 ;
    
    if(node == NULL){
        return 0;
    }
    length_for_left_side = depth_for_BST(type , node->left) ;

    length_for_right_side = depth_for_BST(type , node->right);

    if (length_for_left_side > length_for_right_side){
        return (length_for_left_side + 1);}
    else{
        return (length_for_right_side + 1);}

}
template <class Comparable>
int BinarySearchTree<Comparable>:: depth_for_BST_helper(Comparable type ,BinarySearchTree<Comparable>  BST){
    int length  =0;
    if(type =="left"&& BST.root->left != NULL){
        length  =depth_for_BST(type,BST.root->left);}
    else if(type =="right"&& BST.root->left != NULL){
        length  =depth_for_BST(type,BST.root->right);}

    return  length;
}
 
template <class Comparable>
void BinarySearchTree<Comparable>::PreOrderPrint(BinaryNode<Comparable> * BST, ofstream &output){

    if (BST == NULL){
        return;}
    
    output << BST -> firstName<< " "<<BST -> lastName<< " " << BST -> phoneNumber<< " " << BST -> City<<endl  ;
     
        /*  left subtree */
    PreOrderPrint(BST->left,output);
        /*  right subtree */
    PreOrderPrint(BST->right,output);
    
}
template <class Comparable>
void BinarySearchTree<Comparable>::PreOrderPrintHelper(ofstream &output){
    PreOrderPrint(this->root, output);
}



template <class Comparable>
void BinarySearchTree<Comparable>::InOrderPrint(BinaryNode<Comparable> * BST, ofstream &output){

    if (BST == NULL){
        return;}
        /*  left subtree */
    InOrderPrint(BST->left,output);
    output << BST -> firstName<< " "<<BST -> lastName<< " " << BST -> phoneNumber<< " " << BST -> City<<endl  ;
        /*  right subtree */
    InOrderPrint(BST->right,output);
    
}


template <class Comparable>
void BinarySearchTree<Comparable>::InOrderPrintHelper(ofstream &output){
    InOrderPrint(this->root, output);
}



template <class Comparable>
void BinarySearchTree<Comparable>::Draw(BinaryNode<Comparable> * BST,string empty, ofstream &output,bool x,int count,bool isfirst){
    if (BST == NULL){
        return;}
    if(isfirst){
        output << "|__"<<UpperString(BST -> firstName)<< " "<<UpperString(BST -> lastName)<<endl  ;
        empty = "   ";

    }
    if(x==true && isfirst == false){

        output<<empty;

   
        output << "--"<< UpperString(BST -> firstName)<< " "<<UpperString(BST -> lastName)<<endl  ;
        empty+="  " ;

    }
    else if(x==false && isfirst == false){
        
        output<<empty;
 
        output << "|__"<< UpperString(BST -> firstName)<< " "<<UpperString(BST -> lastName)<<endl  ;
        empty+="   " ;
    }
    isfirst=false;
        /*  left subtree */
    
    Draw(BST->left,empty+"|"  ,output,true,count, isfirst);
        /*  right subtree */
    
    Draw(BST->right,empty,output,false,count,isfirst);
    
}
template <class Comparable>
void BinarySearchTree<Comparable>::DrawHelp(ofstream &output){
   
    Draw(this->root,"   ", output,true ,0,true);
}









template <class Comparable>
bool BinarySearchTree<Comparable>::check_balance_BST(BinaryNode<Comparable> * BST,BinarySearchTree<Comparable>BST1){
   
    int  left_height_BST = depth_for_BST_helper("left", BST1) ;
    int  right_height_BST = depth_for_BST_helper("right", BST1) ;
    if(BST == NULL ) {
        return true;
    }
    if((left_height_BST - right_height_BST == 1 || left_height_BST - right_height_BST == -1 ||left_height_BST - right_height_BST == 0)&& check_balance_BST(BST->right,BST1)&& check_balance_BST(BST->left,BST1)){
        return true;
    }
    return false;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::check_balance_BST_helper(BinarySearchTree<Comparable>BST ){
 
    return check_balance_BST(BST.root,BST);
}




