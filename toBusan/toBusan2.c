#include <stdio.h>
#include<stdlib.h>
#include<windows.h>
#define LEN_MIN 15// 열차 길이
#define LEN_MAX 50
#define PROB_MIN 10// 움직일 확률
#define PROB_MAX 90

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
