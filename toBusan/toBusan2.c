// 1-1: 필요한 헤더 파일과 상수 정의
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

// 1-2: 전역 변수 선언
int length, prob, stamina;
int mc, mz, mm, turn;
int num1, num2;
int c_aggro = 1, m_aggro = 1;
int m_pull;

// 1-3: 게임 시작을 위한 초기 설정 함수
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

// 1-4: 열차 상태를 출력하는 함수
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

// 1-5: 게임 종료 시 결과를 출력하는 함수
void outro() { //아웃트로
	if (mc == 0) {
		printf("YOU WIN!");
		exit(1);
	}
	if (mc == mz - 1) {
		printf("GAME OVER! citizen dead...");
		exit(1);
	}
	printf("Citizen : %d -> %d (aggro: %d)\n", mc + 1, mc, c_aggro);
	if (turn % 2 == 1 && num2) {
		printf("Zombie : %d -> %d\n", mz + 1, mz);
	}
	if (stamina == STM_MIN) {
		printf("GAME OVER! madongseok dead...");
		exit(1);
	}
	else {
		printf("Zombie : stay %d\n", mz);
	}
	printf("madongseok: stay %d (aggro: %d, stamina: %d)\n", mm, m_aggro, stamina);
	printf("\n");
}

// 1-6: 시민의 이동 계산 함수
void Move_Citizen_Phase() { //이동 페이즈 계산 시민
	int r = rand() % 100;
	if (r < (100 - prob)) {
		--mc;
		if (c_aggro < AGGRO_MAX) {
			++c_aggro;
		}
	}
}

// 1-7: 좀비의 이동 계산 함수
void Move_Zombie_Phase() { //이동 좀비 계산
	if (turn % 2 == 1 && !m_pull) {
		if (mm == mz + 1) { //인접 O
			if (m_aggro >= c_aggro) {
				mm = mm;
			}
			else {//m_aggro < c_aggro
				--mz;
			}
		}
		else {//인접 X
			if (m_aggro >= c_aggro) {
				++mz;
			}
			else {//m_aggro < c_aggro
				--mz;
			}
		}
	}
}

int move; //마동석 이동 변수

// 1-8: 마동석의 이동 계산 함수
void Move_Madongseok_Phase() { //이동 페이즈 계산 마동석

	if (move == MOVE_LEFT) {
		--mm;
		if (m_aggro == AGGRO_MAX) { // < 에서 == 로 수정
			m_aggro = m_aggro;
		}
		else {
			++m_aggro;
		}
	}

	else {
		if (m_aggro == AGGRO_MIN) {
			m_aggro = m_aggro;
		}
		else {
			--m_aggro;
		}
	}
}

// 1-9: 시민의 이동 결과 출력 함수
void move_citizen_phase() { //이동 페이즈 출력 시민

	if (c_aggro < AGGRO_MAX) {
		printf("citizen: %d -> %d (aggro : %d -> %d)\n", mc + 1, mc, c_aggro - 1, c_aggro);
	}
	else {
		printf("citizen : %d -> %d (aggro : %d)\n", mc + 1, mc, c_aggro);
	}
}

// 1-10: 좀비의 이동 결과 출력 함수
void move_zombie_phase() { //이동 페이즈 출력 좀비
	// 좀비 이동
	if (turn % 2 == 1 && !m_pull) {  //무조건 움직이는 턴 , 못움직이는건 마동석이랑 인접해있는 상태에서 마동석쪽으로 움직이려 할때만
		if (mm == mz - 1) { //인접 O
			if (m_aggro < c_aggro) { //마동석과 인접했는데 마동석 어그로가 시민보다 크거가 같으므로 좀비 움직임X 
				printf("zombie : %d -> %d\n", mz + 1, mz);
			}
			else { //시민 어그로가 더 크므로  ( m_aggro >= c_aggro )
				printf("zombie : stay %d\n", mz);
			}
		}
		else { //인접 x ( mm != mz - 1 )
			if (m_aggro >= c_aggro)
			{
				printf("zombie : %d -> %d\n", mz - 1, mz);
			}
			else
			{
				printf("zombie : %d -> %d\n", mz + 1, mz);
			}
		}
	}
	else {
		printf("zombie : stay : %d\n", mz);
	}
}

// 1-11: 마동석의 이동 결과 출력 함수
void move_madongseok_phase() { //이동 페이즈 출력 마동석

	if (move == MOVE_LEFT) {
		if (m_aggro == AGGRO_MAX) { // < 에서 == 로 수정
			printf("madongseok move %d -> %d (aggro : %d, stamina : %d)\n", mm + 1, mm, m_aggro, stamina);
		}
		else if (m_aggro == AGGRO_MIN) {
			printf("madongseok move %d -> %d (aggro : %d, stamina : %d)\n", mm + 1, mm, m_aggro, stamina);
		}
		else
		{
			printf("madongseok move %d -> %d (aggro : %d -> %d, stamina : %d)\n", mm + 1, mm, m_aggro - 1, m_aggro, stamina);
		}
	}
	else if (move == MOVE_STAY)
	{
		//위에선 어그로가 5를 넘어가는 일이 생겨서 AGGRO_MAX를 신경썼지만
		/*
		여기에선 마동석이 가만히 있을때 이기 때문에 어그로가
		0 밑으로 출력되지 않게 프린트 해야함
		*/
		printf("madongseok move %d -> %d (aggro : %d, stamina : %d)\n", mm, mm, m_aggro, stamina);

	}
}

// 1-12: 마동석의 이동 입력 함수
void movePhase() {// 마동석 이동
	int i, j = 0;
	do {
		if (mm == mz + 1) {
			printf("madongseok move(0: stay)\n");
			i = 1;
		}
		else {
			printf("madongseok move(0:stay, 1:left)>>\n");
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

// 1-13: 시민의 행동 페이즈 함수
void c_action_phase() { //행동 페이즈 시민 
	if (mc == 0) {
		outro();
	}
}

// 1-14: 좀비의 행동 페이즈 함수
void z_action_phase() { // 좀비 행동 페이즈
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
		printf("citizen does nothing.\n");
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
		if (stamina == STM_MIN) {
			printf("GAME OVER! madongseok dead...");
			exit(0);
		}
	}
}

// 1-15: 마동석의 행동 페이즈 함수
void m_action_phase() { // 마동석 행동 페이즈
	int action;
	if (mm == mz + 1) { //인접했을때
		do {
			printf("madongseok action (0. rest, 1. provoke, 2. pull)>>\n");
			printf("\n");
			scanf_s("%d", &action);
		} while (action != ACTION_REST && action != ACTION_PROVOKE && action != ACTION_PULL);

		if (action == ACTION_REST) { //휴식
			if (m_aggro == AGGRO_MIN) { //마동석 어그로=0일떄
				m_aggro = m_aggro;
			}
			else {
				--m_aggro;

			}if (stamina < STM_MAX) {
				++stamina;
			}
			printf("madongseok rests...\n");
			printf("madongseok: %d (aggro: %d,stamina: %d -> %d)\n", mm, m_aggro, stamina - 1, stamina);
		}
		else if (action == ACTION_PROVOKE) { //도발
			int p_aggro = m_aggro;
			m_aggro = AGGRO_MAX;
			printf("madongseok proveoked zombie...\n");
			printf("madongsoek: %d (aggro: %d -> %d, stamina: %d)\n", mm, p_aggro, m_aggro, stamina);
		}
		else { // action == ACTION_PULL
			m_aggro += 2;
			--stamina;
			int r = rand() % 100;
			if (r < (100 - prob)) {
				m_pull = 1;
				printf("madongseok pulled zombie... Next turn, it can't move\n");
				printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", mm, m_aggro - 2, m_aggro - 1, stamina + 1, stamina);
			}
			else {
				m_pull = 0;
				printf("madongseok failed to pull zombie\n");
				printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", mm, m_aggro - 2, m_aggro - 1, stamina + 1, stamina);
			}
			if (stamina <= STM_MIN) {
				printf("GAME OVER! madongseok dead...");
				exit(0);
			}
		}
	}
	else { //인접하지 않았을때
		do {
			printf("madongseok action (0. rest, 1. provoke)>>\n");
			printf("\n");
			scanf_s("%d", &action);
		} while (action != ACTION_REST && action != ACTION_PROVOKE);

		if (action == ACTION_REST) {
			if (m_aggro == AGGRO_MIN) { //마동석 어그로=0일떄
				m_aggro = m_aggro;
			}
			else {
				--m_aggro;

			}
			if (stamina < STM_MAX) {
				++stamina;
				printf("madongseok rests...\n");
				printf("madongseok: %d (aggro: %d -> %d,stamina: %d -> %d)\n", mm, m_aggro + 1, m_aggro, stamina - 1, stamina);
			}
		}
		else { // action == ACTION_PROVOKE
			int p_aggro = m_aggro;
			m_aggro = AGGRO_MAX;
			printf("madongseok proveoked zombie...\n");
			printf("madongsoek: %d (aggro: %d -> %d, stamina: %d)\n", mm, p_aggro, m_aggro, stamina);
		}
	}
}

// 1-16: 메인 함수
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
	printTrain(); //열차 초기 상태 출력

	while (1) {
		++turn;
		printf("\n%dturn\n\n", turn);
		Move_Citizen_Phase(); //시민 계산
		Move_Zombie_Phase(); //좀비 계산
		printTrain(); // 열차 출력
		move_citizen_phase(); //시민 출력
		move_zombie_phase(); //좀비 출력
		movePhase(); // 마동석 입력
		Move_Madongseok_Phase(); // 마동석 계산
		printTrain(); // 열차출력
		move_madongseok_phase(); //마동석 출력
		c_action_phase(); // 시민 행동
		z_action_phase(); // 좀비 행동
		m_action_phase(); // 마동석 행동
	}
	return 0;
}