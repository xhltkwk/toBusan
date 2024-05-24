#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// 파라미터
#define LEN_MIN 15 // 열차 길이
#define LEN_MAX 50
#define STM_MIN 0 // 마동석 체력
#define STM_MAX 5
#define PROB_MIN 10 // 움직일 확률
#define PROB_MAX 90
#define AGGRO_MIN 0 // 어그로 범위
#define AGGRO_MAX 5 

// 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

// 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1 
#define ACTION_PULL 2

int length, prob, stamina;
int mc, mz, mm, turn;
int num1, num2;
int c_aggro, m_aggro;
int m_pull_success;

void intro() { //인트로
    printf("게임을 시작합니다.\n");
    printf("\n좀비에게서 탈출하세요!\n");
    printf("\n");

    do {
        printf("train Length(15~50)>>\n");
        scanf_s("%d", &length);

    } while (length < LEN_MIN || length > LEN_MAX);

    do {
        printf("madongseok stamina(0~5)>>\n");
        scanf_s("%d", &stamina);

    } while (stamina < STM_MIN || stamina > STM_MAX);

    do {
        printf("percentile probability 'p'(10~90)>>\n");
        scanf_s("%d", &prob);

    } while (prob < PROB_MIN || prob > PROB_MAX);

    printf("\n");
}

void printTrain() { //열차값 출력
    for (int j = 0; j < 2; j++) {
        if (j == 1) {
            printf("#");
            for (int n = 0; n < length - 2; n++) {
                if (n == mc) printf("C");
                else if (n == mz) printf("Z");
                else if (n == mm) printf("M");
                else printf(" ");
            }
            printf("#\n");
        }
        for (int i = 0; i < length; i++) printf("#");
        printf("\n");
    }
    printf("\n");
}

void position() { //위치 이동 rand값
    int r = rand() % 100;
    if (r <= 100 - prob) {
        --mc;
        ++num1;
    }
    int r1 = rand() % 100;
    ++turn;
    if (turn % 2 == 1 && r1 <= prob) {
        --mz;
        ++num2;
    }
}

void outro() { //아웃트로
    if (mc == 0) {
        printf("SUCCESS!\n탈출 성공!");
        exit(0);
    }
    if (mc == mz - 1) {
        printf("GAME OVER\n시민이 좀비에게 먹혔습니다.!");
        exit(0);
    }
    printf("Citizen : %d -> %d (aggro: %d)\n", mc + 1, mc, c_aggro);
    if (turn % 2 == 1 && num2) {
        printf("Zombie : %d -> %d\n", mz + 1, mz);
    }
    else {
        printf("Zombie : stay %d\n", mz);
    }
    printf("madongseok: stay %d (aggro: %d, stamina: %d)\n", mm, m_aggro, stamina);
    printf("\n");
}

void movePhase() { //이동 페이즈
    printf("<이동> 페이즈:\n");

    printTrain(); // 열차값 상태 출력

    // 시민 이동
    int r = rand() % 100;
    if (r < (100 - prob)) {
        if (c_aggro < AGGRO_MAX) {
            --mc;
            c_aggro++;
        }
        printf("시민 이동: 왼쪽으로 이동 (현재 위치: %d)\n", mc);
    }
    else {
        if (c_aggro > AGGRO_MIN) {
            c_aggro--;
        }
        printf("시민 이동: 제자리 대기 (현재 위치: %d)\n", mc);
    }

    // 좀비 이동
    if (turn % 2 == 0 && !m_pull_success) {
        if (c_aggro >= m_aggro) {
            --mz;
            printf("좀비 이동: 시민을 향해 이동 (현재 위치: %d)\n", mz);
        }
        else {
            --mz;
            printf("좀비 이동: 마동석을 향해 이동 (현재 위치: %d)\n", mz);
        }
    }
    else {
        printf("좀비 이동: 이동 불가능 (현재 위치: %d)\n", mz);
    }

    // 마동석 이동
    printf("마동석 이동 (현재 위치: %d, 1: 왼쪽, 0: 이동 안 함)>>\n", mm);
    int move;
    scanf_s("%d", &move);
    if (move == MOVE_LEFT) {
        --mm;
        m_aggro++;
    }
    else {
        m_aggro = (m_aggro > 0) ? m_aggro - 1 : 0;
    }

    printTrain();
}

void actionPhase() { //행동 페이즈
    printf("<행동> 페이즈:\n");

    // 시민 행동
    printf("시민 행동: 시민은 아무것도 하지 않습니다.\n");

    // 좀비 행동
    printf("좀비 행동: 좀비는 아무도 공격하지 않았습니다.\n");

    // 마동석 행동
    printf("마동석 행동 (0: 휴식, 1: 도발, 2: 붙들기)>>\n");
    int action;
    scanf_s("%d", &action);
    if (action == ACTION_REST) {
        printf("마동석이 휴식을 취합니다...\n");
    }
    else if (action == ACTION_PROVOKE) {
        printf("마동석이 도발합니다...\n");
    }
    else if (action == ACTION_PULL) {
        printf("마동석이 좀비를 붙듭니다...\n");
        m_pull_success = 1;
    }
    else {
        m_pull_success = 0;
    }

    printf("\n");
}

int main(void) {
    intro();
    srand(1);
    mc = length - 7;
    mz = length - 4;
    mm = length - 3;
    turn = 0;
    num1 = 0;
    num2 = 0;
    c_aggro = 0;
    m_aggro = 0;
    m_pull_success = 0;

    while (1) {
        movePhase();
        actionPhase();
        turn++;
    }
    return 0;
}