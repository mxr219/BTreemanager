#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define OK 1 
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define BORROW -2
#define m 3  //B������

typedef struct P{
	 int num;
	 char *name ;
	 char *data;
	 P * next;
} *person;

typedef int Status;                //״̬���� 
typedef int KeyType;               //�ؼ��ֶ���Ϊint 
typedef struct Record{             //��¼���� 
    KeyType key; 
    char *name;
    char *author;
    int  reNumber;
    int totalNumber; 
	person p; 
}Record; 

typedef struct BTNode{
    int keynum;                 //�ؼ�����Ŀ 
    KeyType key[m+1];           //�ؼ�������,0�ŵ�Ԫδʹ�� 
    struct BTNode *parent;     //˫�׽��ָ��
    struct BTNode *ptr[m+1];   //���ӽ��ָ������,0�ŵ�Ԫδʹ�� 
    Record *recptr[m+1];      //��¼��������,0��δʹ�� 
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
