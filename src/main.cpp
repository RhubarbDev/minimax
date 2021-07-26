#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

char helper_addmove(int pos, char maxmin);
void helper_printboard(char b[9]);
int helper_staticeval(char b[9]);
bool helper_draw(char b[9]);

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
	if (iswin(b[0], b[1], b[2], 'X') or iswin(b[3], b[4], b[5], 'X') or iswin(b[6], b[7], b[8], 'X')){
		return 1; // ai win (max)
	}
	else if (iswin(b[0], b[1], b[2], '0') or iswin(b[3], b[4], b[5], '0') or iswin(b[6], b[7], b[8], '0')){
		return -1; // player win (min)
	}
	else if (iswin(b[0], b[3], b[6], 'X') or iswin(b[1], b[4], b[7], 'X') or iswin(b[2], b[5], b[8], 'X')){
		return 1;
	}
	else if (iswin(b[0], b[3], b[6], '0') or iswin(b[1], b[4], b[7], '0') or iswin(b[2], b[5], b[8], '0')){
		return -1;
	}
	else if (iswin(b[0], b[4], b[8], 'X') or iswin(b[2], b[4], b[6], 'X')){
		return 1;
	}
	else if (iswin(b[0], b[4], b[8], '0') or iswin(b[2], b[4], b[6], '0')){
		return -1;
	}
	else{
		return 0; // draw / no win
	}
	
}


bool helper_draw(char b[9]){
	for (int i = 0; i < 9; i++){
		if (b[i] == '-'){
			return false;		
		}
	}
	return true;
}

int minimax(int depth, bool maxplr, char b[9]){
	if (depth <= 0 or helper_staticeval(b) != 0 or helper_draw(b)) {
		cout << helper_staticeval(b) << '\n';
		return helper_staticeval(b);
	}

	if (maxplr) {
		int maxeval = -10;
		for (int i = 0; i < 9; i++){
			if (b[i] == '-'){
				char tempb[9];
				strncpy(tempb, b, 9);
				tempb[i] = 'X';
				int eval = minimax((depth - 1), false, tempb);
				if (maxeval < eval){
					maxeval = eval;
				}
			}
		}
		return maxeval;
	}
	else {
		int eval;
		int mineval = 10;
		for (int i = 0; i < 9; i++){
			if (b[i] == '-'){
				char tempb[9];
				strncpy(tempb, b, 9);
				tempb[i] = '0';
				eval = minimax((depth - 1), true, tempb);
				if (mineval > eval){
					mineval = eval;
				}
			}
		}
		return mineval;
	}

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
	aiadd();
}

void aiadd(){
	char tempboard[9];
	bool movemade = false;
	vector<pair<int, int>> vals;
	for (int i = 0; i < 9; i++){		
		strncpy(tempboard, board, 9);
		if (board[i] == '-'){
			tempboard[i] = '0';
			int val = minimax(6, true, tempboard);
			vals.push_back(make_pair(i, val));
		}
	}

	for (pair <int, int> p : vals){
		//cout << p.second << '\n';
	}

	for (pair <int, int> p : vals){
		if (p.second == -1 && !movemade){
			helper_addmove(p.first, maxplayer);
			movemade = true;
			break;
		}
	}

	for (pair <int, int> p : vals){
		if (p.second == 0 && !movemade){
			helper_addmove(p.first, maxplayer);
			movemade = true;
			break;
		}
	}
	playeradd();
}
