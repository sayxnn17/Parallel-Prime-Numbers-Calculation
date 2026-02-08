#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

 
int isPrime(int n) // function to check wheter a number is prime or not
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

// function: signal handler
void done(int sig)
{
    printf("\n Child completed its work \n");
}

int main()
{
    int rl, rh;
    int n;

    printf("CPU Details:\n");
    system("lscpu");

    printf("\nEnter range (rl rh): \n ");  //range of the input
    
    scanf("%d %d", &rl, &rh);

    printf("Enter number of child processes: "); /* no.of children*/
    scanf("%d", &n);

    /*for opening and granting files the operations that we can perform*/
    int fd = open("prime.txt",
                  O_CREAT | O_WRONLY | O_TRUNC,
                  0644);

    /* for registering signal*/
    signal(SIGUSR1, done);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int size = (rh - rl + 1) / n;

    for(int i = 0; i < n; i++)
    {
        pid_t pid = fork();

        if(pid == 0)   // going into the child process
        {
            int s = rl + i * size;
            int e;

            if(i == n-1)
                e = rh;
            else
                e = s + size - 1;

            // finding primes
            for(int j = s; j <= e; j++)
            {
                if(isPrime(j))
                {
                    char buf[50];
                    sprintf(buf, "%d\n", j);
                    write(fd, buf, strlen(buf));
                }
            }

            // informing parent
            kill(getppid(), SIGUSR1);

            close(fd);
            exit(0);
        }
    }

    // parent is waiting
    for(int i = 0; i < n; i++)
        wait(NULL);

    gettimeofday(&end, NULL);

    double t =
        (end.tv_sec - start.tv_sec) +
        (end.tv_usec - start.tv_usec)/1e6;

    printf("\n Execution Time = %f sec \n", t);

    close(fd);

}

