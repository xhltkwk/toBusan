#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// �Ķ����
#define LEN_MIN 15 // ���� ����
#define LEN_MAX 50
#define STM_MIN 0 // ������ ü��
#define STM_MAX 5
#define PROB_MIN 10 // ������ Ȯ��
#define PROB_MAX 90
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

int length, prob, stamina;
int mc, mz, mm, turn;
int num1, num2;
int c_aggro, m_aggro;
int m_pull;

void intro() { //��Ʈ��
	printf("������ �����մϴ�.\n");
	printf("\n���񿡰Լ� Ż���ϼ���!\n");
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

void printTrain() { //������ ���
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

void outro() { //�ƿ�Ʈ��
	if (mc == 0) {
		printf("YOU WIN!");
		exit(0);
	}
	if (mc == mz - 1) {
		printf("GAME OVER\n�ù��� ���񿡰� �������ϴ�.!");
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

void movePhase() { //�̵� ������

	printTrain(); // ������ ���� ���

	// �ù� �̵�
	int r = rand() % 100;
	if (r < (100 - prob)) {
		--mc;
		if (c_aggro < AGGRO_MAX) {
			c_aggro++;
			printf("citizen: %d -> %d (aggro : %d -> %d)\n", mc + 1, mc, c_aggro - 1, c_aggro);
		}
		else if (c_aggro == AGGRO_MAX) {
			printf("citizen : %d -> %d (aggro ; %d)\n", mc + 1, mc, c_aggro);
		}
	}
	else {
		if (c_aggro > AGGRO_MIN) {
			c_aggro--;
			printf("citizen : %d -> %d (aggro : %d -> %d)\n", mc + 1, mc, c_aggro - 1, c_aggro);
		}
		else {
			printf("ctizen : %d -> %d (aggro : %d)\n", mc + 1, mc, c_aggro);
		}
	}

	// ���� �̵�
	if (turn % 2 == 0 && !m_pull) {
		if (mz - 1 != mc && mz - 1 != mm) {
			if (c_aggro >= m_aggro) {
				--mz;
				printf("zombie : %d -> %d\n", mz + 1, mz);
			}
			else {
				++mz;
				printf("zombie : %d -> %d\n", mz - 1, mz);
			}
		}
		else {
			printf("zombie : stay %d \n", mz);
		}
	}
	else {
		printf("zombie : stay %d\n", mz);
	}

	// ������ �̵�
	printf("\n");
	printf("madongseok move(0:stay)>>\n");
	int move;
	scanf_s("%d", &move);
	if (move == MOVE_LEFT) {
		if (m_aggro < AGGRO_MAX) {
			--mm;
			m_aggro++;
		}
	}
	else {
		if (m_aggro > AGGRO_MIN) {
			m_aggro--;
		}
	}
	printf("madongseok: stay %d(aggrp: %d -> %d, stamina : %d)\n", mm, m_aggro + 1, m_aggro, stamina);
	printf("\n");
	printf("citizen does nothing.\n");

	// ���� ���
	printTrain();
}

void actionPhase() { //�ൿ ������

	// �ù� �ൿ
	if (mc == 0) {
		outro();
	}
	else {
		printf("citizen does nothing.\n");
	}

	// ���� �ൿ
	int attack = ATK_NONE;
	if (mz - 1 == mc || mz + 1 == mc) {
		attack = ATK_CITIZEN;
	}
	if (mz - 1 == mm || mz + 1 == mm) {
		if (attack == ATK_CITIZEN) {
			if (m_aggro > c_aggro) {
				attack = ATK_DONGSEOK;
			}
		}
		else {
			attack = ATK_DONGSEOK;
		}
	}
	if (attack == ATK_NONE) {
		printf("zombie attacked nobody.\n");
	}
	else if (attack == ATK_CITIZEN) {
		printf("zombie attacked the citizen");
		printf("GAME OVER! citizen dead...");
		exit(0);
	}
	else if (attack == ATK_DONGSEOK) {
		printf("zombie attacked Madongseok!\n");
		stamina--;
		if (stamina == STM_MIN) {
			printf("GAME OVER! madongseok dead...");
			exit(0);
		}
	}


	// ������ �ൿ
	printf("madongseok action (0: rest, 1: provoke)>>\n");
	int action;
	scanf_s("%d", &action);
	if (action == ACTION_REST) {
		if (m_aggro > AGGRO_MIN) {
			m_aggro--;
		}
		if (stamina < STM_MAX) {
			stamina++;
		}
		printf("madongseok rests...\n");
		printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", mm, m_aggro + 1, m_aggro, stamina - 1, stamina);
	}
	else if (action == ACTION_PROVOKE) {
		m_aggro = AGGRO_MAX;
		printf("madongseok provoked zombie...\n");
		printf("madongseok: %d (aggro: %d -> %d, stamina: %d)\n", mm, AGGRO_MIN, m_aggro, stamina);
	}

	// ���� ���
	printTrain();
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
	m_pull = 0;

	while (1) {
		movePhase();
		actionPhase();
		turn++;
	}
	return 0;
}
