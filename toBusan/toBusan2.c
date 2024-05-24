#include <stdio.h>
#include<stdlib.h>
#include<windows.h>
#define LEN_MIN 15// 열차 길이
#define LEN_MAX 50
#define PROB_MIN 10// 움직일 확률
#define PROB_MAX 90

int main(void) {
	int length, prob;
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
	if (length < LEN_MIN || length>LEN_MAX) {
		printf("길이를 잘못 입력하셨습니다.\n게임을 다시 시작해주세요.\n");
		exit(1);
		//프로그램 종료
	}
	if (prob < PROB_MIN || prob>PROB_MAX) {
		printf("확률을 잘못 입력하셨습니다.\n게임을 다시 시작해주세요.\n");
		exit(1);
	}
	for (int j = 0; j < 2; j++) {

		if (j == 1) {
			printf("#"); //2줄 시작점 #
			int c = length - 7, z = length - 4, m = length - 3;
			for (int n = 0; n < length - 2; n++) {
				if (j == 1 && n == c) {
					printf("C"); // 시민 출력
				}
				else if (j == 1 && n == z) {
					printf("Z"); //좀비 출력
				}
				else if (j == 1 && n == m) {
					printf("M"); // 마동석 출력
				}
				else {
					printf(" "); // 빈칸 출력
				}
			}
			printf("#\n"); // 2줄 마지막 #
		}

		for (int i = 0; i < length; i++) {
			printf("#"); //3줄 출력
		}
		printf("\n");
	}
	printf("\n");
	Sleep(1000);
	srand(1);
	int mc = length - 7, mz = length - 4, mm = length - 3, turn = 0;
	int num1 = 0, num2 = 0;
	while (1) { //시민이동
		int r = rand() % 100;
		if (r <= 100 - prob) {
			--mc;
			++num1;
		}
		int r1 = rand() % 100; //좀비이동
		++turn;
		if (turn % 2 == 1) {
			if (r1 <= prob) {
				--mz;
				++num2;
			}
		}
		//만약 turn이 홀수가 되면 좀비가 움직인다
		for (int j = 0; j < 2; j++) {
			if (j == 1) {
				printf("#"); //2줄 시작점 #
				for (int n = 0; n < length - 2; n++) {
					if (j == 1 && n == mc) {
						printf("C"); // 시민 출력
					}
					else if (j == 1 && n == mz) {
						printf("Z"); //좀비 출력
					}
					else if (j == 1 && n == mm) {
						printf("M"); // 마동석 출력
					}
					else {
						printf(" "); // 빈칸 출력
					}
				}
				printf("#\n"); // 2줄 마지막 #
			}
			for (int i = 0; i < length; i++) {
				printf("#"); //3줄 출력
			}
			printf("\n");
		}
		if (mc == 0) {
			printf("SUCCESS!\n");
			printf("탈출 성공!");
			break;
		}
		if (mc == mz - 1) {
			printf("GAME OVER\n");
			printf("시민이 좀비에게 먹혔습니다.!");
			break;
		}
		if (r <= 100 - prob) {
			printf("Citizen : %d -> %d\n", mc + 1, mc);
		}
		else {
			printf("Citizen : stay %d\n", mc);
		}
		if (turn % 2 == 1)//좀비가 움직일때
			if (num2) {
				printf("Zombie : %d -> %d\n", mz + 1, mz);
			}
			else {
				printf("Zombie : stay %d\n", mz);
			}
		else {
			printf("Zombie : stay %d (cannot move)\n", mz);
		}
		printf("\n");
		Sleep(4000);
	}
	return 0;
}
