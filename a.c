#include <stdio.h>
#include <math.h>

void print(double *,int);
double dataprocess(double *p, int cnt); 

void main(){
double data[42];
int num = 0;
int i=0;
printf("처리할 실수의 갯수는");
scanf("%d",&num);

printf("\n처리할 실수 %d개를 입력하세요.\n",num);

for(i=0; i<num; i++)
{
scanf("%lf",data + i);
}
dataprocess(data,num);

printf("\n===========자료처리==========\n");
printf("입력자료: ");
print(data,num);
printf("자료 합: %.2f\n",dataprocess(data,num));
printf("자료 평균 : %.2f\n", *(data+num));
printf("자료 분산 : %.2f\n", *(data+num+1));
printf("자료 표준편차: %.4f\n",sqrt(*(data+num+1)));
}

double dataprocess(double *p, int cnt)
{
double sum = 0, sqsum = 0;
int i=0;
for(i=0; i< cnt; i++)
{
sum += *p;
sqsum = *p * *p;
p++;}

*p++ = sum/cnt;
*p++ = sqsum/cnt;

return sum;};

void print(double *p, int cnt)
{
int i=0;
for(i=0; i<cnt; i++)
{
printf("%.2f", *p++);
printf("\n");
}
}




