#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define MAX 45

void print_stars(); //*30개 출력
void s(); //print_stars함수를 반환 //void에 return이 포함되어 있음
int max(x, y);
int min(x, y);
void rand_1();

int main(void)
{
    int x, y, larger, smaller;
    s();
    printf("값 2개를 입력하시오 : ");
    scanf("%d %d", &x, &y);
    larger = max(x, y);
    printf("더 큰 값은 %d입니다. \n", larger);
    smaller = min(x, y);
    printf("더 작은 값은 %d입니다. \n", smaller);
    rand_1();

    return 0;
}

void print_stars() //*30개 출력
{
    for(int i=0; i<30; i++)
        printf("*");
}

void s() //print_stars함수를 반환 //void에 return이 포함되어 있음
{
    return print_stars();
    printf("\n");
}

int max(int x, int y)
{
    if( x > y)
        return x;
    else
        return y;
}

int min(int x, int y)
{
    if( x < y)
        return x;
    else
        return y;
}

void rand_1()   //1번째 함수 : 10개의 난수 출력(x,x) 반환값 없고
{
    int i;
    srand( (unsigned)time( NULL ));
    for(i = 0; i < 10; i++)
        printf("%d", 1+rand()%MAX);
    printf("\n");
}

void rand_2()   //2번째 함수 : 10개의 난수 화면에 출력 반환값 없고 10개의
{
    int i;
    srand( (unsigned)time( NULL ));
    for(i = 0; i < 10; i++)
        printf("%d", 1+rand()%MAX);
    printf("\n");
}

void rand_3()   //3번째 함수 : 10개의 난수 화면에 출력 반환값이 있음  10개의 난수 중 최대값
{
    int i;
    srand( (unsigned)time( NULL ));
    for(i = 0; i < 10; i++)
        printf("%d", 1+rand()%MAX);
    printf("\n");
}

void rand_4()   //4번째 함수 : 10개의 난수 화면에 출력 반환값이 없고 난수 중 최대값 출력
{
    int i;
    srand( (unsigned)time( NULL ));
    for(i = 0; i < 10; i++)
        printf("%d", 1+rand()%MAX);
    printf("\n");
}