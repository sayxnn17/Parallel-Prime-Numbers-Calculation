/*
AI Generated Solution
FASTprime — Parallel Prime Computation

Concepts Used:
fork(), signal(), kill(),
open(), write(), close(),
system(), execution time measurement
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

// Prime checking function (optimized trial division)
int isPrime(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// Signal handler
void signal_handler(int sig)
{
    printf("Signal received from child process\n");
}

int main()
{
    int rl, rh, n;

    printf("=== CPU INFORMATION ===\n");
    system("lscpu");

    printf("\nEnter lower range: ");
    scanf("%d", &rl);

    printf("Enter upper range: ");
    scanf("%d", &rh);

    printf("Enter number of child processes: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid process count\n");
        return 0;
    }

    // Open file with error check
    int fd = open("prime_ai.txt",
                  O_CREAT | O_WRONLY | O_TRUNC,
                  0644);

    if (fd < 0)
    {
        perror("File open failed");
        exit(1);
    }

    signal(SIGUSR1, signal_handler);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int total = rh - rl + 1;
    int chunk = total / n;
    int remainder = total % n;

    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            int start_num = rl + i * chunk;
            int end_num = start_num + chunk - 1;

            // Last child handles remainder
            if (i == n - 1)
                end_num += remainder;

            for (int num = start_num; num <= end_num; num++)
            {
                if (isPrime(num))
                {
                    char buffer[50];
                    sprintf(buffer, "%d\n", num);
                    write(fd, buffer, strlen(buffer));
                }
            }

            // Notify parent
            kill(getppid(), SIGUSR1);

            close(fd);
            exit(0);
        }
    }

    // Parent waits
    for (int i = 0; i < n; i++)
        wait(NULL);

    gettimeofday(&end, NULL);

    double exec_time =
        (end.tv_sec - start.tv_sec) +
        (end.tv_usec - start.tv_usec) / 1e6;

    printf("\nTotal Execution Time = %f seconds\n",
           exec_time);

    close(fd);

    return 0;
}

