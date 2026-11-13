#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_QUEUE 10 // 대기 큐의 최대 길이

// 지수 분포 난수 생성기
double get_exponential(double lambda) {
    double u;
    do {
        u = (double)rand() / (double)RAND_MAX;
    } while (u <= 0.0);
    return -log(u) / lambda;
}

int main() {
    srand(time(NULL));

    double arrival_rate = 3.0; // 분당 3명 도착 (람다)
    double service_rate = 2.5; // 분당 2.5명 처리 (뮤) - 처리보다 도착이 빠른 과부하 상황 가정

    double current_time = 0.0;
    double next_arrival_time = get_exponential(arrival_rate);
    double service_finish_time = 1e10; // 서버 휴식 중

    int queue_count = 0;         // 현재 대기실에 있는 사람 수
    int total_arrival = 0;       // 총 도착 시도 횟수
    int dropped_customers = 0;  // 자리가 없어 돌아간 사람 수
    int finished_customers = 0; // 서비스 완료

    printf("--- M/M/1/%d 시뮬레이션 시작 ---\n", MAX_QUEUE);
    printf("설정: 도착 %.1f, 처리 %.1f, 큐 제한 %d\n\n",
           arrival_rate, service_rate, MAX_QUEUE);

    // 총 20명의 도착 시도
    while (total_arrival < 20) {

        if (next_arrival_time < service_finish_time) {
            // [이벤트 1] 손님 도착
            current_time = next_arrival_time;
            total_arrival++;

            if (queue_count < MAX_QUEUE) {
                // 자리가 있는 경우
                queue_count++;
                printf("[시각 %.2f] 손님 입장! (대기열: %d/%d)\n",
                       current_time, queue_count, MAX_QUEUE);

                // 서버가 비어있으면 즉시 서비스 시작
                if (queue_count == 1) {
                    service_finish_time =
                        current_time + get_exponential(service_rate);
                }
            } else {
                // 자리 없음 → 유실
                dropped_customers++;
                printf("[시각 %.2f] 자리 없음! 손님 유실 (누적 유실: %d)\n",
                       current_time, dropped_customers);
            }

            // 다음 도착 시간
            next_arrival_time =
                current_time + get_exponential(arrival_rate);

        } else {
            // [이벤트 2] 서비스 완료
            current_time = service_finish_time;
            queue_count--;
            finished_customers++;

            printf("[시각 %.2f] 서비스 완료 (남은 대기: %d)\n",
                   current_time, queue_count);

            if (queue_count > 0) {
                service_finish_time =
                    current_time + get_exponential(service_rate);
            } else {
                service_finish_time = 1e10;
            }
        }
    }

    printf("\n--- 시뮬레이션 결과 요약 ---\n");
    printf("총 도착 시도: %d회\n", total_arrival);
    printf("성공적 처리: %d회\n", finished_customers);
    printf("유실된 손님: %d회\n", dropped_customers);
    printf("유실률(Loss Probability): %.2f%%\n",
           ((double)dropped_customers / total_arrival) * 100);

    return 0;
}