use std::io;

fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf);
    let t: i32 = buf.trim().parse().unwrap();

    for _ in 0..t {
        buf.clear();
        stdin.read_line(&mut buf);
        let mut it = buf.split_whitespace().map(|x| x.parse().unwrap());
        let n: usize = it.next().unwrap();
        let c: usize = it.next().unwrap();

        buf.clear();
        stdin.read_line(&mut buf);

        let a: Vec<usize> = buf.split_whitespace().map(|x| x.parse().unwrap()).collect();
        
        let mut costs: Vec<_> = (1..=n).map(|x| x + a[x - 1]).collect();
        costs.sort();

        println!("{}", {
            let mut acc = 0;
            let mut cnt = 0;
            for x in costs {
                if acc + x <= c {
                    acc += x;
                    cnt += 1;
                } else {
                    break;
                }
            }
            cnt
        });
    }
}