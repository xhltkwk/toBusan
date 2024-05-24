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
int m_pull_success;

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

void position() { //��ġ �̵� rand��
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

void outro() { //�ƿ�Ʈ��
    if (mc == 0) {
        printf("SUCCESS!\nŻ�� ����!");
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
    printf("<�̵�> ������:\n");

    printTrain(); // ������ ���� ���

    // �ù� �̵�
    int r = rand() % 100;
    if (r < (100 - prob)) {
        if (c_aggro < AGGRO_MAX) {
            --mc;
            c_aggro++;
        }
        printf("�ù� �̵�: �������� �̵� (���� ��ġ: %d)\n", mc);
    }
    else {
        if (c_aggro > AGGRO_MIN) {
            c_aggro--;
        }
        printf("�ù� �̵�: ���ڸ� ��� (���� ��ġ: %d)\n", mc);
    }

    // ���� �̵�
    if (turn % 2 == 0 && !m_pull_success) {
        if (c_aggro >= m_aggro) {
            --mz;
            printf("���� �̵�: �ù��� ���� �̵� (���� ��ġ: %d)\n", mz);
        }
        else {
            --mz;
            printf("���� �̵�: �������� ���� �̵� (���� ��ġ: %d)\n", mz);
        }
    }
    else {
        printf("���� �̵�: �̵� �Ұ��� (���� ��ġ: %d)\n", mz);
    }

    // ������ �̵�
    printf("������ �̵� (���� ��ġ: %d, 1: ����, 0: �̵� �� ��)>>\n", mm);
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

void actionPhase() { //�ൿ ������
    printf("<�ൿ> ������:\n");

    // �ù� �ൿ
    printf("�ù� �ൿ: �ù��� �ƹ��͵� ���� �ʽ��ϴ�.\n");

    // ���� �ൿ
    printf("���� �ൿ: ����� �ƹ��� �������� �ʾҽ��ϴ�.\n");

    // ������ �ൿ
    printf("������ �ൿ (0: �޽�, 1: ����, 2: �ٵ��)>>\n");
    int action;
    scanf_s("%d", &action);
    if (action == ACTION_REST) {
        printf("�������� �޽��� ���մϴ�...\n");
    }
    else if (action == ACTION_PROVOKE) {
        printf("�������� �����մϴ�...\n");
    }
    else if (action == ACTION_PULL) {
        printf("�������� ���� �ٵ�ϴ�...\n");
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