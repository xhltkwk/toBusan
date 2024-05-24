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

int length, prob,stamina;
int mc, mz, mm,turn;
int num1, num2;

void intro() {
	printf("������ �����մϴ�.\n");
	printf("\n");
	printf("���񿡰Լ� Ż���ϼ���!\n");
	printf("\n");
	do{
		printf("train Length(15~50)>>\n");
		scanf_s("%d", &length);
	} while (length < LEN_MIN || length > LEN_MAX);

	do {
		printf("madongseok stamina(0~5)>>\n");
		scanf_s("%d", &stamina);
	} while (stamina < STM_MIN || stamina >STM_MAX);

	do {
		printf("percentile probability 'p'(10~90)>>\n");
		scanf_s("%d", &prob);

	} while (prob < PROB_MIN || prob > PROB_MAX);

	printf("\n");
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
	printf("\n");
}
	
void move_positions() {
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

		
void outro() {
	if (mc == 0) {
		printf("SUCCESS!\nŻ�� ����!");
		exit(0);
	}
	if (mc == mz - 1) {
		printf("GAME OVER\n�ù��� ���񿡰� �������ϴ�.!");
		exit(0);
	}
	printf("Citizen : %d -> %d (aggro: 1)\n", mc + 1, mc);
	if (turn % 2 == 1 && num2) {
		printf("Zombie : %d -> %d\n", mz + 1, mz);
	}
	else {
		printf("Zombie : stay %d\n", mz);
	}
	printf("madongseok: stay %d (aggro: 1, stamina: %d)\n", mm, stamina);
	printf("\n");
}

void movePhase() {
	printf("<�̵�> ������:\n");

	// �ù� �̵�
	printf("�ù� �̵� (���� ��ġ: %d, 1: ����, 0: �̵� �� ��)>>\n", mc);
	int move;
	scanf_s("%d", &move);
	if (move == MOVE_LEFT) {
		--mc;
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
