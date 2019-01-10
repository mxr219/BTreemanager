#include"head.h"

void copy(Record * &e1,Record *&e2){
	      int d =0; 
	      e1->key = e2->key;
          e1->reNumber= e2->reNumber;
          e1->totalNumber= e2->totalNumber;
            for(d=0;e2->name[d]!='\0';d++){
                 	e1->name[d] = e2->name[d]; 
				 }  e1->name[d] = '\0'; 
			for(d=0;e2->author[d]!='\0';d++){
                    e1->author[d] = e2->author[d]; 
				 }  e1->author[d] = '\0'; 
		    exchage(e1->p,e2->p);		 
}
void copyRE(Record &e1,Record *&e2) {
	      int d= 0;
	      e1.key = e2->key;
          e1.reNumber= e2->reNumber;
          e1.totalNumber= e2->totalNumber;
            for(d=0;e2->name[d]!='\0';d++){
                 	e1.name[d] = e2->name[d]; 
				 }  e1.name[d] = '\0'; 
			for(d=0;e2->author[d]!='\0';d++){
                    e1.author[d] = e2->author[d]; 
				 }  e1.author[d] = '\0'; 
			 exchage(e1.p,e2->p); 
}

void copyRec(Record * &e1,Record &e2) {
	      int d= 0;
	      e1->key = e2.key;
          e1->reNumber= e2.reNumber;
          e1->totalNumber= e2.totalNumber;
            for(d=0;e2.name[d]!='\0';d++){
                 	e1->name[d] = e2.name[d]; 
				 }  e1->name[d] = '\0'; 
			for(d=0;e2.author[d]!='\0';d++){
                    e1->author[d] = e2.author[d]; 
				 }  e1->author[d] = '\0';
		  exchage(e1->p,e2.p);  
}
int Search(BTree p ,int k){
    int i = 1;
    while(i<=p->keynum&&k>p->key[i]){
       i++;
    }
    return i;
}
void SearchBTree(BTree  t,int k,result &r){
    int  i = 0, found = 0;
    BTree p = t,q = NULL;
    while(p!=NULL&&0 == found ){
        i = Search(p,k);
        if(i<=p->keynum&&p->key[i]==k) found = 1;
        else {
             q = p;
             p = p->ptr[i-1];     
         }
    }
    if(1==found){
         r.pt = p;
         r.i = i;
         r.tag = 1;
    }else{
        r.pt = q;
        r.i = i;
        r.tag = 0; 
    }
} 

void split(BTree &q,int s,BTree &ap){
     int i,j,n = q->keynum;
     ap = (BTNode *)malloc(sizeof(BTNode));
      int d =0;
     for(d=0;d<=m;d++){
        ap->recptr[d] = (Record *)malloc(sizeof(Record));
		ap->recptr[d]->name = (char *)malloc(20*sizeof(char));
		ap->recptr[d]->author = (char *)malloc(20*sizeof(char));
		ap->recptr[d]->p = makeNode();

	 }
     ap->ptr[0] = q->ptr[s];
     for(i=s+1,j=1;i<=n;i++,j++){   //将q的后半部分复制到ap中
          ap->key[j] = q->key[i];
          copy(ap->recptr[j], q->recptr[i]);
          ap->ptr[j] = q->ptr[i];
     } 
     ap->keynum = n-s;             //给ap的keynum赋值 
     ap->parent = q->parent;       //给ap的parent赋值 
                             
     for(i=0;i<=n-s;i++){         //修改子节点的parent域; 
          if(ap->ptr[i]!=NULL){
                 ap->ptr[i]->parent = ap;
          }
     }
     q->keynum = s-1;
}

void newRoot(BTree &t,BTree q,BTree ap,int x,Record &e){
     t = (BTNode *)malloc(sizeof(BTNode));
     t->keynum = 1;
     t->key[1] = x;
     t->parent = NULL;
     t->ptr[0] = q;     //t的左孩子 
     t->ptr[1] = ap;    //t的右孩子指针 
     if(q!=NULL)   q->parent = t;  
     if(NULL!=ap)   ap->parent = t;
     // t->recptr = ;  给记录类型数组赋值 
     int d =0;
     for(d=0;d<=m;d++){
        t->recptr[d] = (Record *)malloc(sizeof(Record));
		t->recptr[d]->name = (char *)malloc(20*sizeof(char));
		t->recptr[d]->author = (char *)malloc(20*sizeof(char));
		t->recptr[d]->p =makeNode();			
	 }
     copyRec(t->recptr[1],e);
} 

void insert(BTree &q,int i,int x,BTree ap,Record &e){
      int j, n = q->keynum;
      for(j = n;j>=i;j--){
           q->ptr[j+1] = q->ptr[j];
           q->key[j+1] = q->key[j];
           copy(q->recptr[j+1], q->recptr[j]);
      }
      q->key[i] = x;
      copyRec(q->recptr[i],e);
      q->ptr[i] = ap;
      if(NULL!=ap) ap->parent = q;
      q->keynum++;
}

void InsertBTree(BTree &t,int k,BTree q,int i,Record &e){
    int x,s,finished = 0,needNewRoot = 0;
    BTree ap;
    if(NULL == q) newRoot(t, NULL, NULL, k,e);    
    else{
       x = k;
       ap = NULL;
       while(0==needNewRoot && 0==finished){
             insert(q, i, x, ap,e);
          if(q->keynum<m) finished = 1;
          else{
                s = (m+1)/2;
                 split(q, s,ap);
                 x = q->key[s];
                 copyRE(e,q->recptr[s]); 
                 if(NULL!= q->parent){
                       q = q->parent;
                       i = Search( q ,x );
                }else{
                    needNewRoot = 1;
                }
          } 
       }
       if(1==needNewRoot)  newRoot(t, q, ap ,x,e);
    } 
}

Status insertBTree(BTree &t,int k,Record &e){
     result r ;
     BTree q ;
     int i = 0;     
     SearchBTree( t,k,r);
     if(r.tag==1) return ERROR;
     q = r.pt;
     i = r.i;
     InsertBTree(t, k, q, i,e);
     return OK;
}

void Remove(BTree &p,int k){
     int i=0;
     for(i = k;i<p->keynum;i++){
          p->key[i] = p->key[i+1];  
          p->ptr[i] = p->ptr[i+1];
          copy( p->recptr[i],p->recptr[i+1]);
     }
     p->keynum--;
}

void Restore(BTree &t,BTree &p,int k){
     int s = (m-1)/2;
     BTree ppar = p->parent,pl,pr,pp;
     int i,next,last,j;
     if(NULL == ppar) {     
       t = p->ptr[0];
       if(NULL!=t)
       t->parent = NULL;
       free(p);
       return;
     }
     for(i=0;i<=ppar->keynum&&ppar->ptr[i]!=p;i++){     
       }
     next = i+1;
     last = i-1;
     if(i<ppar->keynum&&ppar->ptr[next]->keynum>s){    //右相邻兄弟有富余
         pr = ppar->ptr[next];
         p->key[++p->keynum] = ppar->key[next];       //pkey+1,
         copy(p->recptr[p->keynum], ppar->recptr[next]);
         if( NULL!=pr->ptr[0]){
              p->ptr[p->keynum] =  pr->ptr[0];        //若非最下层节点，则将pr第一个右孩子变成p的最后一个左孩子
              pr->ptr[0]->parent = p;                 //改变右孩子的双亲值
         }
                
         ppar->key[next] = pr->key[1];
         copy(ppar->recptr[next],pr->recptr[1]);
         pr->ptr[0] = pr->ptr[1];
         for(j = 1;j<pr->keynum;j++){                  //将pr所有关键字左移
              pr->key[j] = pr->key[j+1];         
              pr->ptr[j] = pr->ptr[j+1]; 
			  copy(pr->recptr[j],pr->recptr[j+1]);        
         }
         pr->keynum--; 
     }else if(i>0&&ppar->ptr[last]->keynum>s){       //左相邻兄弟有富余
         pl = ppar->ptr[last]; 
         p->keynum++;
         
         for(j = p->keynum;j>1;j--){
            p->key[j+1] = p->key[j];
           // p->ptr[j] = p->ptr[j-1];
            copy(p->recptr[j],p->recptr[j-1]); 
         }
         for(j = p->keynum;j>=1;j--){
            p->ptr[j] = p->ptr[j-1];
         }
         p->key[1] = ppar->key[i];
         copy(p->recptr[1],ppar->recptr[i]); 
         if(NULL!=pl->ptr[pl->keynum]){
            p->ptr[0] = pl->ptr[pl->keynum];        //若非最下层节点，则将pl最后孩子变成p的第一个左孩子
            pl->ptr[pl->keynum]->parent = p;        //左孩子双亲
         }
         copy(ppar->recptr[i],pl->recptr[pl->keynum]);
         ppar->key[i] = pl->key[pl->keynum--];
         
     }else if(i<ppar->keynum){
         pr = ppar->ptr[next];
         p->key[++p->keynum] = ppar->key[next];
         copy(p->recptr[p->keynum],ppar->recptr[next]);
         if(pr->ptr[0]!=NULL){
           p->ptr[p->keynum] = pr->ptr[0];
           pr->ptr[0]->parent = p;
         }
       
         for(j=1;j<= pr->keynum;j++){
            p->key[++p->keynum] = pr->key[j];
            copy(p->recptr[p->keynum],pr->recptr[j]);
            if(p->ptr[j]!=NULL){
              p->ptr[p->keynum] = pr->ptr[j];
              pr->ptr[j]->parent = p;
            }
         }
         pr->keynum = 0;   
         for(j = next;j<ppar->keynum;j++){
             ppar->key[j] = ppar->key[j+1];
             ppar->ptr[j] = ppar->ptr[j+1];
             copy(ppar->recptr[j],ppar->recptr[j+1]);
         }
         ppar->keynum--;
         if(ppar->keynum<s) Restore(t,ppar,k);
     }else{      
         pl = ppar->ptr[last];
         pl->key[++pl->keynum] = ppar->key[i];
         copy(pl->recptr[pl->keynum],ppar->recptr[i]); 
         if(NULL!=p->ptr[0])  {
              pl->ptr[pl->keynum] = p->ptr[0];
              p->ptr[0]->parent = pl;         
         }
        
         for(j=1;j<= p->keynum;j++){
            pl->key[++pl->keynum] = p->key[j];
            copy(pl->recptr[pl->keynum],p->recptr[j]);
            if(p->ptr[j]!=NULL){
             pl->ptr[pl->keynum] = p->ptr[j];
             p->ptr[j]->parent = pl;
            }           
         }
         p->keynum = 0;       
         for(j = i;j<ppar->keynum;j++){
             ppar->key[j] = ppar->key[j+1];
             ppar->ptr[j] = ppar->ptr[j+1];
             copy(ppar->recptr[j],ppar->recptr[j+1]);
         }
         ppar->keynum--;
         if(ppar->keynum<s) Restore(t,ppar,k);         
        }
}  
void Successor(BTree &p,int i){
     BTree ptemp,q;
     ptemp = p->ptr[i-1];
     q = ptemp;
     while(NULL!= ptemp) {
       q = ptemp;
       ptemp = ptemp->ptr[ptemp->keynum];       
     }
     p->key[i] = q->key[q->keynum];
     copy(p->recptr[i],q->recptr[q->keynum]);
     p = q;
}
void DeleteBTree(BTree &t,BTree &p,int i){
     if(NULL!=p->ptr[i]){
        Successor(p, i);
        DeleteBTree(t,p, p->keynum) ;
     }else{
        Remove(p,i);
        if(p->keynum<(m-1)/2){
           Restore(t,p,i);
        }
     }
}

Status deleteBTree(BTree &t,int k){
     result r ;
     BTree q ;
     int i = 0;     
     SearchBTree( t,k,r);
     if(r.tag==0) return ERROR;
     q = r.pt;
     i = r.i;
     DeleteBTree(t,q,i);
     return OK;
}
void printBTree(BTree t,int lev,FILE *fp){
    if(NULL==t) return ;  
    int n = t->keynum;
    printBTree( t->ptr[n], lev+n,fp);
    for(int j = t->keynum;j>0;j--){
          for(int k= 0;k<lev;k++){
            printf("   ");
            fprintf(fp,"   ");
          }
          printf("%3d \n",t->key[j]);
          fprintf(fp,"%3d \n",t->key[j]);
          printBTree( t->ptr[j-1], lev+n,fp);
    }      
}

void travse(BTree t){
    if(NULL==t) return;
    travse(t->ptr[0]);
    int n = t->keynum;
    for(int i= 1;i<=n;i++){
       printf("%d ",t->key[i]);
       travse(t->ptr[i]);
    }
    return;
}
 
void destroy(BTree &t){
      int i =0;
     if(NULL==t ) return;     
     for(i;i<t->keynum;i++){
        destroy(t->ptr[i]);
     }
     free(t);
    // t = NULL;
}
void destr(BTree &t){
      while(t!=NULL)
      deleteBTree(t,t->key[1]);
}

void menu(FILE *fp){
	printf("======菜单栏=====\n");
	printf("0：退出系统\n");
	printf("1：图书入库\n");
	printf("2: 清除库存\n");
	printf("3: 借阅图书\n"); 
    printf("4: 归还图书\n");
    printf("5: 查看库存信息\n"); 
    printf("6: 查找某作者作品\n");
    printf("7：查找某本书所有信息\n");
    printf("8：凹表输出\n");
    printf("9: 清空书库\n"); 
    printf("=================\n");
    fprintf(fp,"======菜单栏=====\n");        //输出到文件做日志 
    fprintf(fp,"0：退出系统\n");
	fprintf(fp,"1：图书入库\n");
	fprintf(fp,"2: 清除库存\n");
	fprintf(fp,"3: 借阅图书\n"); 
    fprintf(fp,"4: 归还图书\n");
    fprintf(fp,"5: 查看库存信息\n"); 
    fprintf(fp,"6: 查找某作者作品\n\n");
    fprintf(fp,"7：查找某本书所有信息\n");
    fprintf(fp,"8：凹表输出\n");
    fprintf(fp,"9: 清空书库\n"); 
    fprintf(fp,"=================\n");
}

void travseFor(BTree t,FILE *fp){   //按顺序输出所有结点的信息(按关键字大小顺序输出) 
    if(NULL==t) return;
    travseFor(t->ptr[0],fp);
    int n = t->keynum;
    for(int i= 1;i<=n;i++){
       printf(    "%2d   %s\t    %s\t\t %2d\t\t %2d\n",t->recptr[i]->key,t->recptr[i]->name,t->recptr[i]->author,t->recptr[i]->reNumber,t->recptr[i]->totalNumber);  
       fprintf(fp,"%2d   %s\t    %s\t\t %2d\t\t %2d\n",t->recptr[i]->key,t->recptr[i]->name,t->recptr[i]->author,t->recptr[i]->reNumber,t->recptr[i]->totalNumber);    
	   travseFor(t->ptr[i],fp);
    }
    return;
}
 
Status borrow(BTree &t,int key,FILE *fp){
	 result r ;
     BTree q ;
     person  e;
     e = makeNode();
     int i = 0;     
     SearchBTree( t,key,r);
     if(r.tag==0) return ERROR;
     q = r.pt;
     i = r.i;
     if(q->recptr[r.i]->reNumber<=0) return OVERFLOW;
     else{
	    printf("输入学号：");
	    fprintf(fp,"输入学号：");
  	    scanf("%d",&e->num);
  	    fprintf(fp,"%d\n",e->num);
	    if (SearchPer(q->recptr[i]->p,e->num)==OK){
	       return BORROW;
	    }else{
		   printf("输入姓名：");
		   fprintf(fp,"输入姓名：");
		   scanf("%s",e->name);
		   fprintf(fp,"%s\n",e->name);
		   addperson(q->recptr[r.i]->p, e);
		   q->recptr[r.i]->reNumber--;
		    return OK; 
	   }  
	 }      
}

Status Return(BTree &t,int key,FILE *fp){
	 result r ;
     BTree q ;
     int num;
     int i = 0;     
     SearchBTree( t,key,r);
     if(r.tag==0) return ERROR;
        q = r.pt;
        i = r.i;
	    printf("输入学号：");
	    fprintf(fp,"输入学号：");
  	    scanf("%d",&num);
  	    fprintf(fp,"%d\n",&num);
	    if (SearchPer(q->recptr[i]->p,num)==OK){
	    	deleteNode(q->recptr[i]->p,num);
	    	q->recptr[r.i]->reNumber++;
	        return OK;
	    }else{
		    return OVERFLOW; 
	   }  
}

void travseBORROW(BTree t,FILE *fp){
    if(NULL==t) return;
    travseBORROW(t->ptr[0],fp);
    int n = t->keynum;
    for(int i= 1;i<=n;i++){
       printf("书号：%d\t\t",t->key[i]);
       fprintf(fp,"书号：%d\t\t",t->key[i]);
       print1(t->recptr[i]->p);
       printf("\n"); 
       fprintf(fp,"\n");
       travseBORROW(t->ptr[i],fp);
    }
    return;
}

Status comparechar(char *a,char *b){
	 int d = 0;
	 int flag = OK;
	 for(d=0;a[d]!='\0'&&b[d]!=NULL;d++){
	     if(a[d]==b[d]){
	     	 continue;
		 }else return ERROR; 
	 }
	 if(a[d]=='\0'&&b[d]=='\0'){
	 	return OK;
	 }else return ERROR;
}

void travseAuthor(BTree t,char *author,FILE *fp){   //按顺序输出所有结点的信息(按关键字大小顺序输出) 
    if(NULL==t) return;
    travseAuthor(t->ptr[0],author,fp);
    int n = t->keynum;
    for(int i= 1;i<=n;i++){
       if(OK==comparechar(t->recptr[i]->author,author))
       printf("%3d\t %s\t\n",t->recptr[i]->key,t->recptr[i]->name);
	   fprintf(fp,"%3d\t %s\t\n",t->recptr[i]->key,t->recptr[i]->name);    
       travseAuthor(t->ptr[i],author,fp);
    }
    return;
}
void addNewBook(BTree &t,Record &e,FILE *fp){
	          result r;
	          int number;
              printf("请输入书号：");
              fprintf(fp,"请输入书号：");
              scanf("%d",&e.key);   
              fprintf(fp,"%d\n",e.key); 
              SearchBTree( t,e.key,r);
              if(r.tag==1) {
              	printf("该书已经存在，请输入要新增的数量：");
              	fprintf(fp,"该书已经存在，请输入要新增的数量：");
              	scanf("%d",&number);
              	fprintf(fp,"%d\n",number);
              	 r.pt->recptr[r.i]->reNumber += number;
              	 r.pt->recptr[r.i]->totalNumber += number;
              	printf("该书数量已增加\n");
              	fprintf(fp,"该书数量已增加\n");
                return ;
			  }
              else{
               printf("请输入书名：");
               fprintf(fp,"请输入书名：");
               scanf("%s",e.name);
			   fprintf(fp,"%s\n",e.name); 
               printf("请输入作者：");
               fprintf(fp,"请输入作者：");
               scanf("%s",e.author);
               fprintf(fp,"%s\n",e.author); 
               printf("请输入入库量：");
               fprintf(fp,"请输入入库量：");
               scanf("%d",&e.totalNumber); 
               fprintf(fp,"%d\n",e.totalNumber); 
               e.reNumber = e.totalNumber; 
               insertBTree(t,e.key,e);
               
			  }
}
void searchBook(BTree t,FILE *fp){   //按顺序输出所有结点的信息(按关键字大小顺序输出) 
             result r; 
             int key;
	          int number;
              printf("请输入书号：");
              fprintf(fp,"请输入书号：");
              scanf("%d",&key);  
			  fprintf(fp,"%d",&key);  
              SearchBTree( t,key,r);
              if(r.tag==1) {
              	printf("书号\t 书名\t作者\t现存量\t总库存\n");
                fprintf(fp,"书号\t 书名\t作者\t现存量\t总库存\n");
              	printf("%2d\t%s\t%s\t%3d\t%3d\n",r.pt->recptr[r.i]->key,r.pt->recptr[r.i]->name,r.pt->recptr[r.i]->author,r.pt->recptr[r.i]->reNumber,r.pt->recptr[r.i]->totalNumber);
                printf("以下为借阅者信息：\n"); 
                fprintf(fp,"%2d\t%s\t%s\t%3d\t%3d\n",r.pt->recptr[r.i]->key,r.pt->recptr[r.i]->name,r.pt->recptr[r.i]->author,r.pt->recptr[r.i]->reNumber,r.pt->recptr[r.i]->totalNumber);
                fprintf(fp,"以下为借阅者信息：\n"); 
				print(r.pt->recptr[r.i]->p,fp);
				return ;
			  }
			  printf("该书不存在，查询失败\n");
              fprintf(fp,"该书不存在，查询失败\n");
}
void testInsertDelete(BTree &t,	Record &e) {
    int number[18] = {35, 16, 18, 70, 5, 50, 22, 60, 13, 17, 12 , 45, 25, 42, 15, 90, 30, 7};
    int deleteNumber[5] = {45, 90, 50, 22, 42};
   // int booknum[18] = {15, 98 , 54, 68, 78,15,45,12, 70, 5, 50, 22, 60, 13, 17, 35, 16,12 };
	char name[][18] = {"数据结构","大学物理","大学英语","高等数学","线性代数","高等代数",
	                   "离散数学","网页设计","数字逻辑","近现代史","程序设计","电子技术",
					   "java课程","青春健康","算法设计","计算机网络","计组原理","工程数学",
					   };
	char author[][18] ={"陈","马","王","方","李","许",
	                    "陈","马","王","方","李","许",
	                    "陈","马","王","方","李","许",
						  }; 
	   for(int i=0;i<18;i++){
	   	  e.key = number[i];
	   	  e.name = name[i];
	   	  e.author = author[i];
	   	  e.reNumber = number[i];
          e.totalNumber = number[i];
          insertBTree(t,e.key, e);
	   }   
  	   deleteBTree(t,45);
	   deleteBTree(t, 90);
       deleteBTree(t, 50);
       deleteBTree(t, 22);
       deleteBTree(t, 42);
       
}
int test()
{
      BTree t = NULL ,q = NULL;
      Record e,e1;
      Status re;
	  int k ,i ;
      result r ;                                           
      int lev = 0;
      int key ; 
      char author[20];
      e.name =(char *) malloc(20*sizeof(char));
      e.author =(char *) malloc(20*sizeof(char));
      e.p = makeNode();
      
      e1.name =(char *) malloc(20*sizeof(char));
      e1.author =(char *) malloc(20*sizeof(char));
      e1.p = makeNode();
      
        FILE *fp = NULL; 
	   fp = fopen("log.txt","w"); 
       testInsertDelete(t,e1) ;
       
        while(TRUE){
         int n = 0;
         menu(fp); 
         printf("请输入操作: ");
         fprintf(fp, "请输入操作: ");
         scanf("%d",&n);
         fprintf(fp,"%d\n",n);
         if(n<0||n>10) continue;
         switch(n){   
		  case 0: exit(0);     
          case 1:
               addNewBook(t,e,fp);
               printf("=================\n");
               fprintf(fp,"=================\n");
               printBTree(t,lev,fp);
               printf("=================\n");
               fprintf(fp,"=================\n");
               break;
          case 2: 
		     printf("请输入要删除的书籍书号\n");   
			 fprintf(fp,"请输入要删除的书籍书号\n");           
             scanf("%d",&key);
             fprintf(fp,"%d\n",key);
             re = deleteBTree(t,key );
             if(ERROR==re){
             	 printf("不存在该书，删除失败\n");
             	 fprintf(fp,"不存在该书，删除失败\n");
			 }else{
			 	  printf("该书已移除\n"); 
			 	  fprintf(fp,"该书已移除\n"); 
			 }
             printf("=================\n");
             fprintf(fp,"=================\n");
             printBTree(t,lev,fp);
             printf("=================\n");
             fprintf(fp,"=================\n");
              break; 
          case 3 :
        	    printf("请输入想要借阅的书号\n"); 
        	    fprintf(fp,"请输入想要借阅的书号\n"); 
        	    scanf("%d",&key);
        	    fprintf(fp,"%d\n",key); 
		        re = borrow(t,key,fp);
		        if(OK==re){
		        	printf("借书成功\n");
		        	fprintf(fp,"借书成功\n"); 
				}else if(ERROR==re){
					printf("查无此书，请重新输入\n");
					fprintf(fp,"查无此书，请重新输入\n");
				}else if(OVERFLOW==re){
					printf("此书库存量为0，借阅失败\n");
					fprintf(fp,"此书库存量为0，借阅失败\n");
				}else{
					printf("您已借阅此书未还，请借阅其他书籍\n");
					fprintf(fp,"您已借阅此书未还，请借阅其他书籍\n");
				} 
		        break;
          case 4:
	    	    printf("输入要归还的书号\n"); 
                fprintf(fp,"输入书号\n"); 
        	    scanf("%d",&key);
        	    fprintf(fp,"%d",key); 
		        re = Return(t,key,fp);
		        if(OK==re){
		        	printf("还书成功\n");
                    fprintf(fp,"还书成功\n");
				}else if(ERROR==re){
					printf("查无此书，请重新输入\n");
                    fprintf(fp,"查无此书，请重新输入\n");
				}else if(OVERFLOW==re){
					printf("未借书，请重新输入\n");
                    fprintf(fp,"未借书，请重新输入\n");
				} 
	    	break;
	    	
        case 5:   //查看图书总信息（书号等） 
             printf("书号  书名\t  著作者\t剩余数\t   库存总量\n"); 
             fprintf(fp,"书号  书名  著作者  剩余数   库存总量\n"); 
             travseFor(t,fp);
             break;
             
	    case 6 :        //查找某一作者的所有信息； 
                 printf("请输入需要查找的作者名字\n");
                 fprintf(fp,"请输入需要查找的作者名字\n");
                 scanf("%s",author);
                 fprintf(fp,"%s",author);
                 travseAuthor( t, author,fp);
                 break;
         case 7:          //输出某本书的所有信息 
		        searchBook(t,fp);
				break; 
         case 8 :
             printf("=================\n");
             fprintf(fp,"=================\n");
             printBTree(t,lev,fp);
             printf("=================\n");
             fprintf(fp,"=================\n");
             break;
        
		case 9: 
		        destr(t);
                printf("B树已销毁\n"); 
				break;      
        default : 
              break;
        }     
     }   
	  fclose(fp); 
      return 0;
}

Status Stuborrow(BTree &t,int key,FILE *fp,int num){
	 result r ;
     BTree q ;
     person  e;
     e = makeNode();
     int i = 0;     
     SearchBTree( t,key,r);
     if(r.tag==0) return ERROR;
     q = r.pt;
     i = r.i;
     if(q->recptr[r.i]->reNumber<=0) return OVERFLOW;
     else{
  	    e->num = num;
	    if (SearchPer(q->recptr[i]->p,e->num)==OK){
	       return BORROW;
	    }else{
		   printf("输入姓名：");
		   fprintf(fp,"输入姓名：");
		   scanf("%s",e->name);
		   fprintf(fp,"%s\n",e->name);
		   addperson(q->recptr[r.i]->p, e);
		   q->recptr[r.i]->reNumber--;
		    return OK; 
	   }  
	 }      
}

Status StuReturn(BTree &t,int key,FILE *fp,int num){
	 result r ;
     BTree q ;
    
     int i = 0;     
     SearchBTree( t,key,r);
     if(r.tag==0) return ERROR;
        q = r.pt;
        i = r.i;
	    if (SearchPer(q->recptr[i]->p,num)==OK){
	    	deleteNode(q->recptr[i]->p,num);
	    	q->recptr[r.i]->reNumber++;
	        return OK;
	    }else{
		    return OVERFLOW; 
	   }  
}

void Stumenu(FILE *fp){
	printf("======菜单栏=====\n");
	printf("0：退出系统\n");
	printf("1: 借阅图书\n"); 
    printf("2: 归还图书\n");
    printf("3: 查看库存信息\n"); 
    printf("4: 查找某作者作品\n");
    printf("5：查找某本书所有信息\n");
    printf("6：凹表输出\n");
    printf("=================\n");
    fprintf(fp,"======菜单栏=====\n");        //输出到文件做日志 
    fprintf(fp,"0：退出系统\n");
	fprintf(fp,"1: 借阅图书\n"); 
    fprintf(fp,"2: 归还图书\n");
    fprintf(fp,"3: 查看库存信息\n"); 
    fprintf(fp,"4: 查找某作者作品\n\n");
    fprintf(fp,"5：查找某本书所有信息\n");
    fprintf(fp,"6：凹表输出\n");
    fprintf(fp,"=================\n");
}
int test2(int num){
	BTree t = NULL ,q = NULL;
      Record e,e1;
      Status re;
	  int k ,i ;
      result r ;                                           
      int lev = 0;
      int key ; 
      char author[20];
      e.name =(char *) malloc(20*sizeof(char));
      e.author =(char *) malloc(20*sizeof(char));
      e.p = makeNode();
      
      e1.name =(char *) malloc(20*sizeof(char));
      e1.author =(char *) malloc(20*sizeof(char));
      e1.p = makeNode();
      
        FILE *fp = NULL; 
	   fp = fopen("log.txt","w"); 
       testInsertDelete(t,e1) ;
       
       while(TRUE){
        int n = 0;
        Stumenu(fp); 
        printf("请输入操作: ");
        fprintf(fp, "请输入操作: ");
        scanf("%d",&n);
        fprintf(fp,"%d\n",n);
        if(n<0||n>10) continue;
        switch(n){   
		  case 0: return 0;     
          case 1 :
        	    printf("请输入想要借阅的书号\n"); 
        	    fprintf(fp,"请输入想要借阅的书号\n"); 
        	    scanf("%d",&key);
        	    fprintf(fp,"%d\n",key); 
		        re = Stuborrow(t,key,fp,num);
		        if(OK==re){
		        	printf("借书成功\n");
		        	fprintf(fp,"借书成功\n"); 
				}else if(ERROR==re){
					printf("查无此书，请重新输入\n");
					fprintf(fp,"查无此书，请重新输入\n");
				}else if(OVERFLOW==re){
					printf("此书库存量为0，借阅失败\n");
					fprintf(fp,"此书库存量为0，借阅失败\n");
				}else{
					printf("您已借阅此书未还，请借阅其他书籍\n");
					fprintf(fp,"您已借阅此书未还，请借阅其他书籍\n");
				} 
		        break;
          case 2:
	    	    printf("输入要归还的书号\n"); 
                fprintf(fp,"输入书号\n"); 
        	    scanf("%d",&key);
        	    fprintf(fp,"%d",key); 
		        re = StuReturn(t,key,fp,num);
		        if(OK==re){
		        	printf("还书成功\n");
                    fprintf(fp,"还书成功\n");
				}else if(ERROR==re){
					printf("查无此书，请重新输入\n");
                    fprintf(fp,"查无此书，请重新输入\n");
				}else if(OVERFLOW==re){
					printf("未借书，请重新输入\n");
                    fprintf(fp,"未借书，请重新输入\n");
				} 
	    	break;
	    	
        case 3:   //查看图书总信息（书号等） 
             printf("书号  书名\t  著作者\t剩余数\t   库存总量\n"); 
             fprintf(fp,"书号  书名  著作者  剩余数   库存总量\n"); 
             travseFor(t,fp);
             break;
             
	    case 4 :        //查找某一作者的所有信息； 
                 printf("请输入需要查找的作者名字\n");
                 fprintf(fp,"请输入需要查找的作者名字\n");
                 scanf("%s",author);
                 fprintf(fp,"%s",author);
                 travseAuthor( t, author,fp);
                 break;
         case 5:          //输出某本书的所有信息 
		        searchBook(t,fp);
				break; 
         case 6 :
             printf("=================\n");
             fprintf(fp,"=================\n");
             printBTree(t,lev,fp);
             printf("=================\n");
             fprintf(fp,"=================\n");
             break;
        default : 
              break;
        }     
     }   
	  fclose(fp); 
      return 0;
}

