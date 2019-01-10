#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define OK 1 
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define BORROW -2
#define m 3  //B树阶数

typedef struct P{
	 int num;
	 char *name ;
	 char *data;
	 P * next;
} *person;

typedef int Status;                //状态类型 
typedef int KeyType;               //关键字定义为int 
typedef struct Record{             //记录类型 
    KeyType key; 
    char *name;
    char *author;
    int  reNumber;
    int totalNumber; 
	person p; 
}Record; 

typedef struct BTNode{
    int keynum;                 //关键字数目 
    KeyType key[m+1];           //关键字数组,0号单元未使用 
    struct BTNode *parent;     //双亲结点指针
    struct BTNode *ptr[m+1];   //孩子结点指针数组,0号单元未使用 
    Record *recptr[m+1];      //记录类型数组,0号未使用 
}BTNode, * BTree; 

typedef struct result{
    BTree pt;
    int i;
    int tag;
}result; 

person makeNode();
void exchage(person &p,person &pp);
void copyPer(person &p,person &pp);
void makeNodeP(person p);
void InitBorperson(person &p);
Status SearchPer(person p,int key);
void addperson(person &p,person &e);
Status deleteNode(person &p,int key);
void print(person p,FILE *fp);
void print1(person p);
int test();
int test2(int key);
