#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// 지수분포 난수 생성 (M)
double get_exponential(double lambda) {
    double u;
    do {
        u = (double)rand() / (double)RAND_MAX;
    } while (u <= 0.0);
    return -log(u) / lambda;
}

// 패킷(프레임) 정보 저장용 구조체
typedef struct {
    int id;             // 패킷 번호
    double start_time;  // 전송 시작 시각
    double end_time;    // 전송 종료 시각
    int collided;       // 충돌 여부 (0: 성공 후보, 1: 충돌)
} Frame;

int main() {
    srand(time(NULL));

    // 설정값
    double arrival_rate = 0.8;     // 단위 시간당 평균 도착률 (lambda)
    double frame_time = 1.0;       // 고정 전송 시간(서비스 시간) = D.  (D)
    int total_frames = 30;         // 생성할 총 프레임 수

    Frame frames[1000];

    double current_time = 0.0;

    printf("=== Pure ALOHA 시뮬레이션 (M/D/1 기반) ===\n");
    printf("도착률(lambda): %.2f\n", arrival_rate);
    printf("고정 전송 시간(frame time): %.2f\n", frame_time);
    printf("총 프레임 수: %d\n\n", total_frames);

    // 1단계: 프레임 도착 및 전송 시작 시각 생성
    for (int i = 0; i < total_frames; i++) {
        double inter_arrival = get_exponential(arrival_rate);
        current_time += inter_arrival;

        frames[i].id = i + 1;
        frames[i].start_time = current_time;
        frames[i].end_time = current_time + frame_time;
        frames[i].collided = 0;
    }

    // 2단계: Pure ALOHA 충돌 판정
    // 두 프레임의 전송 시간이 겹치면 충돌
    for (int i = 0; i < total_frames; i++) {
        for (int j = i + 1; j < total_frames; j++) {
            // [start_i, end_i] 와 [start_j, end_j] 가 겹치는지 확인
            if (frames[i].start_time < frames[j].end_time &&
                frames[j].start_time < frames[i].end_time) {
                frames[i].collided = 1;
                frames[j].collided = 1;
            }
        }
    }

    // 3단계: 결과 출력
    int success_count = 0;
    int collision_count = 0;

    printf("번호\t시작시각\t종료시각\t결과\n");
    printf("-------------------------------------------------\n");

    // 변경
    for (int i = 0; i < total_frames; i++) {
        if (frames[i].collided) {
            printf("%d\t%.4f\t\t%.4f\t\t충돌\n",
                   frames[i].id,
                   frames[i].start_time,
                   frames[i].end_time);
            collision_count++;
        } else {
            printf("%d\t%.4f\t\t%.4f\t\t성공\n",
                   frames[i].id,
                   frames[i].start_time,
                   frames[i].end_time);
            success_count++;
        }
    }

    // 4단계: 통계
    printf("\n=== 시뮬레이션 결과 요약 ===\n");
    printf("전체 프레임 수: %d\n", total_frames);
    printf("성공 프레임 수: %d\n", success_count);
    printf("충돌 프레임 수: %d\n", collision_count);
    printf("성공률: %.2f%%\n", (double)success_count / total_frames * 100.0);
    printf("충돌률: %.2f%%\n", (double)collision_count / total_frames * 100.0);

    return 0;
}