//SO IS1 222A LAB09
//Vitalii Natalevych
//nv53790@zut.edu.pl


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(int argc, char ** argv) {
    if(argc !=2){
        fprintf(stderr,"False input argument! Input must contain ONLY one argument!\n");
        return 1;
    }
    int len = strlen(argv[1]);
    if(len>25 || len < 1){
        fprintf(stderr,"False input argument! Input length must be from 1 to 25!\n");
        return 1;
    }
    char * end;
    long numb = strtol(argv[1],&end,10);
    errno = 0;
    if(errno || *end){
        fprintf(stderr,"False input argument! Input must included only digits!\n");
        return 1;
    }

    if(len == 1){
        return numb;
    }
    char arg1[(len/2)+3];
    char arg2[(len/2)+(len%2)+3];
    strncpy(arg1,"p ",2);
    strncpy(arg2,"p ",2);
    char  first_half[(len/2)+1];
    char second_half[(len/2)+(len%2)+1];
    strncpy(first_half,argv[1],(len/2));
    strncpy(second_half,argv[1]+(len/2),(len/2)+(len%2));
    first_half[(len/2)] = '\0';
    second_half[(len/2)+len%2] = '\0';
    strcat(arg1,first_half);
    strcat(arg2,second_half);


    STARTUPINFO s1,s2;
    PROCESS_INFORMATION p1,p2;

    memset(&s1,0,sizeof(s1));
    memset(&s2,0,sizeof(s2));

    memset(&p1,0,sizeof(p1));
    memset(&p2,0,sizeof(p2));

    s1.cb = sizeof(s1);
    s2.cb = sizeof(s2);

    if(!CreateProcessA(
            "lab9c.exe",
            arg1,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &s1,
            &p1
            )){
        fprintf(stderr,"Failed Process %d",GetLastError());
    }

    if(!CreateProcessA(
            "lab9c.exe",
            arg2,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            "D:\\so\\lab9c\\cmake-build-debug",
            &s2,
            &p2
    )){
        fprintf(stderr,"Failed Process %d",GetLastError());
    }

    HANDLE children[2] = {p1.hProcess,p2.hProcess};
    WaitForMultipleObjects(2,children,1,INFINITE);

    DWORD ec1,ec2;
    GetExitCodeProcess(p1.hProcess,&ec1);
    GetExitCodeProcess(p2.hProcess,&ec2);

    printf("%d  %d 			%s %d \n",GetCurrentProcessId(),p1.dwProcessId,first_half,ec1);
    printf("%d  %d 			%s %d \n",GetCurrentProcessId(),p2.dwProcessId,second_half,ec2);
    CloseHandle(p1.hProcess);
    CloseHandle(p1.hThread);
    CloseHandle(p2.hProcess);
    CloseHandle(p2.hThread);
    int sum =(int) ec1 + (int) ec2;

    return sum;

}
