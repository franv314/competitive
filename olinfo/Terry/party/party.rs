use std::io;

fn main() -> io::Result<()> {
    let mut buf = String::new();
    let stdin = io::stdin();

    stdin.read_line(&mut buf)?;

    buf.pop();
    let t = buf.parse::<i32>().unwrap();

    for tc in 1..=t {
        stdin.read_line(&mut buf)?;
        stdin.read_line(&mut buf)?;

        buf.clear();
        stdin.read_line(&mut buf)?;

        let ans: i32 = buf.split_whitespace()
            .map(|x| x.parse::<i32>().unwrap())
            .filter(|x| x > &0)
            .sum();

        println!("Case #{tc}: {ans}");
    }

    Ok(())
}