#include <iostream>
#include <sys/sysctl.h>
#include <cstring>
#include <cstdlib>
#include <cctype>

int main()
{
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    size_t len = 0;
    if (sysctl(mib, 4, NULL, &len, NULL, 0) == -1)
    {
        std::cerr << "Failed to get process information\n";
        return 1;
    }
    struct kinfo_proc* kp = (struct kinfo_proc*)malloc(len);
    if (sysctl(mib, 4, kp, &len, NULL, 0) == -1)
    {
        std::cerr << "Failed to get process information\n";
        free(kp);
        return 1;
    }
    int nprocs = len / sizeof(struct kinfo_proc);
    for (int i = 0; i < nprocs; i++)
    {
        std::cout << kp[i].kp_proc.p_pid << "\t" << kp[i].kp_proc.p_comm << std::endl;
    }
    free(kp);
    return 0;
}

