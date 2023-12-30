use std::io;
use std::collections::HashMap;

fn solve(n: usize, x: i32, t: &[i64]) -> i64 {
    let l = &t[..n / 2];
    let r = &t[n / 2..];

    let mut vals: HashMap<i64, i64> = HashMap::new();
    let mut ans = 0_i64;

    for mask in 0..(1 << l.len()) {
        let sum: i64 = (0..l.len()).filter(|i| mask & (1 << i) != 0).map(|i| l[i]).sum();
        vals.entry(sum).and_modify(|v| *v += 1).or_insert(1);
    }

    for mask in 0..(1 << r.len()) {
        let sum: i64 = (0..r.len()).filter(|i| mask & (1 << i) != 0).map(|i| r[i]).sum();
        ans += vals.get(&(x as i64 - sum)).unwrap_or(&0);
    }

    ans
}

fn main() -> io::Result<()> {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf)?;
    let mut it = buf.split_whitespace().map(|x| x.parse::<i32>().unwrap());

    let n = it.next().unwrap();
    let x = it.next().unwrap();

    buf.clear();
    stdin.read_line(&mut buf)?;
    let t: Vec<i64> = buf.split_whitespace().map(|x| x.parse().unwrap()).collect();

    println!("{}", solve(n as _, x, &t));

    Ok(())
}