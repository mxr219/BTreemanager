#include"head.h"

person makeNode(){
	person p;
	p = (person )malloc(sizeof(P));
	p->name = (char *)malloc(10*sizeof(char));
    p->data = (char *)malloc(10*sizeof(char));
	p->num = 0;
	p->next = NULL; 
	return p;
}

void exchage(person &p,person &pp){
	person e = p;
	p = pp;
	pp = e; 
}
void copyPer(person &p,person &pp){
	person e = p;
	p = pp;
	pp = e; 
} 

void makeNodeP(person p){
	p = (person )malloc(sizeof(P));
	p->name = (char *)malloc(10*sizeof(char));
	p->data = (char *)malloc(10*sizeof(char));
	p->num = 0;
	p->next = NULL; 
	return ;
}

void InitBorperson(person &p){
      p = makeNode();
}

Status SearchPer(person p,int key){
	 if(NULL==p) return ERROR;
	 person pp = p->next;
	 while(NULL!=pp&&pp->num!=key){
	 	 pp = pp->next;
	 }
	 if(pp==NULL) return ERROR;
	 else return OK;
}

void addperson(person &p,person &e){
	 person pp,ppar;
	 pp = p;
	 ppar = pp;
	 struct tm *newtime;
     time_t lt;
     lt=time( NULL );
     newtime=localtime(&lt);
     strftime(e->data, 128, "%Y.%m.%d", newtime);
	 while(NULL!=pp){
	 	 ppar = pp;
	 	 pp = pp->next ;
	 }
     if(p==NULL){
     	p = makeNode();
     	copyPer(p->next,e);
	 }else{
	 	ppar->next = makeNode();
	 	copyPer(ppar->next,e);
	 }
}
Status deleteNode(person &p,int key){
	 person pp = p->next;
	 person ppar = p;
	 if(NULL==p||NULL==pp) return ERROR;
	 else{
	 	while(pp!=NULL&&pp->num!= key){
	 		ppar = pp;
	 		pp = pp->next;
		 }
	    if(pp==NULL) return ERROR;
		else{
		    ppar->next = pp->next;
		    free(pp);
			return OK; 	
		}   
	 }
}
void print(person p,FILE *fp){
	if(NULL==p) return;
	p = p->next;
	while(NULL!=p){
		printf("学号： %3d ,姓名：%s ,借阅时间：%s\n",p->num,p->name,p->data);
		fprintf(fp,"学号： %3d ,姓名：%s 借阅时间：%s\n",p->num,p->name,p->data);
		p = p->next; 
	}
	return;
}

void print1(person p){
	if(NULL==p) return;
	p = p->next;
	while(NULL!=p){
		printf("%d %s \t;",p->num,p->name);
		p = p->next; 
	}
	return;
}

