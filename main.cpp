#include"head.h"
int main(){
   int managernum = 6666;	
   int managerkey = 6666;
   int stunum = 4422;
   int stukey = 4422;
   int num, key,flag; 
   printf("***********��ӭ��¼ͼ�����ϵͳ************************\n");
   while(1){
   	   printf("*******1:��¼,0:�˳�,��ѡ��*******\n");
   	   scanf("%d",&flag);
   	   if(1==flag){
   	   	     printf("������ѧ�ţ�");
             scanf("%d",&num); 
             printf("���������룺");
             scanf("%d",&key);
             if(num==managernum&&managerkey==key){
   	            test();
             }else if(num==stunum&&stukey==key){
     	        test2(key);
	         }else{
	  	        printf("ѧ�Ż������������������\n");
	     }
       }else if(0==flag){
     	  exit(0);
	 }
   }  
 }

