use std::collections::BinaryHeap;
use std::io;

fn main() -> io::Result<()> {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf)?;
    buf.pop();
    let n = buf.parse::<usize>().unwrap();

    buf.clear();
    stdin.read_line(&mut buf)?;
    let x: Vec<i64> = buf.split_whitespace().map(|x| x.parse().unwrap()).collect();

    let mut pq = BinaryHeap::new();
    for v in &x {
        pq.push(v);
        pq.push(v);

        pq.pop();
    }

    let mut val: i64 = x.iter().sum();
    let mut last: i64 = 0;
    let mut slope: i64 = 0;

    while let Some(&v) = pq.pop() {
        val -= slope * (last - v);
        last = v;
        slope += 1;
    }
    val -= slope * last;

    println!("{val}");

    Ok(())
}