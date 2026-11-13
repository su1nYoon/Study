#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;
void *runner1(void *param);    // +1
void *runner2(void *param);    // -1

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    sum = 0;

    pthread_create(&tid1, &attr, runner1, argv[1]);
    pthread_create(&tid2, &attr, runner2, argv[1]);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("sum = %d\n", sum);

    return 0;
}

// +1
void *runner1(void *param)
{
    int i, upper = atoi((char *)param);

    for(i = 0; i < upper; i++)
        sum += 1;
    
    pthread_exit(0);
}

void *runner2(void *param)
{
    int i, upper = atoi((char *)param);

    for(i = 1; i <= upper; i++)
        sum -= 1;

    pthread_exit(0);
}