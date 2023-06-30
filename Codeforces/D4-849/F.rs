use std::io;
use std::cmp;

struct Fenwick {
    size: usize,
    arr: Vec<i32>,
}

impl Fenwick {
    fn new(size: usize) -> Self {
        Self {
            size,
            arr: vec![0; size],
        }
    }

    fn add(&mut self, x: i32, v: i32) {
        let mut x = x;
        while (x as usize) < self.size {
            self.arr[x as usize] += v;
            x += x & (-x)
        }
    }

    fn query(&self, x: i32) -> i32 {
        let mut x = x;
        let mut ans = 0;
        while x > 0 {
            ans += self.arr[x as usize];
            x -= x & (-x);
        }
        ans
    }
}

fn sums(x: i32) -> [i32; 4] {
    let mut ans = [x; 4];
    for i in 1..4 {
        ans[i] = ans[i - 1].to_string().bytes().map(|x| x as i32 - 48).sum();
    }
    ans
}

fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf);
    let t: i32 = buf.trim().parse().unwrap();

    for _ in 0..t {
        buf.clear();
        stdin.read_line(&mut buf);
        let mut it = buf.split_whitespace();
        let n: i32 = it.next().unwrap().parse().unwrap();
        let q: i32 = it.next().unwrap().parse().unwrap();

        buf.clear();
        stdin.read_line(&mut buf);
        let a: Vec<[i32; 4]> = buf.split_whitespace().map(|x| sums(x.parse().unwrap())).collect();

        let mut fenwick = Fenwick::new(n as usize + 1);
        for _ in 0..q {
            buf.clear();
            stdin.read_line(&mut buf);
            let mut it = buf.split_whitespace();
            let r#type: i32 = it.next().unwrap().parse().unwrap();

            if r#type == 1 {
                let l: i32 = it.next().unwrap().parse().unwrap();
                let r: i32 = it.next().unwrap().parse().unwrap();

                fenwick.add(l, 1);
                fenwick.add(r + 1, -1);
            } else {
                let x: i32 = it.next().unwrap().parse().unwrap();
                let y = cmp::min(fenwick.query(x), 3);

                println!("{}", a[(x - 1) as usize][y as usize]);
            }
        }
    }
}