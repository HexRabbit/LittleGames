#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void Printer(int L);
int char2int(char C);
char int2char(int C);
int* AI(int L);
int WIN(); 

static int BestPoint[10][2];
static char Board[19][19];
static int Score[19][19];
static int Joint[19][19];
static int AI_Joint[19][19];
static char Sign;
static char AI_Sign;
static int Count = 0;
static int first = -1;
static char input; //use for break (%c for \n)

int main() {
	printf("Welcome to Gomoku Gaming Center.\n");
	oncemore:{}
	first = -1;
	int L = 0;
	int Sign_temp;
	int mid;
	char X; // 
	char Y; // 與AI共用 
	int* AI_temp;
	for(int a=0; a<19; a++) {
		for(int b=0; b<19; b++) {
			Board[a][b] = '-';
		}
	}
	for(int a=0; a<19; a++) {
		for(int b=0; b<19; b++) {
			Score[a][b] = -10000;
		}
	}
	printf("How large is the gaming board? ");
	while(L<7 || L>19) {
		if(scanf("%d",&L) == 1) {
			if(L<7){
				printf("Well,you should draw it on your face.");
			}
			else if(L>19) {
				printf("Nice choise,now go buy one for me.");
			}
//			else {
//				printf("Wut? Go check if your brain is still there!");
//			}
		}
	}
	fflush(stdin);
	mid = L/2;
	printf("Which do you wanna use?\n");
	printf("Circle or Cross(O/X)? ");
	scanf("%c",&Sign);
	fflush(stdin);
	if(Sign == 'O') {
		AI_Sign = 'X';
	}
	if(Sign == 'X') {
		AI_Sign = 'O';
	}
	if((Sign != 'O') && (Sign != 'X')) {
		printf("You've chose the HIDDEN one!");
		AI_Sign = 'X';
		while(1) {
			if(scanf("%c",&input) == 1) {
				break;
			}
		}
		fflush(stdin);
	}
	printf("Who start first?\n");
	printf("Player = 1 , AI = 2 : ");
	while(first != 1 && first != 2 && first != 0) {
		if(scanf("%d",&first) == 1) {
			if(first != 1 && first != 2 && first != 0){
				printf("God damnit. Could you please read the instruction?");
			}
		}
	}
	fflush(stdin);
	if(first == 0) {
		printf("Enable AI self-testing!!!\n");
		goto AItest;
	}
	printf("Game start!Please type in the coodinate of the board. (ex. 7c)\n");
	if(first == 1) {
		goto Playerfirst;
	}
	Board[mid][mid] = AI_Sign;
	Playerfirst:{}
	Printer(L);
	Retry:{}
	while(1){
		if(scanf("%1c%1c[^\n]",&X,&Y) == 2) { //X縱Y橫
			fflush(stdin);
			if (Board[X][Y] == Sign || Board[X][Y] == AI_Sign)
			{
				printf("You can't do that!\n");
				goto Retry;
			}
			Board[(char2int(X))][(char2int(Y))] = Sign;
			if(WIN() == 1){
				Printer(L);
				printf("YOU WIN!\n");
				goto FINISH;
			}
			AI_temp = AI(L);
			Printer(L);
			printf("AI moves %c%c !\n",int2char(AI_temp[0]),int2char(AI_temp[1])); 
			if(WIN() == 2){
				printf("AI WIN!\n");
				goto FINISH;
			}
		}
	}
	FINISH:
		fflush(stdin);
		printf("Thank you for playing.\n");
		printf("Do you wanna play once more? (Y/N) ");
		while(1) {
			if(scanf("%c",&input) == 1) {
				if(input == 'Y' || input == 'y') {
					fflush(stdin);
					printf("\n");
					goto oncemore;
				}
				break;
			}
		}
	return 0;
	AItest:
		fflush(stdin);
		Board[mid][mid] = Sign;
		Printer(L);
		while (WIN() != 1 && WIN() != 2) {
			AI(L); //same
			Sign_temp = AI_Sign;
			AI_Sign = Sign;
			Sign = Sign_temp;
			while(1) {
				if(scanf("%c",&input) == 1) {
					break;
				}
			}
			fflush(stdin);
			Printer(L);
			if (WIN() != 1 && WIN() != 2) {
				AI(L); //exchanged
				Sign_temp = AI_Sign;
				AI_Sign = Sign;
				Sign = Sign_temp;
				while(1) {
					if(scanf("%c",&input) == 1) {
						break;
					}
				}
				fflush(stdin);
				Printer(L);
			}
		}
		printf("Testing is over.\n");
		printf("Return to the game?(Y/N) ");
		while(1) {
			if(scanf("%c",&input) == 1) {
				if(input == 'Y') {
					fflush(stdin);
					printf("\n");
					goto oncemore;
				}
				break;
			}
		}
	return 0;
}

void Printer(int L) {
	char Num[] = "0123456789abcdefghi";
	printf("* ");
	for(int i=0; i<L; i++) {
		printf("%c ",Num[i]);
	}
	printf("*\n");
	for(int a=0; a<L; a++) {
		printf("%c ",Num[a]);
			for(int b=0; b<L; b++) {
				printf("%c ",Board[a][b]);
			}
		printf("%c\n",Num[a]);
	}
	printf("* ");
	for(int i=0; i<L; i++) {
		printf("%c ",Num[i]);
	}
	printf("*\n");
}

int char2int(char C) {
	switch(C){
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'a': return 10;
		case 'b': return 11;
		case 'c': return 12;
		case 'd': return 13;
		case 'e': return 14;
		case 'f': return 15;
		case 'g': return 16;
		case 'h': return 17;
		case 'i': return 18;
	}
}
char int2char(int C) {
	switch(C){
		case 0: return '0';
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		case 10: return 'a';
		case 11: return 'b';
		case 12: return 'c';
		case 13: return 'd';
		case 14: return 'e';
		case 15: return 'f';
		case 16: return 'g';
		case 17: return 'h';
		case 18: return 'i';
	}
}
int* AI(int L) { //先手時預設下在棋盤正中間  //仍須設定地圖邊界 //是否該改採用行列掃描方式?
	int HighestScore = 0; 
	int r = 0;
	for(int a=0; a<10; a++) {
		for(int b=0; b<2; b++) {
			BestPoint[a][b] = 0;
		}
	}
	for(int a=0; a<L; a++) {
		for(int b=0; b<L; b++) {
			Score[a][b] = 0;
		}
	}
	for(int a=0; a<L; a++) {
		for(int b=0; b<L; b++) {
			Joint[a][b] = 0;
		}
	}
	for(int a=0; a<L; a++) {
		for(int b=0; b<L; b++) {
			AI_Joint[a][b] = 0;
		}
	}
//	if(second == 0) {
//		goto SECOND;
//	}
	for(int a=0; a<L; a++) { //掃描至最外圍2層時為何不會發生錯誤?
		for(int b=0; b<L; b++) {
			//Player
			if(Board[a][b] == Sign) { 
				for(int c=-1; c<2; c++) { 
					for(int d=-1; d<2; d++) {
						Score[a+c][b+d] += 1;
					} 
				}
				//單二 
				if(Board[a+1][b] == Sign) { 
					Score[a-1][b] += 35;
				}
				if(Board[a-1][b] == Sign) {
					Score[a+1][b] += 35;
				}
				if(Board[a][b+1] == Sign) {
					Score[a][b-1] += 35;
				}
				if(Board[a][b-1] == Sign) {
					Score[a][b+1] += 35;
				}
				if(Board[a+1][b+1] == Sign) {
					Score[a-1][b-1] += 35;
				}
				if(Board[a-1][b-1] == Sign) {
					Score[a+1][b+1] += 35;
				}
				if(Board[a-1][b+1] == Sign) {
					Score[a+1][b-1] += 35;
				}
				if(Board[a+1][b-1] == Sign) {
					Score[a-1][b+1] += 35;
				}
				// 雙單
				if(Board[a+2][b] == Sign) {
					Score[a+1][b] += 17;
					if(Board[a-1][b] == Sign) {
						Score[a+1][b] += 400;
						if (Board[a-2][b] == AI_Sign || Board[a+3][b] == AI_Sign){
							Score[a+1][b] += -365;
						}
					}
					if(Board[a+3][b] == Sign) {
						Score[a+1][b] += 400;
						if (Board[a+4][b] == AI_Sign || Board[a-1][b] == AI_Sign){
							Score[a+1][b] += -365;
						}
					}
					if(Board[a-1][b] == Sign && Board[a+3][b] == Sign) {
						Score[a+1][b] += 7000;
					}
				}
				if(Board[a][b+2] == Sign) {
					Score[a][b+1] += 17;
					if(Board[a][b-1] == Sign) {
						Score[a][b+1] += 400;
						if (Board[a][b-2] == AI_Sign || Board[a][b+3] == AI_Sign){
							Score[a][b+1] += -365;
						}
					}
					if(Board[a][b+3] == Sign) {
						Score[a][b+1] += 400;
						if (Board[a][b+4] == AI_Sign || Board[a][b-1] == AI_Sign){
							Score[a][b+1] += -365;
						}
					}
					if(Board[a][b-1] == Sign && Board[a][b-3] == Sign) {
						Score[a][b+1] += 7000;
					}
				}
				if(Board[a+2][b-2] == Sign) {
					Score[a+1][b-1] += 17;
					if(Board[a-1][b+1] == Sign) {
						Score[a+1][b-1] += 400;
						if (Board[a-2][b+2] == AI_Sign || Board[a+3][b-3] == AI_Sign){
							Score[a+1][b-1] += -365;
						}
					}
					if(Board[a+3][b-3] == Sign) {
						Score[a+1][b-1] += 400;
						if (Board[a+4][b-4] == AI_Sign || Board[a-1][b+1] == AI_Sign){
							Score[a+1][b-1] += -365;
						}
					}
					if(Board[a-1][b+1] == Sign && Board[a+3][b-3] == Sign) {
						Score[a+1][b-1] += 7000;
					}
				}
				if(Board[a+2][b+2] == Sign) {
					Score[a+1][b+1] += 17;
					if(Board[a-1][b-1] == Sign) {
						Score[a+1][b+1] += 400;
						if (Board[a-2][b-2] == AI_Sign || Board[a+3][b+3] == AI_Sign){
							Score[a+1][b+1] += -365;
						}
					}
					if(Board[a+3][b+3] == Sign) {
						Score[a+1][b+1] += 400;
						if (Board[a+4][b+4] == AI_Sign || Board[a-1][b-1] == AI_Sign){
							Score[a+1][b+1] += -365;
						}
					}
					if(Board[a-1][b-1] == Sign && Board[a+3][b+3] == Sign) {
						Score[a+1][b+1] += 7000;
					}
				}
				//單三 
				if((Board[a+1][b+1] == Sign) && (Board[a-1][b-1] == Sign)) { //重複計算,只多加上10 
					Score[a+2][b+2] += 700;
					Score[a-2][b-2] += 700;
				}
				if((Board[a-1][b+1] == Sign) && (Board[a+1][b-1] == Sign)) {
					Score[a+2][b-2] += 700;
					Score[a-2][b+2] += 700;
				}
				if((Board[a][b+1] == Sign) && (Board[a][b-1] == Sign)) {
					Score[a][b+2] += 700;
					Score[a][b-2] += 700;
				}
				if((Board[a-1][b] == Sign) && (Board[a+1][b] == Sign)) {
					Score[a+2][b] += 700;
					Score[a-2][b] += 700;
				}
				//單四
				if((Board[a+1][b+1] == Sign) && (Board[a+2][b+2] == Sign) && (Board[a+3][b+3] == Sign)) {
					Score[a-1][b-1] += 4000;
					Score[a+4][b+4] += 4000;
				}
				if((Board[a+1][b] == Sign) && (Board[a+2][b] == Sign) && (Board[a+3][b] == Sign)) {
					Score[a-1][b] += 4000;
					Score[a+4][b] += 4000;
				}
				if((Board[a-1][b+1] == Sign) && (Board[a-2][b+2] == Sign) && (Board[a-3][b+3] == Sign)) {
					Score[a+1][b-1] += 4000;
					Score[a-4][b+4] += 4000;
				}
				if((Board[a][b+1] == Sign) && (Board[a][b+2] == Sign) && (Board[a][b+3] == Sign)) {
					Score[a][b-1] += 4000;
					Score[a][b+4] += 4000;
				}
				//阻擋扣分
				if((Board[a+1][b+1] == AI_Sign) && (Board[a+2][b+2] == AI_Sign)) { //70 - 55 = 15
					Score[a+3][b+3] += -60;
				}
				if((Board[a+1][b] == AI_Sign) && (Board[a+2][b] == AI_Sign)) {
					Score[a+3][b] += -60;
				}
				if((Board[a-1][b+1] == AI_Sign) && (Board[a-2][b+2] == AI_Sign)) {
					Score[a-3][b+3] += -60;
				}
				if((Board[a][b+1] == AI_Sign) && (Board[a][b+2] == AI_Sign)) {
					Score[a][b+3] += -60;
				}
				if((Board[a-1][b-1] == AI_Sign) && (Board[a-2][b-2] == AI_Sign)) {
					Score[a-3][b-3] += -60;
				}
				if((Board[a-1][b] == AI_Sign) && (Board[a-2][b] == AI_Sign)) {
					Score[a-3][b] += -60;
				}
				if((Board[a+1][b-1] == AI_Sign) && (Board[a+2][b-2] == AI_Sign)) {
					Score[a+3][b-3] += -60;
				}
				if((Board[a][b-1] == AI_Sign) && (Board[a][b-2] == AI_Sign)) {
					Score[a][b-3] += -60;
				}
				if((Board[a+1][b+1] == AI_Sign) && (Board[a+2][b+2] == AI_Sign) && (Board[a+3][b+3] == AI_Sign)) { //1000 - 850 = 150
					Score[a+4][b+4] += -850;
				}
				if((Board[a+1][b] == AI_Sign) && (Board[a+2][b] == AI_Sign) && (Board[a+3][b] == AI_Sign)) {
					Score[a+4][b] += -850;
				}
				if((Board[a-1][b+1] == AI_Sign) && (Board[a-2][b+2] == AI_Sign) && (Board[a-3][b+3] == AI_Sign)) {
					Score[a-4][b+4] += -850;
				}
				if((Board[a][b+1] == AI_Sign) && (Board[a][b+2] == AI_Sign) && (Board[a][b+3] == AI_Sign)) {
					Score[a][b+4] += -850;
				}
				if((Board[a-1][b-1] == AI_Sign) && (Board[a-2][b-2] == AI_Sign) && (Board[a-3][b-3] == AI_Sign)) {
					Score[a-4][b-4] += -850;
				}
				if((Board[a-1][b] == AI_Sign) && (Board[a-2][b] == AI_Sign) && (Board[a-3][b] == AI_Sign)) {
					Score[a-4][b] += -850;
				}
				if((Board[a+1][b-1] == AI_Sign) && (Board[a+2][b-2] == AI_Sign) && (Board[a+3][b-3] == AI_Sign)) {
					Score[a+4][b-4] += -850;
				}
				if((Board[a][b-1] == AI_Sign) && (Board[a][b-2] == AI_Sign) && (Board[a][b-3] == AI_Sign)) {
					Score[a][b-4] += -850;
				}

			}
			
			//AI
			if(Board[a][b] == AI_Sign) { 
				for(int e=-1; e<2; e++) { 
					for(int f=-1; f<2; f++) {
						Score[a+e][b+f] += 2;
					}
				}
				//單二 
				if(Board[a+1][b] == AI_Sign) {
					Score[a-1][b] += 70;
					if(Board[a-2][b] == Sign) {
						Score[a-1][b] += -50;
					}
					if(Board[a-2][b] == AI_Sign) {
						Score[a-1][b] += 350;
					}
				}
				if(Board[a-1][b] == AI_Sign) {
					Score[a+1][b] += 70;
					if(Board[a+2][b] == Sign) {
						Score[a+1][b] += -50;
					}
					if(Board[a+2][b] == AI_Sign) {
						Score[a+1][b] += 350;
					}
				}
				if(Board[a][b+1] == AI_Sign) {
					Score[a][b-1] += 70;
					if(Board[a][b-2] == Sign) {
						Score[a][b-1] += -50;
					}
					if(Board[a][b-2] == AI_Sign) {
						Score[a][b-1] += 350;
					}
				}
				if(Board[a][b-1] == AI_Sign) {
					Score[a][b+1] += 70;
					if(Board[a][b+2] == Sign) {
						Score[a][b+1] += -50;
					}
					if(Board[a][b+2] == AI_Sign) {
						Score[a][b+1] += 350;
					}
				}
				if(Board[a+1][b+1] == AI_Sign) {
					Score[a-1][b-1] += 70;
					if(Board[a-2][b-2] == Sign) {
						Score[a-1][b-1] += -50;
					}
					if(Board[a-2][b-2] == AI_Sign) {
						Score[a-1][b-1] += 350;
					}
				}
				if(Board[a-1][b-1] == AI_Sign) {
					Score[a+1][b+1] += 70;
					if(Board[a+2][b+2] == Sign) {
						Score[a+1][b+1] += -50;
					}
					if(Board[a+2][b+2] == AI_Sign) {
						Score[a+1][b+1] += 350;
					}
				}
				if(Board[a-1][b+1] == AI_Sign) {
					Score[a+1][b-1] += 70;
					if(Board[a+2][b-2] == Sign) {
						Score[a+1][b-1] += -50;
					}
					if(Board[a+2][b-2] == AI_Sign) {
						Score[a+1][b-1] += 350;
					}
				}
				if(Board[a+1][b-1] == AI_Sign) {
					Score[a-1][b+1] += 70;
					if(Board[a-2][b+2] == Sign) {
						Score[a-1][b+1] += -50;
					}
					if(Board[a-2][b+2] == AI_Sign) {
						Score[a-1][b+1] += 350;
					}
				}
				//雙單 
				if(Board[a+2][b] == AI_Sign) {
					Score[a+1][b] += 300;
					if(Board[a-1][b] == Sign || Board[a+3][b] == Sign) {
						Score[a+1][b] += -290;
					}
				}
				if(Board[a][b+2] == AI_Sign) {
					Score[a][b+1] += 300;
					if(Board[a][b-1] == Sign || Board[a][b-3] == Sign) {
						Score[a][b+1] += -290;
					}
				}
				if(Board[a+2][b-2] == AI_Sign) {
					Score[a+1][b-1] += 300;
					if(Board[a-1][b+1] == Sign || Board[a+3][b-3] == Sign) {
						Score[a+1][b-1] += -290;
					}
				}
				if(Board[a+2][b+2] == AI_Sign) {
					Score[a+1][b+1] += 300;
					if(Board[a-1][b-1] == Sign || Board[a+3][b+3] == Sign) {
						Score[a+1][b+1] += -290;
					}
				}
				//單三 
				if((Board[a+1][b+1] == AI_Sign) && (Board[a-1][b-1] == AI_Sign)) { 
					Score[a+2][b+2] += 1000;
					Score[a-2][b-2] += 1000;
				}
				if((Board[a-1][b+1] == AI_Sign) && (Board[a+1][b-1] == AI_Sign)) {
					Score[a+2][b-2] += 1000;
					Score[a-2][b+2] += 1000;
				}
				if((Board[a][b+1] == AI_Sign) && (Board[a][b-1] == AI_Sign)) {
					Score[a][b+2] += 1000;
					Score[a][b-2] += 1000;
				}
				if((Board[a-1][b] == AI_Sign) && (Board[a+1][b] == AI_Sign)) {
					Score[a+2][b] += 1000;
					Score[a-2][b] += 1000;
				}

				//單四
				if((Board[a+1][b+1] == AI_Sign) && (Board[a+2][b+2] == AI_Sign) && (Board[a+3][b+3] == AI_Sign)) {
					Score[a-1][b-1] += 5000;
					Score[a+4][b+4] += 5000;
				}
				if((Board[a+1][b] == AI_Sign) && (Board[a+2][b] == AI_Sign) && (Board[a+3][b] == AI_Sign)) {
					Score[a-1][b] += 5000;
					Score[a+4][b] += 5000;
				}
				if((Board[a-1][b+1] == AI_Sign) && (Board[a-2][b+2] == AI_Sign) && (Board[a-3][b+3] == AI_Sign)) {
					Score[a+1][b-1] += 5000;
					Score[a-4][b+4] += 5000;
				}
				if((Board[a][b+1] == AI_Sign) && (Board[a][b+2] == AI_Sign) && (Board[a][b+3] == AI_Sign)) {
					Score[a][b-1] += 5000;
					Score[a][b+4] += 5000;
				}
				//
				if((Board[a+1][b+1] == Sign) && (Board[a+2][b+2] == Sign)) { //35 - 15 = 20
					Score[a+3][b+3] += -15;
				}
				if((Board[a+1][b] == Sign) && (Board[a+2][b] == Sign)) {
					Score[a+3][b] += -15;
				}
				if((Board[a-1][b+1] == Sign) && (Board[a-2][b+2] == Sign)) {
					Score[a-3][b+3] += -15;
				}
				if((Board[a][b+1] == Sign) && (Board[a][b+2] == Sign)) {
					Score[a][b+3] += -15;
				}
				if((Board[a-1][b-1] == Sign) && (Board[a-2][b-2] == Sign)) {
					Score[a-3][b-3] += -15;
				}
				if((Board[a-1][b] == Sign) && (Board[a-2][b] == Sign)) {
					Score[a-3][b] += -15;
				}
				if((Board[a+1][b-1] == Sign) && (Board[a+2][b-2] == Sign)) {
					Score[a+3][b-3] += -15;
				}
				if((Board[a][b-1] == Sign) && (Board[a][b-2] == Sign)) {
					Score[a][b-3] += -15;
				}
				if((Board[a+1][b+1] == Sign) && (Board[a+2][b+2] == Sign) && (Board[a+3][b+3] == Sign)) { //700 - 730 + 70 = 40
					Score[a+4][b+4] += -730;
				}
				if((Board[a+1][b] == Sign) && (Board[a+2][b] == Sign) && (Board[a+3][b] == Sign)) {
					Score[a+4][b] += -730;
				}
				if((Board[a-1][b+1] == Sign) && (Board[a-2][b+2] == Sign) && (Board[a-3][b+3] == Sign)) {
					Score[a-4][b+4] += -730;
				}
				if((Board[a][b+1] == Sign) && (Board[a][b+2] == Sign) && (Board[a][b+3] == Sign)) {
					Score[a][b+4] += -730;
				}
				if((Board[a-1][b-1] == Sign) && (Board[a-2][b-2] == Sign) && (Board[a-3][b-3] == Sign)) {
					Score[a-4][b-4] += -730;
				}
				if((Board[a-1][b] == Sign) && (Board[a-2][b] == Sign) && (Board[a-3][b] == Sign)) {
					Score[a-4][b] += -730;
				}
				if((Board[a+1][b-1] == Sign) && (Board[a+2][b-2] == Sign) && (Board[a+3][b-3] == Sign)) {
					Score[a+4][b-4] += -730;
				}
				if((Board[a][b-1] == Sign) && (Board[a][b-2] == Sign) && (Board[a][b-3] == Sign)) {
					Score[a][b-4] += -730;
				}

			}
			// 交會點賦值
			if((Board[a][b-1] == AI_Sign) && (Board[a][b-2] == AI_Sign)) {
				if(Board[a][b-3] != Sign) {
					AI_Joint[a][b] += 1;
				}
			}
			if((Board[a][b+1] == AI_Sign) && (Board[a][b+2] == AI_Sign)) {
				if(Board[a][b+3] != Sign) {
					AI_Joint[a][b] += 1;
				}
			}
			if((Board[a+1][b] == AI_Sign) && (Board[a+2][b] == AI_Sign)) {
				if(Board[a+3][b] != Sign) {
					AI_Joint[a][b] += 1;
				}
			}
			if((Board[a-1][b] == AI_Sign) && (Board[a-2][b] == AI_Sign)) {
				if(Board[a-3][b] != Sign) {
					AI_Joint[a][b] += 1;
				}
			}
			if((Board[a-1][b-1] == AI_Sign) && (Board[a-2][b-2] == AI_Sign)) {
				if(Board[a-3][b-3] != Sign) {
					AI_Joint[a][b] += 1;
				}
			}
			if((Board[a+1][b+1] == AI_Sign) && (Board[a+2][b+2] == AI_Sign)) {
				if(Board[a+3][b+3] != Sign) {
					AI_Joint[a][b] += 1;
				}
			}
			if((Board[a+1][b-1] == AI_Sign) && (Board[a+2][b-2] == AI_Sign)) {
				if(Board[a+3][b-3] != Sign) {
					AI_Joint[a][b] += 1;
				}
			}
			if((Board[a-1][b+1] == AI_Sign) && (Board[a-2][b+2] == AI_Sign)) {
				if(Board[a-3][b+3] != Sign) {
					AI_Joint[a][b] += 1;
				}
			}	
			if((Board[a][b-1] == Sign) && (Board[a][b-2] == Sign)) {
				if(Board[a][b-3] != AI_Sign) {
					Joint[a][b] += -1;
				}
			}
			if((Board[a][b+1] == Sign) && (Board[a][b+2] == Sign)) {
				if(Board[a][b+3] != AI_Sign) {
					Joint[a][b] += -1;
				}
			}
			if((Board[a+1][b] == Sign) && (Board[a+2][b] == Sign)) {
				if(Board[a+3][b] != AI_Sign) {
					Joint[a][b] += -1;
				}
			}
			if((Board[a-1][b] == Sign) && (Board[a-2][b] == Sign)) {
				if(Board[a-3][b] != AI_Sign) {
					Joint[a][b] += -1;
				}
			}
			if((Board[a-1][b-1] == Sign) && (Board[a-2][b-2] == Sign)) {
				if(Board[a-3][b-3] != AI_Sign) {
					Joint[a][b] += -1;
				}
			}
			if((Board[a+1][b+1] == Sign) && (Board[a+2][b+2] == Sign)) {
				if(Board[a+3][b+3] != AI_Sign) {
					Joint[a][b] += -1;
				}
			}
			if((Board[a+1][b-1] == Sign) && (Board[a+2][b-2] == Sign)) {
				if(Board[a+3][b-3] != AI_Sign) {
					Joint[a][b] += -1;
				}
			}
			if((Board[a-1][b+1] == Sign) && (Board[a-2][b+2] == Sign)) {
				if(Board[a-3][b+3] != AI_Sign) {
					Joint[a][b] += -1;
				}
			}	
		}
	}
	//加權
	for(int a=0; a<L; a++) {
		for(int b=0; b<L; b++) {
			if(AI_Joint[a][b] >= 2) {
				Score[a][b] += AI_Joint[a][b]*180;
			}
			if(Joint[a][b] <= -2) {
				Score[a][b] += -Joint[a][b]*155;
			}
		}
	}
	/*
	//數值隨機化 
	for(int a=0; a<L; a++) {
		for(int b=0; b<L; b++) {
			if(Score[a][b] > 0) {
				Score[a][b] += rand() % 5;
			}
		}
	}
	*/
	for(int a=0; a<L; a++) {
		for(int b=0; b<L; b++) {
			if(Score[a][b] > 15) {
				goto A;
			}
			if((a == L-1) && (b == L-1)) {
				for(int c=0; c<L; c++) {
					for(int d=0; d<L; d++) {
						Score[c][d] = 100*Score[c][d];
					}
				}
			}
		}
	}
	A:{}
	
	//清除已落子位置
	for(int a=0; a<L; a++) {
		for(int b=0; b<L; b++) {
			if((Board[a][b] == Sign) || (Board[a][b] == AI_Sign)) {
				Score[a][b] = 0;
			}
		}
	}
	for(int a=0;a<L;a++) {
		Score[a][L-1] = 0;
		Score[a][0] = 0;
		Score[L-1][a] = 0;
		Score[0][a] = 0;
	}
	
	Count = 0;
	
	for(int a=0; a<L; a++) {
		for(int b=0; b<L; b++) {
			if(Score[a][b] >= HighestScore){
				if(((Score[a][b] - HighestScore) <= 10) && (Count < 10)) {
					Count++;
					HighestScore = Score[a][b]; 
					BestPoint[Count][0] = a;
					BestPoint[Count][1] = b;
				}
				if((Score[a][b] - HighestScore) > 10) {
					Count = 0;
					HighestScore = Score[a][b];
					BestPoint[0][0] = a;
					BestPoint[0][1] = b;
				}
			}
		}
	}
	srand(time(0));
	r = rand() % (Count + 1);
	Board[(BestPoint[r][0])][(BestPoint[r][1])] = AI_Sign;
	return BestPoint[r];
}
int WIN() {
	for(int a=0; a<19; a++) { 
		for(int b=0; b<19; b++) {
			if(Board[a][b] == Board[a+1][b+1] && Board[a+1][b+1] == Board[a+2][b+2] && Board[a+2][b+2] == Board[a+3][b+3] && Board[a+3][b+3] == Board[a+4][b+4]) {
				if(Board[a][b] == Sign) {
					return 1;
				}
				if(Board[a][b] == AI_Sign) {
					return 2;
				}
			}
			if(Board[a][b] == Board[a-1][b+1] && Board[a-1][b+1] == Board[a-2][b+2] && Board[a-2][b+2] == Board[a-3][b+3] && Board[a-3][b+3] == Board[a-4][b+4]) {
				if(Board[a][b] == Sign) {
					return 1;
				}
				if(Board[a][b] == AI_Sign) {
					return 2;
				}
			}
			if(Board[a][b] == Board[a][b+1] && Board[a][b+1] == Board[a][b+2] && Board[a][b+2] == Board[a][b+3] && Board[a][b+3] == Board[a][b+4]) {
				if(Board[a][b] == Sign) {
					return 1;
				}
				if(Board[a][b] == AI_Sign) {
					return 2;
				}
			}
			if(Board[a][b] == Board[a+1][b] && Board[a+1][b] == Board[a+2][b] && Board[a+2][b] == Board[a+3][b] && Board[a+3][b] == Board[a+4][b]) {
				if(Board[a][b] == Sign) {
					return 1;
				}
				if(Board[a][b] == AI_Sign) {
					return 2;
				}
			}
		}
	}
	return 0;
}
