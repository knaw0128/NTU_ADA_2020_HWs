#include<stdio.h>
int main(){
    int lar=80;
    printf("1\n");
    printf("%d %d\n",lar,lar-1);
    for(int a=0;a<lar-1;a++){
        printf("%d %d\n",a,a+1);
    }
    return 0;
}