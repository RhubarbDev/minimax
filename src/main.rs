use std::io;
use std::io::Write;

static HUMAN: char = 'X';
static COMPUTER: char = '0';

fn main() {
    let mut board : Vec<Vec<char>> = vec![vec!['-'; 3]; 3];
    print_board(&board);
    let positions: (usize, usize) = get_move(&board);
    update_board(&mut board, true, positions.0, positions.1);
    print_board(&board);
    let positions: (usize, usize) = get_move(&board);
    update_board(&mut board, true, positions.0, positions.1);
    print_board(&board);
    let positions: (usize, usize) = get_move(&board);
    update_board(&mut board, true, positions.0, positions.1);
    print_board(&board);
    if check_win(&board, true) {
        println!("\n\x1b[32;4mYou Win!\x1b[0m");
    }
}

fn update_board(board: &mut Vec<Vec<char>>, player: bool, x_pos: usize, y_pos: usize) {
    let character: char = if player { HUMAN } else { COMPUTER };
    board[y_pos][x_pos] = character;
}

fn valid_position(board: &Vec<Vec<char>>, x_pos: usize, y_pos: usize) -> bool {
    if board[y_pos][x_pos] == '-' {
        return true;
    }
    return false;
}

fn in_range(value: usize) -> bool {
    if value > 2 {
        return false;
    }
    return true;
}

fn print_board(board: &Vec<Vec<char>>) {
    println!("  0 1 2");
    for i in 0..3 {
        print!("{}", i);
        for j in 0..3 {
            print!(" {}", board[i][j]);
        }
        println!();
    }
}

fn check_win(board: &Vec<Vec<char>>, player: bool) -> bool {
    let character: char = if player { HUMAN } else { COMPUTER };
    let mut won: bool = false;
    for n in 0..3 {
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

fn get_move(board: &Vec<Vec<char>>) -> (usize, usize) {
    let x_pos: usize = get_number("Enter X Position: ");
    let y_pos: usize = get_number("Enter Y Position: ");

    return if valid_position(board, x_pos, y_pos) {
        (x_pos, y_pos)
    } else {
        println!("This is not a valid position");
        get_move(board)
    }
}

fn get_number(prompt: &str) -> usize {
    let mut value = 3;
    while !in_range(value) {
        let mut input_text: String = String::new();
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        io::stdin()
            .read_line(&mut input_text)
            .expect("failed to read from stdin");
        let trimmed = input_text.trim();
        value = match trimmed.parse::<usize>() {
            Ok(n) => n,
            Err(_) => {
                println!("Failed to parse integer, try again");
                3
            },
        }
    }
    return value;
}