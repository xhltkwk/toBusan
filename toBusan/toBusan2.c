#include <stdio.h>
#include<stdlib.h>
#include<windows.h>
#define LEN_MIN 15// ���� ����
#define LEN_MAX 50
#define PROB_MIN 10// ������ Ȯ��
#define PROB_MAX 90

int main(void) {
	int length, prob;
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
	if (length < LEN_MIN || length>LEN_MAX) {
		printf("���̸� �߸� �Է��ϼ̽��ϴ�.\n������ �ٽ� �������ּ���.\n");
		exit(1);
		//���α׷� ����
	}
	if (prob < PROB_MIN || prob>PROB_MAX) {
		printf("Ȯ���� �߸� �Է��ϼ̽��ϴ�.\n������ �ٽ� �������ּ���.\n");
		exit(1);
	}
	for (int j = 0; j < 2; j++) {

		if (j == 1) {
			printf("#"); //2�� ������ #
			int c = length - 7, z = length - 4, m = length - 3;
			for (int n = 0; n < length - 2; n++) {
				if (j == 1 && n == c) {
					printf("C"); // �ù� ���
				}
				else if (j == 1 && n == z) {
					printf("Z"); //���� ���
				}
				else if (j == 1 && n == m) {
					printf("M"); // ������ ���
				}
				else {
					printf(" "); // ��ĭ ���
				}
			}
			printf("#\n"); // 2�� ������ #
		}

		for (int i = 0; i < length; i++) {
			printf("#"); //3�� ���
		}
		printf("\n");
	}
	printf("\n");
	Sleep(1000);
	srand(1);
	int mc = length - 7, mz = length - 4, mm = length - 3, turn = 0;
	int num1 = 0, num2 = 0;
	while (1) { //�ù��̵�
		int r = rand() % 100;
		if (r <= 100 - prob) {
			--mc;
			++num1;
		}
		int r1 = rand() % 100; //�����̵�
		++turn;
		if (turn % 2 == 1) {
			if (r1 <= prob) {
				--mz;
				++num2;
			}
		}
		//���� turn�� Ȧ���� �Ǹ� ���� �����δ�
		for (int j = 0; j < 2; j++) {
			if (j == 1) {
				printf("#"); //2�� ������ #
				for (int n = 0; n < length - 2; n++) {
					if (j == 1 && n == mc) {
						printf("C"); // �ù� ���
					}
					else if (j == 1 && n == mz) {
						printf("Z"); //���� ���
					}
					else if (j == 1 && n == mm) {
						printf("M"); // ������ ���
					}
					else {
						printf(" "); // ��ĭ ���
					}
				}
				printf("#\n"); // 2�� ������ #
			}
			for (int i = 0; i < length; i++) {
				printf("#"); //3�� ���
			}
			printf("\n");
		}
		if (mc == 0) {
			printf("SUCCESS!\n");
			printf("Ż�� ����!");
			break;
		}
		if (mc == mz - 1) {
			printf("GAME OVER\n");
			printf("�ù��� ���񿡰� �������ϴ�.!");
			break;
		}
		if (r <= 100 - prob) {
			printf("Citizen : %d -> %d\n", mc + 1, mc);
		}
		else {
			printf("Citizen : stay %d\n", mc);
		}
		if (turn % 2 == 1)//���� �����϶�
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
