use std::io;
use std::collections::VecDeque;

fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf);
    let t: i32 = buf.trim().parse().unwrap();

    for _ in 0..t {
        buf.clear();
        stdin.read_line(&mut buf);
        let _: i32 = buf.trim().parse().unwrap();

        buf.clear();
        stdin.read_line(&mut buf);
        
        let mut s: VecDeque<_> = buf.trim().bytes().collect();
        while s.front() != s.back() {
            s.pop_front();
            s.pop_back();
        }
        println!("{}", s.len());
    }
}