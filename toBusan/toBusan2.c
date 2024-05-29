//������ ��������

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
int c_aggro = 1, m_aggro = 1;
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
		printf("GAME OVER! citizen dead...");
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

void Move_Citizen_Phase() { //�̵� ������ ��� �ù�
	int r = rand() % 100;
	if (r < (100 - prob)) {
		--mc;
		if (c_aggro < AGGRO_MAX) {
			++c_aggro;
		}
	}
	else {
		if (c_aggro > AGGRO_MIN) {
			--c_aggro;
		}
	}
}

void Move_Zombie_Phase() { //�̵� ������ ��� ����
	if (turn % 2 == 1 && !m_pull) {
		if (mz - 1 != mc && mz - 1 != mm) {
			if (c_aggro > m_aggro) {
				--mz;
			}
			else {
				++mz;
			}
		}
		else {
			if (c_aggro > m_aggro) {
				--mz;
			}
			else {
				++mz;
			}
		}
	}
}

int move;
void Move_Madongseok_Phase() { //�̵� ������ ��� ������

	if (move == MOVE_LEFT) {
		--mm;
		if (m_aggro == AGGRO_MAX) { // < ���� == �� ����
			m_aggro = m_aggro;
		}
	}

	else {
		if (m_aggro > AGGRO_MIN) {
			--m_aggro;
		}
	}
}

void move_citizen_phase() { //�̵� ������ ��� �ù�

	if (c_aggro < AGGRO_MAX) {
		printf("citizen: %d -> %d (aggro : %d -> %d)\n", mc + 1, mc, c_aggro - 1, c_aggro);
	}
	else {
		printf("citizen : %d -> %d (aggro ; %d)\n", mc + 1, mc, c_aggro);
	}
}

void move_zombie_phase() { //�̵� ������ ��� ����
	// ���� �̵�
	if (turn % 2 == 1 && !m_pull) {
		if (mz - 1 != mc && mz - 1 != mm) {

			printf("zombie : %d -> %d\n", mz + 1, mz);
		}
		else {
			printf("zombie : stay %d \n", mz);
		}
	}
	else {
		printf("zombie : stay %d\n", mz);
	}
}

void move_madongseok_phase() { //�̵� ������ ��� ������

	if (move == MOVE_LEFT) {
		if (m_aggro == AGGRO_MAX) { // < ���� == �� ����
			printf("madongseok move %d -> %d (aggro : %d, stamina : %d)\n", mm + 1, mm, m_aggro, stamina);
		}
		else
		{
			printf("madongseok move %d -> %d (aggro : %d -> %d, stamina : %d)\n", mm - 1, mm, m_aggro - 1, m_aggro, stamina);
		}
	}
	else if (move == MOVE_STAY)
	{
		//������ ��׷ΰ� 5�� �Ѿ�� ���� ���ܼ� AGGRO_MAX�� �Ű������
		/*
		���⿡�� �������� ������ ������ �̱� ������ ��׷ΰ�
		0 ������ ��µ��� �ʰ� ����Ʈ �ؾ���
		*/
		printf("madongseok move %d -> %d (aggro : %d, stamina : %d)\n", mm, mm, m_aggro, stamina);

	}
}

void movePhase() {// ������ �̵�

	int i, j = 0;
	do {
		if (mm == mz + 1) {
			printf("madongseok move(0: stay)\n");
			i = 1;
		}
		else {
			printf("madongseok move(0:stay, 1:left)\n");
			i = 2;
		}
		printf("\n");
		scanf_s("%d", &move);
		if (move == MOVE_STAY && i == 1) {
			j = 1;
		}
		else if (move == MOVE_STAY || move == MOVE_LEFT) {
			if (i == 2) {
				j = 1;
			}
		}
	} while (j != 1);

	printf("\n");
}

void c_action_phase() { //�ൿ ������ �ù� 
	if (mc == 0) {
		outro();
	}
}

void z_action_phase() { // ���� �ൿ ������
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
		printf("citizen does nothing\n");
		printf("zombie attacked nobody.\n");
	}
	else if (attack == ATK_CITIZEN) {
		printf("citizen does nothing\n");
		printf("GAME OVER! citizen dead...");
		exit(0);
	}
	else if (attack == ATK_DONGSEOK) {
		--stamina;
		printf("citizen does nothing\n");
		printf("zombie attacked madongseok (aggro: %d, madongseok stamina: %d -> %d)\n", m_aggro, stamina + 1, stamina);
		if (stamina == STM_MIN) {
			printf("GAME OVER! madongseok dead...");
			exit(0);
		}
	}
	else if (mc == mz - 1 && mm - 1 == mz) {
		--stamina;
		printf("citizen does nothing\n");
		printf("zombie attacked madongseok (aggro: %d vs %d, madongseok stamina: %d -> %d)\n", c_aggro, m_aggro, stamina + 1, stamina);
	}
}

void m_action_phase() { // ������ �ൿ ������
	int action;
	do {
		printf("madongseok action (0. rest, 1. provoke, 2. pull)>>\n");
		printf("\n");
		scanf_s("%d", &action);
	} while (action != ACTION_REST && action != ACTION_PROVOKE && action != ACTION_PULL);

	if (action == ACTION_REST) {
		if (m_aggro == AGGRO_MIN) {
			printf("madongseok rests...\n");
			printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", mm, m_aggro + 1, m_aggro, stamina - 1, stamina);
		}
		else {
			m_aggro--;

		}
		if (stamina < STM_MAX) {
			stamina++;
		}
	}
	else if (action == ACTION_PROVOKE) {
		int p_aggro = m_aggro;
		m_aggro = AGGRO_MAX;
		printf("madongseok provoked zombie...\n");
		printf("madongseok: %d (aggro: %d -> %d, stamina: %d)\n", mm, p_aggro, m_aggro, stamina);
	}
	else if (action == ACTION_PULL) {
		m_aggro += 2;
		stamina--;
		int r = rand() % 100;
		if (r < (100 - prob)) {
			m_pull = 1;
			printf("madongseok pulled zombie... Next turn, it can't move\n");
			printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d", mm, m_aggro - 2,m_aggro-1, stamina + 1, stamina);
		}
		else {
			m_pull = 0;
			printf("madongseok failed to pull zombie\n");
			printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d", mm, m_aggro - 2,m_aggro-1, stamina + 1, stamina);
		}
	}
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
	c_aggro = 1;
	m_aggro = 1;
	m_pull = 0;
	printTrain();
	while (1) {
		++turn;
		//��� �ù� ���� ������ 
		Move_Citizen_Phase(); //�ù� ���
		Move_Zombie_Phase(); //���� ���
		printTrain(); // ���� ���
		move_citizen_phase(); //�ù� ���
		move_zombie_phase(); //���� ���
		movePhase(); // ������ �Է�
		Move_Madongseok_Phase(); // ������ ���
		printTrain(); // �������
		move_madongseok_phase(); //������ ���
		c_action_phase(); // �ù� �ൿ
		z_action_phase(); // ���� �ൿ
		m_action_phase(); // ������ �ൿ

	}
	return 0;
}