#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <cstring>

#include "logger.h"

using namespace std;


void check()
{
    if (errno == -1)
    {
        throw runtime_error(strerror(errno));
    }
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Usage: sudo ./Audit <pid>" << endl;
        cout << "       or" << endl;
        cout << "       sudo ./Audit `pidof <process name>`" << endl;
        return EXIT_FAILURE;
    }

    int pid = stoi(argv[1]);

    Logger logger(pid);

    // Attach to the process
    ptrace(PTRACE_ATTACH, pid, nullptr, nullptr);
    check();
    logger.log("Attached");

    // Set listener
    ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);
    check();
    logger.log("Set sys call listener");

    // Listen loop
    int status;
    waitpid(pid, &status, 0);
    user_regs_struct regs;
    while (WIFSTOPPED(status))
    {
        // Wait for a sys call
        ptrace(PTRACE_SYSCALL, pid, nullptr, nullptr);
        check();
        waitpid(pid, &status, 0);

        // Get all general purpose registers
        ptrace(PTRACE_GETREGS, pid, 0, &regs);
        check();

        logger.log(regs.orig_rax);
    }

    // Detach
    ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
    logger.log("Detached");

    return 0;
}
