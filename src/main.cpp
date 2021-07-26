#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

char helper_addmove(int pos, char maxmin);
void helper_printboard(char b[9]);
int helper_staticeval(char b[9]);
bool helper_movesleft(char b[9]);
void helper_moveswapper(bool player);

int minimax(int depth, bool maxplr, char b[9]);
void playeradd();
void aiadd();




char maxplayer = 'X';
char minplayer = 'O';

static char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};


int main(int argc, char *argv[])
{
	cout << "Starting Game: current board\n";
	helper_printboard(board);
	aiadd();
}

char helper_addmove(int pos, char maxmin){
	cout << "making move...\n";
	board[pos] = maxmin;
	helper_printboard(board);
}

void helper_printboard(char b[]){
	for (int i = 0; i < 9; i++){
		cout << b[i];
		if (i == 2 or i == 5 or i == 8){
			cout << '\n';
		}
	}
	cout << endl;
}

bool iswin(char a, char b, char c, char d){
	if (a == d && b == d && c == d){
		return true;
	}
	else{
		return false;
	}
}

int helper_staticeval(char b[9]){
	if (iswin(b[0], b[1], b[2], maxplayer) or iswin(b[3], b[4], b[5], maxplayer) or iswin(b[6], b[7], b[8], maxplayer)){
		return 10; // ai win (max)
	}
	else if (iswin(b[0], b[1], b[2], minplayer) or iswin(b[3], b[4], b[5], minplayer) or iswin(b[6], b[7], b[8], minplayer)){
		return -10; // player win (min)
	}
	else if (iswin(b[0], b[3], b[6], maxplayer) or iswin(b[1], b[4], b[7], maxplayer) or iswin(b[2], b[5], b[8], maxplayer)){
		return 10;
	}
	else if (iswin(b[0], b[3], b[6], minplayer) or iswin(b[1], b[4], b[7], minplayer) or iswin(b[2], b[5], b[8], minplayer)){
		return -10;
	}
	else if (iswin(b[0], b[4], b[8], maxplayer) or iswin(b[2], b[4], b[6], maxplayer)){
		return 10;
	}
	else if (iswin(b[0], b[4], b[8], minplayer) or iswin(b[2], b[4], b[6], minplayer)){
		return -10;
	}
	else{
		return 0; // draw / no win
	}
	
}


bool helper_movesleft(char b[9]){
	for (int i = 0; i < 9; i++){
		if (b[i] == '-'){
			return true;		
		}
	}
	return false;
}

int minimax(int depth, bool maxplr, char b[9]){
	int score = helper_staticeval(b);

	if (score == 10){
		return score - depth;
	}
	else if (score == -10){
		return score + depth;
	}
	else if (!helper_movesleft(b)){
		return 0;
	}

	if (maxplr){
		int maxeval = -1000;

		for (int i = 0; i < 9; i++){
			if (b[i] == '-'){
				b[i] = maxplayer;
				maxeval = max(maxeval, minimax(depth++, false, b));
				b[i] = '-';
			}
		}
		return maxeval;
	}
	else{
		int mineval = 1000;

		for (int i = 0; i < 9; i++){
			if (b[i] == '-'){
				b[i] = minplayer;
				mineval = min(mineval, minimax(depth++, true, b));
				b[i] = '-';
			}
		}
		return mineval;
	}

}

int bestmove(char b[9]){
	int bestval = -1000;
	int optimalmove;
	for (int i = 0; i < 9; i++){
		if (b[i] == '-'){
			b[i] = maxplayer;
			int movescore = minimax(0, true, b);
			b[i] = '-';
			if (movescore > bestval){
				bestval = movescore;
				optimalmove = i;
			}
		}
	}
	return optimalmove;
}


void playeradd(){
	int move;
	cout << "1 2 3\n4 5 6\n7 8 9\nEnter Value:";
	cin >> move; move--;
	if (board[move] == '-'){
		helper_addmove(move, minplayer);
	}
	else{
		cout << "That isn't a valid move! - trying again...\n";
		playeradd();
	}
	helper_moveswapper(false);
}

void aiadd(){
	int optimal = bestmove(board);
	helper_addmove(optimal, maxplayer);
	helper_moveswapper(true);
}

void helper_moveswapper(bool player){
	int score = helper_staticeval(board);
	if (score == 10){
		cout << "The AI has won!\n";
	}
	else if (score == -10){
		cout << "The player has won!\n";
	}
	else if (!helper_movesleft(board)){
		cout << "Draw!\n";
	}
	else{
		if (player){
			playeradd();
		}
		else{
			aiadd();
		}
	}
}


