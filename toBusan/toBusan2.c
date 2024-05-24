#include <stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

// �Ķ����
#define LEN_MIN 15 // ���� ����
#define LEN_MAX 50
#define PROB_MIN 10 // ������ Ȯ��
#define PROB_MAX 90
#define STM_MIN 0 // ������ ü��
#define STM_MAX 5
#define AGGRO_MIN 0 // ��׷� ����
#define AGGRO_MAX 5

// ������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY 0

// ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int length, prob;
int mc, mz, mm,turn;
int num1, num2;

void intro() {
	printf("������ �����մϴ�.\n");
	Sleep(1000);
	printf("\n");
	printf("���񿡰Լ� Ż���ϼ���!\n");
	Sleep(1000);
	printf("\n");
	printf("train Length(15~50)>>\n");
	scanf_s("%d", &length);
	printf("percentile probability 'p'(10~90)>>\n");
	scanf_s("%d", &prob);
	Sleep(1000);
	printf("\n");
	if (length < LEN_MIN || length > LEN_MAX || prob < PROB_MIN || prob > PROB_MAX) {
		printf("�Է°��� �߸��Ǿ����ϴ�.\n������ �ٽ� �������ּ���.\n");
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
	if (mc == 0) { printf("SUCCESS!\nŻ�� ����!"); exit(0); }
	if (mc == mz - 1) { printf("GAME OVER\n�ù��� ���񿡰� �������ϴ�.!"); exit(0); }
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
