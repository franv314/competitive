use std::io;
use std::cmp;

fn main() -> io::Result<()> {
    let mut buf = String::new();
    let stdin = io::stdin();

    stdin.read_line(&mut buf)?;
    buf.pop();
    let t = buf.parse::<i32>().unwrap();

    for tc in 1..=t {
        stdin.read_line(&mut buf)?;
        buf.clear();
        stdin.read_line(&mut buf)?;
        let mut it = buf.split_whitespace().map(|x| x.parse::<usize>().unwrap());
        
        let n = it.next().unwrap();
        let m = it.next().unwrap();
        let k = it.next().unwrap();
        let a = it.next().unwrap();
        let b = it.next().unwrap();

        let mut grid = vec![vec![0; m]; n];
        for _ in 0..k {
            buf.clear();
            stdin.read_line(&mut buf)?;
            let mut it = buf.split_whitespace().map(|x| x.parse::<usize>().unwrap());
            
            let x = it.next().unwrap();
            let y = it.next().unwrap();

            grid[x][y] += 1;
        }

        let mut ps = vec![vec![0; m + 1]; n + 1];
        for x in 1..=n {
            for y in 1..=m {
                ps[x][y] = ps[x - 1][y] + ps[x][y - 1] - ps[x - 1][y - 1] + grid[x - 1][y - 1];
            }
        }
        
        let mut mi = i32::MAX;
        for x in 0..=n - a {
            for y in 0..=m - b {
                let val = ps[x + a][y + b] + ps[x][y] - ps[x + a][y] - ps[x][y + b];
                mi = cmp::min(mi, val);
            }
        }

        println!("Case #{tc}: {mi}");
    }

    Ok(())
}