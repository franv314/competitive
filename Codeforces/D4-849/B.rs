use std::io;

fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf);
    let t: i32 = buf.trim().parse().unwrap();

    'tests: for _ in 0..t {
        buf.clear();
        stdin.read_line(&mut buf);
        let _: i32 = buf.trim().parse().unwrap();

        buf.clear();
        stdin.read_line(&mut buf);
        
        let mut pos = (0, 0);
        for c in buf.trim().chars() {
            match c {
                'U' => pos.1 += 1,
                'D' => pos.1 -= 1,
                'R' => pos.0 += 1,
                'L' => pos.0 -= 1,
                _ => unreachable!(""),
            };
            if pos == (1, 1) {
                println!("YES");
                continue 'tests;
            }
        }
        println!("NO")
    }
}