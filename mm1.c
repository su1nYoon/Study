#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// 지수 분포 난수 생성기
double get_exponential(double lambda) {     //서비스 시간
    double u;

    do {
        u = (double)rand() / (double)RAND_MAX;
    } while (u <= 0.0);

    return -log(u) / lambda;
}

int main() {
    srand(time(NULL));

    double arrival_rate = 2.0;   // 1분당 평균 2명 도착 (lambda)
    double service_rate = 2.5;   // 1분당 평균 2.5명 처리 (mu)

    double current_time = 0.0;
    double next_arrival_time = get_exponential(arrival_rate);
    double service_finish_time = 1e10;  // 서버가 비어있음을 의미

    int queue_count = 0;        // 시스템 내 손님 수
    int total_customers = 10;   // 처리할 총 손님 수

    printf("--- M/M/1 큐 시뮬레이션 시작 ---\n");
    printf("평균 도착: %.1f명/분, 평균 처리: %.1f명/분\n\n",
           arrival_rate, service_rate);

    for (int i = 0; i < total_customers; ) {

        if (next_arrival_time < service_finish_time) {
            // [사건 1] 새로운 손님 도착
            current_time = next_arrival_time;
            queue_count++;

            printf("[시각 %.2f] 손님 도착! (현재 대기: %d명)\n",
                   current_time, queue_count);

            // 서버가 쉬고 있었다면 바로 서비스 시작
            if (queue_count == 1) {
                service_finish_time =
                    current_time + get_exponential(service_rate);
            }

            // 다음 손님 도착 시간 예약
            next_arrival_time =
                current_time + get_exponential(arrival_rate);

        } else {
            // [사건 2] 서비스 완료
            current_time = service_finish_time;
            queue_count--;
            i++;  // 처리 완료된 손님 수 증가

            printf("[시각 %.2f] 서비스 완료! (남은 대기: %d명)\n",
                   current_time, queue_count);

            // 대기자가 남아있다면 다음 서비스 시작
            if (queue_count > 0) {
                service_finish_time =
                    current_time + get_exponential(service_rate);
            } else {
                service_finish_time = 1e10;  // 서버가 다시 쉼
            }
        }
    }

    printf("\n시뮬레이션 종료. 수고하셨습니다!\n");

    return 0;
}