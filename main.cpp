#include"head.h"
int main(){
   int managernum = 6666;	
   int managerkey = 6666;
   int stunum = 4422;
   int stukey = 4422;
   int num, key,flag; 
   printf("***********欢迎登录图书管理系统************************\n");
   while(1){
   	   printf("*******1:登录,0:退出,请选择：*******\n");
   	   scanf("%d",&flag);
   	   if(1==flag){
   	   	     printf("请输入学号：");
             scanf("%d",&num); 
             printf("请输入密码：");
             scanf("%d",&key);
             if(num==managernum&&managerkey==key){
   	            test();
             }else if(num==stunum&&stukey==key){
     	        test2(key);
	         }else{
	  	        printf("学号或密码错误，请重新输入\n");
	     }
       }else if(0==flag){
     	  exit(0);
	 }
   }  
 }

