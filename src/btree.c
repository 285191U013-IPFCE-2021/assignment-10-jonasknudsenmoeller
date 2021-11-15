#include "..\include\btree.h"

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

//function for finding the smallest value in the the right side of the tree. So the smallest of the largest values. 

int find_min_of_right (struct tree_node *t)
{
  struct tree_node * temp = t;
      while (t -> left != NULL)
      {
        temp = t -> left;
      }
  return temp -> item;
} 


struct tree_node * Insert (int x, struct tree_node *t)
{

  struct tree_node * new_x = malloc(sizeof(struct tree_node));

  new_x -> item = x;
  new_x -> right = NULL;
  new_x -> left = NULL;

  if (t == NULL) //if the tree is empty, we just return the new tree with the value x. 
    return new_x;
  
  if (x > t -> item)
    t -> right = Insert(x , t -> right); //recursive step, when x is larger than the knot.
  else 
    t -> left = Insert(x , t -> left); //recursive step, when x is smaller than the knot. 

  return t; //returns the tree with item x now in it. 
}

struct tree_node * Remove (int x, struct tree_node *t)
{
  if (t == NULL) //if the tree is empty, we return the empty tree. 
    return t;

  if (x > t->item) 
    {
      t -> right = Remove (x , t -> right); //the function is called recursively, by going either left or right through the branches
    }                                       //until we end up on the x we are searching for. 
  else if (x < t -> item)
    {
      t -> left = Remove (x , t -> left);
    }
  else if (t -> left == NULL && t -> right == NULL) //if the knot with the x-value we are looking to remove, doesn't have any children
    {                                               //we can just free the node, and return the updated tree. 
      free(t);
      return NULL;
    }
     else if (t->right == NULL || t->left == NULL)
              {
                struct tree_node * temp_t = NULL;
                if (t -> right == NULL)
                {
                  temp_t = t -> left;
                }
                else if (t -> left == NULL)
                  temp_t = t -> right;
                free (t);
                return temp_t;
              } 
     else 
      {
        int min_largest = find_min_of_right (t->right); //function find_min_of_right is used to change the value of t->item to the 
        t -> item = min_largest;                        //the replacement value, and then we recursively remove the node from which 
        t -> right = Remove(t -> item, t -> right);     //borrowed the value. 
      }
  return t;
}


int Contains (int x, struct tree_node *t)
{
  if (t == NULL) //firstly we check if the tree is empty
    return 0;
    
  if (t->item == x) //base case 
    return 1;
  else if (x < t->item)         //recursive step: is x smaller than current item? else check "left child"
    return Contains(x, t->left);
  else              //recursive step: is x larger than current item? else check "right child"
    return Contains(x, t->right);
  // Return true if the tree t contains item x. Return false otherwise.

}


struct tree_node * Initialize (struct tree_node *t)
{
  t = NULL;

  return t;
}

int Empty (struct tree_node *t)
{
  // if there is no tree (if it is empty), we should return true. Else we return false (0)
  if (t == NULL)
    return 1;
  else
    return 0;
}

int Full (struct tree_node *t)
{
    // a tree cannot be full, so we should always return false (or in this case 0 because we have an integer as return type)
    return 0;
}
