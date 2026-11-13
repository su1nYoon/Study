#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATIONS 4
#define SLOTS 1000

int main(void)
{
    double bestP = 0.0;
    int bestTotalSuccess = -1;

    srand((unsigned int)time(NULL));

    printf("=== ALOHA Simulation ===\n");
    printf("조건: S1, S2, S3, S4가 독립적으로 전송 시도\n");
    printf("      1개만 전송하면 성공, 2개 이상이면 충돌, 0개면 유휴\n\n");

    printf(" p      성공   실패   유휴    S1    S2    S3    S4\n");
    printf("------------------------------------------------------\n");

    // p를 0.10부터 0.50까지 0.01씩 증가
    for (double p = 0.10; p <= 0.50 + 1e-9; p += 0.01)
    {
        int success = 0;
        int fail = 0;
        int idle = 0;

        // 각 스테이션의 성공 횟수
        int stationSuccess[STATIONS] = {0, 0, 0, 0};

        // 슬롯 반복
        for (int i = 0; i < SLOTS; i++)
        {
            int sendCount = 0;
            int sender = -1;   // 성공한 스테이션 번호 기록용

            // S1 ~ S4가 각각 독립적으로 전송 시도
            for (int j = 0; j < STATIONS; j++)
            {
                double r = (double)rand() / RAND_MAX;

                if (r < p)
                {
                    sendCount++;
                    sender = j;   // 현재 전송한 스테이션 번호
                }
            }

            // 결과 판정
            if (sendCount == 0)
            {
                idle++;
            }
            else if (sendCount == 1)
            {
                success++;
                stationSuccess[sender]++;
            }
            else
            {
                fail++;
            }
        }

        printf("%.2f   %4d   %4d   %4d   %4d  %4d  %4d  %4d\n",
               p, success, fail, idle,
               stationSuccess[0], stationSuccess[1],
               stationSuccess[2], stationSuccess[3]);

        // 전체 성공 횟수가 가장 큰 p 저장
        if (success > bestTotalSuccess)
        {
            bestTotalSuccess = success;
            bestP = p;
        }
    }

    printf("\n=== 최종 결과 ===\n");
    printf("가장 큰 성공 횟수를 만든 p 값 : %.2f\n", bestP);
    printf("그때의 총 성공 횟수          : %d\n", bestTotalSuccess);

    return 0;
}