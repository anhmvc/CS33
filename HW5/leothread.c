#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


struct node {
  int label;
  int level;
};

int leonardoNum(int n);
void *thread(void *vargp);

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      printf("Incorrect number of arguments");
      exit(1);
    }
  
  int N = atoi(argv[1]); // convert string to integer
  // the main thread is a leaf if and only if N == 1
  if (N == 1)
    {
      printf("[0]\n");
      exit(0);
    }

  if (N > 1)
  {
      printf("(0\n"); // print main label -- 0
      struct node* leftChild = malloc(sizeof(struct node));
      leftChild->label = 1; // T + 1
      leftChild->level = N-1;
      
      struct node* rightChild = malloc(sizeof(struct node));
      rightChild->label = 1 + leonardoNum(N-1); // T+1+L(k-1)
      rightChild->level = N-2;
      
      pthread_t tid1, tid2;
      pthread_create(&tid1,NULL,thread,leftChild);
      pthread_create(&tid2,NULL,thread,rightChild);
      pthread_join(tid1,NULL);
      pthread_join(tid2,NULL);
      
      // free memory
      free(leftChild);
      free(rightChild);
      printf("%d)\n",0);
  }
  else
      printf("[%d]\n",0); // print main label
  
  exit(0);
}

/* Thread routine */
void *thread(void* vargp)
{
  struct node* mom = vargp;
  int T = mom->label;
  int level = mom->level;

  // leaf thread
  if (level == 0 || level == 1)
    {
      // print "[T]\n" where T is thread's label
      printf("[%d]\n",T);
      return NULL;
    }
    
  // non-leaf thread
    struct node* leftChild = malloc(sizeof(struct node));
  leftChild->label = T+1; // left label = T + 1
  leftChild->level = level-1; // left level = N-1
    struct node* rightChild = malloc(sizeof(struct node));
  rightChild->label = T+1+leonardoNum(level-1); // right label = T+1+L(k-1)
  rightChild->level = level-2; // right level = N-2
      
  // print "(T\n"
  printf("(%d\n",T);
  // creating/reaping children
  pthread_t tid1, tid2;
  pthread_create(&tid1,NULL,thread,leftChild);
  pthread_create(&tid2,NULL,thread,rightChild);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  // print "T)\n" before exiting
  printf("%d)\n",T);
  
  free(leftChild);
  free(rightChild);
  return NULL;
}

int leonardoNum(int n)
{
  if (n == 0 || n == 1)
    return 1;
  // L(N) = L(N-1) + L (N-2) + 1 for N > 1
  return (leonardoNum(n-1) + leonardoNum(n-2) + 1);
}


