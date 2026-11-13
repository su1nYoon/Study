#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // sleep

#define N 7

int q[N];
int f = 0, r = 0;

pthread_mutex_t m; // 잠금

// 비었는지
int empty() {
    return f == r; 
}

// 가득 찼는지
int full() { 
    return (r + 1) % N == f; 
}

// 넣기
void in(int x) {
    r = (r + 1) % N;
    q[r] = x;
    printf("In: %d\n", x);
}

// 빼기
int out() {
    f = (f + 1) % N;
    return q[f];
}

// 생산자 (5개 넣기)
void* p(void* arg) {
    int data[5] = {10, 20, 30, 40, 50};

    for(int i = 0; i < 5; i++) {
        pthread_mutex_lock(&m);

        if(!full())
            in(data[i]);

        pthread_mutex_unlock(&m);

        sleep(1); // 보기 쉽게
    }
    return NULL;
}

// 소비자 (3개 빼기)
void* c(void* arg) {
    for(int i = 0; i < 3; i++) {
        pthread_mutex_lock(&m);

        if(!empty()) {
            int v = out();
            printf("Out: %d\n", v);
        }

        pthread_mutex_unlock(&m);

        sleep(2); // 보기 쉽게
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&m, NULL);

    pthread_create(&t1, NULL, p, NULL);
    pthread_create(&t2, NULL, c, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}