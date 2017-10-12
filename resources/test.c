#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[])
{
    printf("About to perform exec syscall\n");
    asm
    (
    "pushl $0x0068732f\n\t" // "/sh\0"
    "pushl $0x6e69622f\n\t" // "/bin"
    "movl %esp, %ebx\n\t" // Program pathname
    "pushl $0x0\n\t" // argv null-terminator
    "pushl %ebx\n\t" // first arg in argv
    "movl %esp, %ecx\n\t" // point to argv list on stack
    "movl $0x0, %edx\n\t" // No environment
    "movl 0x0000000b, %eax\n\t" // exec syscall ID
    "int $0x80" // trigger syscall
    );
printf("If we got here the syscall failed!\n");
}
