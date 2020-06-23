#include "bst.h"
#include <stdlib.h>

int flag_empty_tree;

int compare(int left, int right)
{
  if(left > right)
  {
    return -1;
  }
  else if(right > left)
  {
    return 1;
  }
  return 0;
}

void init_compare_function_ptr( int(*comp)(int left, int right))
{
  //TODO: The compare function should be a function that returns -1 if left-side is bigger than right-side and 1 if right-side ist bigger than left-side
  if (comp) comparer_fct_ptr = comp;
  else comparer_fct_ptr = compare;
}

node* constructNode(int key)
{
  node *temp = malloc(sizeof(node));
  temp->key_ = key;
  temp->left_ = 0;
  temp->right_ = 0;
  flag_empty_tree = 0;
  return temp;
}

node* insert_node(node* root, int key)
{
  if(!root)
  {
    root = constructNode(key);
  }
  else if(!find_node(root, key))
  {
    node *temp = root;
    for(int found_leaf = 0; !found_leaf;)
    {
      if (comparer_fct_ptr(key, temp->key_) > 0)
      {
        if (!(temp->left_))
        {
          temp->left_ = constructNode(key);
          found_leaf = 1;
        }
        else temp = temp->left_;
      }
      else
      {
        if (!(temp->right_))
        {
          temp->right_ = constructNode(key);
          found_leaf = 1;
        }
        else temp = temp->right_;
      }
    }
    temp = 0;
  }
  return root;
}


node* find_node(node* root, int key)
{ 
  //TODO: Return NODE_NOT_FOUND if key was not found, return the node if found
  if (flag_empty_tree || !root)
  {
    flag_empty_tree = 1;
    return NODE_NOT_FOUND;
  }
  node *temp = root;
  if (root->key_ != key)
  {
    for(int found_node = 0; !found_node;)
    {
      if (comparer_fct_ptr(key, temp->key_) > 0)
      {
        if (temp->left_)
        {
          if (temp->left_->key_ == key)
          {
            found_node = 1;
          }
        }
        temp = temp->left_;
      }
      else
      {
        if (temp->right_)
        {
          if (temp->right_->key_ == key)
          {
            found_node = 1;
          }
        }
        temp = temp->right_;
      }
      if(!temp)
      {
        found_node = 1;
      }
    }
  }
  if (!temp)
  {
    return NODE_NOT_FOUND;
  }
  else
  {
    return temp;
  }
}

node* findParent(node* root, int key)
{
  node *temp = root;
  node *parent = 0;
  if (root->key_ != key)
  {
    for(int found_node = 0; !found_node;)
    {
      parent = temp;
      if (comparer_fct_ptr(key, temp->key_) > 0)
      {
        if (temp->left_)
        {
          if (temp->left_->key_ == key)
          {
            found_node = 1;
          }
        }
        temp = temp->left_;
      }
      else
      {
        if (temp->right_)
        {
          if (temp->right_->key_ == key)
          {
            found_node = 1;
          }
        }
        temp = temp->right_;
      }
      if(!temp)
      {
        found_node = 1;
      }
    }
  }
  if (!parent)
  {
    return NODE_NOT_FOUND;
  }
  else
  {
    return parent;
  }
}

int findInorderSuccessor(node* node_to_delete)
{
  int right, left;
  int path_right = 0;
  int path_left = 0;
  node *temp = node_to_delete->right_;
  right = temp->key_;
  while (temp)
  {
    temp = temp->left_;
    if (temp) right = temp->key_;
    path_right++;
  }
  temp = node_to_delete->left_;
  left = temp->key_;
  while (temp)
  {
    temp = temp->right_;
    if (temp) left = temp->key_;
    path_left++;
  }
  if ( (node_to_delete->key_ - right) == (node_to_delete->key_ - left) )
  {
    return (path_right >= path_left) ? right : left;
  }
  else
  {
    return ( (node_to_delete->key_ - right) <= (node_to_delete->key_ - left) ) ? right : left;
  }
}

node* delete_node(node* root, int key)
{
  //TODO: Remove node with key from the tree. Return the root if node was found and deleted, return NODE_NOT_FOUND if not.
  //TODO: Consider all the cases which could occur. Care for memory leaks
  if (flag_empty_tree || !root)
  {
    flag_empty_tree = 1;
    return NODE_NOT_FOUND;
  }
  node *temp = find_node(root, key);
  if (temp)
  {
    node *parent = findParent(root, key);
    if ( (!(temp->left_)) && (!(temp->right_)) )
    {     
      if (parent)
      {
        if (compare(key, parent->key_) > 0)
        {
          parent->left_ = 0;
          free(temp);
        }
        else
        {
          parent->right_ = 0;
          free(temp);
        }
      }
      else
      {
        root = 0;
        free(temp);
        flag_empty_tree = 1;
      }
    }
    else if ( (!(temp->left_)) | (!(temp->right_)) )
    {
      if (parent)
      {
        if (compare(key, parent->key_) > 0)
        {
          parent->left_ = (temp->left_) ? temp->left_ : temp->right_;
          free(temp);
        }
        else
        {
          parent->right_ = (temp->left_) ? temp->left_ : temp->right_;
          free(temp);
        }
      }
      else
      {
        root = (root->left_) ? root->left_ : root->right_;
        free(temp);
      }
    }
    else
    {
      int inorder_successor = findInorderSuccessor(temp);
      delete_node(root, inorder_successor);
      temp->key_ = inorder_successor;
    }
  }
  if (temp) 
  {
    return root;
  }
  else
  {
    return NODE_NOT_FOUND;
  }
}
void dispose_tree(node* root)
{
  //TODO: Free all nodes. Care for memory leaks.
  while (root)
  {
    root = delete_node(root, root->key_);
  }
  flag_empty_tree = 1;
  free(root);
}




