#include <stdio.h>
#define N 8

int q[N];
int f = 0;
int r = 0;

// 공백 상태
int empty() {
    return f == r; 
}

// 포화 상태
int full() {
    return (r + 1) % N == f;
}

// 넣기 (IN)
void in(int x) {
    if (full()) {
        printf("포화 상태\n");
        return;
    }

    r = (r + 1) % N;
    q[r] = x;
    printf("IN: %d\n", x);
}

// 빼기 (OUT)
int out() {
    if (empty()) {
        printf("공백 상태\n");
        return -1;
    }
    f = (f + 1) % N;
    return q[f];
}

// 출력
void print() {
    int i = (f + 1) % N;
    printf("큐: ");

    while (i != (r + 1) % N) {
        printf("%d ", q[i]);
        i = (i + 1) % N;
    }
    printf("\n");
}

int main() {

    // 10개 IN
    for(int i = 1; i <= 10; i++) {
        in(i * 10);   // 10,20,30,...
    }

    printf("\n");
    print();
    printf("\n");

    // 3개 OUT
    printf("OUT: %d\n", out());
    printf("OUT: %d\n", out());
    printf("OUT: %d\n", out());
    printf("\n");
    print();

    return 0;
}