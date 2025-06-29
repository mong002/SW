#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fp;
    char file[100];
    char command[100] = "\"C:\\Program Files\\IrfanView\\i_view64.exe\"";

    printf("읽을 파일 이름을 입력하시오 : ");
    scanf("%s", file);

    fp = fopen(file, "r");
    if( fp == NULL )
        printf("파일 열기 실패\n");
    else
        printf("파일 열기 성공\n");

    strcat(command, " ");
    strcat(command, file);

    printf("실행 명령어: %s\n", command); // 디버깅용 출력

    system(command);

    return 0;
}
