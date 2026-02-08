#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

// function to check prime
int isPrime(int n)
{
    if(n < 2)
        return 0;

    for(int i = 2; i <= n/2; i++)
    {
        if(n % i == 0)
            return 0;
    }

    return 1;
}

// signal handler
void done(int sig)
{
    printf("Child completed its work\n");
}

int main()
{
    int rl, rh;
    int n;

    printf("CPU Details:\n");
    system("lscpu");

    // input range
    printf("\nEnter range (rl rh): \n ");
    
    scanf("%d %d", &rl, &rh);

    // number of children
    printf("Enter number of child processes: ");
    scanf("%d", &n);

    // open file
    int fd = open("prime.txt",O_CREAT | O_WRONLY | O_TRUNC,0644);

    // register signal
    signal(SIGUSR1, done);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int size = (rh - rl + 1) / n;

    for(int i = 0; i < n; i++)
    {
        pid_t pid = fork();

        if(pid == 0)   // child
        {
            int s = rl + i * size;
            int e;

            if(i == n-1)
                e = rh;
            else
                e = s + size - 1;

            // find primes
            for(int j = s; j <= e; j++)
            {
                if(isPrime(j))
                {
                    char buf[50];
                    sprintf(buf, "%d\n", j);
                    write(fd, buf, strlen(buf));
                }
            }

            // inform parent
            kill(getppid(), SIGUSR1);

            close(fd);
            exit(0);
        }
    }

    // parent waits
    for(int i = 0; i < n; i++)
        wait(NULL);

    gettimeofday(&end, NULL);

    double t =
        (end.tv_sec - start.tv_sec) +
        (end.tv_usec - start.tv_usec)/1e6;

    printf("\nExecution Time = %f sec\n", t);

    close(fd);

}

