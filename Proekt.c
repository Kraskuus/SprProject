#include <stdio.h>
#include <stdlib.h>



struct persons
{
	int id;
	int years;
	int egn;
	char name[20];
	char diagnosa[20];
	char prognosa[30];
};



	int main (void)
{  

  FILE *fp;
  struct persons s;
 
  fp=fopen("registry.txt","wb");
  if(fp==NULL){
  	printf("Error");
  	exit(1);
  }   

printf("Enter Person id \n");
scanf("%d",&s.id);
printf("Enter Person name \n");
fflush(stdin);
gets(s.name);



fwrite(&s,sizeof(struct persons),1,fp);
printf("Naise");
fclose(fp);

}






