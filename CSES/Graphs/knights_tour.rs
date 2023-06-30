use std::io;

const AVAILABLE: [[u8; 8]; 8] = [
    [2, 3, 4, 4, 4, 4, 3, 2,],
    [3, 4, 6, 6, 6, 6, 4, 3,],
    [4, 6, 8, 8, 8, 8, 6, 4,],
    [4, 6, 8, 8, 8, 8, 6, 4,],
    [4, 6, 8, 8, 8, 8, 6, 4,],
    [4, 6, 8, 8, 8, 8, 6, 4,],
    [3, 4, 6, 6, 6, 6, 4, 3,],
    [2, 3, 4, 4, 4, 4, 3, 2,],
];

struct Solver {
    curr: [[u8; 8]; 8]
}

impl Solver {
    fn new() -> Solver {
        Solver {curr: [[0; 8]; 8]}
    }

    fn solve(&mut self, x: i8, y: i8, depth: u8) -> bool {
        self.curr[x as usize][y as usize] = depth;
        if depth == 64 {
            return true;
        }

        let mut moves: Vec<_> = vec![(1, 2), (1, -2), (-1, 2), (-1, -2), (2, 1), (2, -1), (-2, 1), (-2, -1)]
            .iter()
            .map(|(dx, dy)| (x + dx, y + dy))
            .filter(|(px, py)| px >= &0 && px < &8 && py >= &0 && py < &8)
            .filter(|(px, py)| self.curr[*px as usize][*py as usize] == 0)
            .collect();

        moves.sort_by_key(|(px, py)| AVAILABLE[*px as usize][*py as usize]);

        for (px, py) in moves {
            if self.solve(px, py, depth + 1) {
                return true;
            }
        }
        self.curr[x as usize][y as usize] = 0;
        false
    }

    fn print(&self) {
        for i in 0..8 {
            for j in 0..8 {
                print!("{} ", self.curr[j][i]);
            }
            println!();
        }
    }
}

fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf).unwrap();

    let mut it = buf.split_whitespace().map(|x| x.parse::<i8>().unwrap());

    let x = it.next().unwrap() - 1;
    let y = it.next().unwrap() - 1;

    let mut path = Solver::new();
    path.solve(x, y, 1);
    path.print();
}