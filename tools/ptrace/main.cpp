#include <iostream>
#include <sys/ptrace.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <map>

using namespace std;

map<int, const char *> syscallNames;

void fillSyscallNames()
{
#include "syscall_names.cpp"
}

void child(int argc, char **argv)
{
    ptrace(PTRACE_TRACEME, 0, 0, 0);

    // argv array is null terminated
    execvp(argv[0], argv);

    perror("execv");
}

void parent(pid_t pid)
{
    fillSyscallNames();

    int status;
    waitpid(pid, &status, 0);

    ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);

    while (!WIFEXITED(status))
    {
        struct user_regs_struct state;

        ptrace(PTRACE_SYSCALL, pid, 0, 0);
        waitpid(pid, &status, 0);

        if (WIFSTOPPED(status) && (WSTOPSIG(status) & 0x80))
        {
            ptrace(PTRACE_GETREGS, pid, 0, &state);

            unsigned long long int syscallNumber = state.orig_rax;
            const char * syscallName = syscallNames[syscallNumber];
            if (syscallName == nullptr)
            {
                syscallName = "-";
            }

            printf("%-12s   %3llu\n", syscallName, state.orig_rax);

            /*if (state.orig_rax == 1)
            {
                // write syscall. replace text.
                char * text = (char *)state.rsi;
                ptrace(PTRACE_POKETEXT, pid, (void*)(text), 0x6463626164636261); //abcdabcd
            }*/

            ptrace(PTRACE_SYSCALL, pid, 0, 0);
            waitpid(pid, &status, 0);
        }
    }
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("USAGE: ptrace program arg0 arg1 arg2 ...\n");
        return -1;
    }

    pid_t pid = fork();
    if (pid)
    {
        parent(pid);
    }
    else
    {
        child(argc - 1, argv + 1);
    }

    return 0;
}

