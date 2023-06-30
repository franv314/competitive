use std::io;
use std::cmp;

struct Fenwick {
    size: usize,
    arr: Vec<i64>,
}

impl Fenwick {
    fn new(size: usize) -> Self {
        Fenwick { size, arr: vec![0; size] }
    }

    fn add(&mut self, x: i32, v: i64) {
        let mut x = x;
        while (x as usize) < self.size {
            self.arr[x as usize] += v;
            x += x & -x;
        }
    }

    fn query(&self, x: i32) -> i64 {
        let mut x = x;
        let mut ans = 0_i64;
        while x > 0 {
            ans += self.arr[x as usize];
            x -= x & -x;
        }
        ans
    }

    fn bin_search(&self, max: i64) -> usize {
        let mut taken = 0;
        let mut curr = 0_i64;
        let i = usize::BITS - self.size.leading_zeros() - 1;

        for x in (0..=i).rev() {
            if taken + (1 << x) >= self.size {
                continue;
            }
            let add = self.arr[taken + (1 << x)];
            if curr + add <= max {
                curr += add;
                taken += 1 << x;
            }
        }
        taken
    }
}

fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf);
    let t: i32 = buf.trim().parse().unwrap();

    for _ in 0..t {
        println!("{}", {
            buf.clear();
            stdin.read_line(&mut buf);
            let mut it = buf.split_whitespace().map(|x| x.parse().unwrap());
            let n: usize = it.next().unwrap();
            let c: usize = it.next().unwrap();

            buf.clear();
            stdin.read_line(&mut buf);

            let a: Vec<usize> = buf.split_whitespace().map(|x| x.parse().unwrap()).collect();
            
            let mut costs: Vec<_> = (1..=n).map(|x| (cmp::min(x + a[x - 1], n + 1 - x + a[x - 1]), x)).collect();
            costs.sort();

            let mut fenwick = Fenwick::new(n + 1);
            for i in 0..n {
                fenwick.add(i as i32 + 1, costs[i].0 as i64);
            }

            let mut max = 0;
            for j in 1..=n {
                let (cost, i) = costs[j - 1];
                let rem = (c as i64) - (a[i - 1] as i64) - (i as i64);
                if rem < 0 {
                    continue;
                }
                fenwick.add(j as i32, -(cost as i64));
                let mut taken = fenwick.bin_search(rem);
                if taken < j {
                    taken += 1;
                }
                max = cmp::max(max, taken as i32);
                fenwick.add(j as i32, cost as i64);
            }
            max
        });
    }
}