#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 400

int main(){
	FILE *f;
	char vanban[MAX];
	char noi[MAX];
	//yeucau1: nhap noi dung va ghi vao file
	printf("Nhap van ban:");
	fgets(vanban, MAX , stdin);
	f= fopen("C1t.txt","w");
	if(f==NULL){
	    printf("loi mo file");
	    return 1;
	}
	fputs(vanban,f);
	fclose(f);
	//yeucau2:doc va in noi dung tu file
	printf("\nNoi dung file:");
	f= fopen("C1t.txt", "r");
	if(f==NULL){
	printf("loi mo file");
	return 1;	
    }
    while(fgets(vanban,MAX,f)!=NULL){
        printf("%s",vanban);
	}
	fclose(f);
//yeucau3:doc,in va noi them thong tin vao cuoi file
   printf("\n Nhap thong tin muon noi them:");
   fgets(noi,MAX,stdin);
   f=fopen("C1t.txt","a");
   if(f==NULL){
	    printf("loi mo file");
	    return 1;
	}
	fputs(noi,f);
	fclose(f);
	
	f=fopen("C1t.txt","r");
	if(f==NULL){
	printf("loi mo file");
	return 1;	
	}
	while(fgets(vanban,MAX,f)!=NULL){
	printf("%s",vanban);	
	}
	fclose(f);
	return 0;	
}
