use std::io;

fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf);
    let t: i32 = buf.trim().parse().unwrap();

    for _ in 0..t {
        buf.clear();
        stdin.read_line(&mut buf);
        let n: i32 = buf.trim().parse().unwrap();

        buf.clear();
        stdin.read_line(&mut buf);
        
        let a: Vec<_> = buf.split_whitespace().map(|x| x.parse::<i64>().unwrap()).collect();

        let neg = a.iter().filter(|x| x < &&0).count();
        let sum: i64 = a.iter().map(|x| x.abs()).sum();
        let min = a.iter().map(|x| x.abs()).min().unwrap();

        println!("{}", if neg & 1 == 0 { sum } else { sum - 2 * min });
    }
}