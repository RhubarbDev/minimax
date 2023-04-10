use std::io;
use crate::board::Board;

static HUMAN: char = 'X';
static COMPUTER: char = '0';

fn main() {
    let mut board : Vec<Vec<char>> = vec![vec!['-'; 3]; 3];







}

pub fn update_board(mut board: Vec<Vec<char>>, player: bool, xPos: usize, yPos: usize) {
    let character: char = if player { HUMAN } else { COMPUTER };
    if valid_position(xPos, yPos) {
        board[xPos][yPos] = character;
    }
}

pub fn valid_position(xPos: usize, yPos: usize) -> bool {
    if xPos < 0 || xPos > 2 || yPos < 0 || yPos > 2 {
        return false;
    }
    if board[xPos][yPos] == '-' {
        return true;
    }
    return false;
}

pub fn print_board(board: Vec<Vec<char>>) {
    for i in 0..2 {
        for j in 0..2 {
            print!(" {}", board[i][j]);
        }
    }
}

pub fn check_win(board: Vec<Vec<char>>, player: bool) -> bool {
    let character: char = if player { HUMAN } else { COMPUTER };
    let mut won: bool = false;
    for n in 0..2 {
        if board[n][0] == character && board[n][1] == character && board[n][2] == character {
            won = true;
        }

        if board[0][n] == character && board[1][n] == character && board[2][n] == character {
            won = true;
        }
    }

    if board[0][0] == character && board[1][1] == character && board[2][2] == character {
        won = true;
    }

    if board[0][2] == character && board[1][1] == character && board[2][0] == character {
        won = true;
    }

    return won;
}

pub fn get_move() -> (usize, usize) {
    let mut xPos: usize = 3;
    let mut yPos : usize= 3;
    while !valid_position(xPos, yPos) {
        println!("Enter X position: ");
        let mut inputX: String = String::new();
        io::stdin().read_line(&mut inputX);
        println!("Enter Y position: ");
        let mut inputY: String = String::new();
        io::stdin().read_line(&mut inputY);
        xPos = 0;
        yPos = 0;
    }
    return (xPos, yPos)
}
