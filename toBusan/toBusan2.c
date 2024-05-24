#include <stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

// 파라미터
#define LEN_MIN 15 // 열차 길이
#define LEN_MAX 50
#define PROB_MIN 10 // 움직일 확률
#define PROB_MAX 90
#define STM_MIN 0 // 마동석 체력
#define STM_MAX 5
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

int length, prob;
int mc, mz, mm,turn;
int num1, num2;

void intro() {
	printf("게임을 시작합니다.\n");
	Sleep(1000);
	printf("\n");
	printf("좀비에게서 탈출하세요!\n");
	Sleep(1000);
	printf("\n");
	printf("train Length(15~50)>>\n");
	scanf_s("%d", &length);
	printf("percentile probability 'p'(10~90)>>\n");
	scanf_s("%d", &prob);
	Sleep(1000);
	printf("\n");
	if (length < LEN_MIN || length > LEN_MAX || prob < PROB_MIN || prob > PROB_MAX) {
		printf("입력값이 잘못되었습니다.\n게임을 다시 시작해주세요.\n");
		exit(1);
	}
}

void print_train() {
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
}
	
void move_positions() {
	int r = rand() % 100;
	if (r <= 100 - prob) { --mc; ++num1; }
	int r1 = rand() % 100;
	if (turn % 2 == 1 && r1 <= prob) { --mz; ++num2; }
}
		
void print_status() {
	if (mc == 0) { printf("SUCCESS!\n탈출 성공!"); exit(0); }
	if (mc == mz - 1) { printf("GAME OVER\n시민이 좀비에게 먹혔습니다.!"); exit(0); }
	printf("Citizen : %d -> %d\n", mc + 1, mc);
	if (turn % 2 == 1 && num2) printf("Zombie : %d -> %d\n", mz + 1, mz);
	else printf("Zombie : stay %d\n", mz);
}

int main(void) {
	srand(1);
	intro();
	mc = length - 7; mz = length - 4; mm = length - 3; turn = 0; num1 = 0; num2 = 0;
	while (1) {
		move_positions();
		print_train();
		print_status();
		turn++;
		Sleep(4000);
	}
	return 0;
}
