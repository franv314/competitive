use std::io;

fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf).unwrap();
    buf.pop();
    let q: i32 = buf.parse().unwrap();

    for _ in 0..q {
        buf.clear();
        stdin.read_line(&mut buf).unwrap();
        buf.pop();
        let k = buf.parse::<i64>().unwrap() - 1;

        let mut count = 0_i64;
        for i in 0_i64.. {
            let add = 9 * (i + 1) * 10_i64.pow(i as u32);
            
            if count + add > k {
                let num = (k - count) / (i + 1) + 10_i64.pow(i as u32);
                let pos = (k - count) % (i + 1);

                let ans = (num / 10_i64.pow((i - pos) as u32)) % 10;

                println!("{ans}");
                break;
            }
            count += add;
        }
    }
}