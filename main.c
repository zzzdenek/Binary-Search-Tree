#include <assert.h>
#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

//TODO: Test the implementation here

int main() 
{
  //Add more tests by yourself as these are only sample tests
  node* bst = 0;
  init_compare_function_ptr(0);

  //setvbuf(stdout, NULL, _IONBF, 0);
  setbuf(stdin, NULL);

  while (1)
  {
    char in_char = 0;
    int in_int = 0;
    if(!in_char) printf("[I]nsert or [F]ind or [D]elete or [Q]uit?\n");
    //setbuf(stdout, NULL);
    fflush(stdin);
    //scanf("%c", &in_char);
    in_char = getchar();
    if (in_char) printf("Node?\n");
    //fflush(stdin);
    scanf("%d", &in_int);
    if ( (in_char == 'i') || (in_char == 'I') ) bst = insert_node(bst, in_int);
    else if ( (in_char == 'f') || (in_char == 'F') ) find_node(bst, in_int);
    else if ( (in_char == 'd') || (in_char == 'D') )
    {
      printf("Dispose tree?\n");
      fflush(stdin);
      in_char = getchar();
      if (in_char == 'y')
      {
        printf("REALLY?\n");
        fflush(stdin);
        in_char = getchar();
        if (in_char == 'y')
        {
          dispose_tree(bst);
        }
        else delete_node(bst, in_int);
      }
      else delete_node(bst, in_int);
    }
    else if ( (in_char == 'q') || (in_char == 'Q') ) break;
    fflush(stdin);
  }

/*
  bst = insert_node(bst,100);
  bst = insert_node(bst,150);
  bst = insert_node(bst,50);
  assert(find_node(bst,100) != NODE_NOT_FOUND);
  assert(find_node(bst,150) != NODE_NOT_FOUND);
  assert(find_node(bst,50) != NODE_NOT_FOUND);
  //bst = delete_node(bst,100);
  //assert(find_node(bst,100) == NODE_NOT_FOUND);
  //bst = delete_node(bst,50);
  //bst = delete_node(bst,100);
  //assert(find_node(bst,150) != NODE_NOT_FOUND);
  dispose_tree(bst);*/

  

  return 0;

}
