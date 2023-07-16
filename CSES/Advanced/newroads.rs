use std::io;
use std::mem;
 
struct DSU {
    arr: Vec<Vec<(usize, i32)>>,
}
 
impl DSU {
    fn new(size: usize) -> DSU {
        DSU { arr: vec![vec![(0, -1)]; size] }
    }
 
    fn find(&self, u: usize, t: usize) -> usize {
        let i = self.arr[u].partition_point(|&(t0, _)| t0 <= t) - 1;
        let (_, j) = self.arr[u][i];
        
        return if j < 0 { u } else { self.find(j as usize, t) }
    }
 
    fn merge(&mut self, u: usize, v: usize, t: usize) {
        let mut u = self.find(u, usize::MAX);
        let mut v = self.find(v, usize::MAX);
    
        if u == v {
            return;
        }
 
        let &(_, mut u_size) = self.arr[u].last().unwrap();
        let &(_, mut v_size) = self.arr[v].last().unwrap();
 
        if u_size > v_size {
            mem::swap(&mut u, &mut v);
            mem::swap(&mut u_size, &mut v_size);
        }
 
        self.arr[u].push((t, u_size + v_size));
        self.arr[v].push((t, u as i32));
    }
}
 
fn main() -> io::Result<()> {
    let stdin = io::stdin();
    let mut buf = String::new();
 
    buf.clear();
    stdin.read_line(&mut buf)?;
    let mut it = buf.split_whitespace().map(|s| s.parse::<usize>().unwrap());
    let n = it.next().unwrap();
    let m = it.next().unwrap();
    let q = it.next().unwrap();
    
    let mut dsu = DSU::new(n + 1);
    
    for t in 1..=m {
        buf.clear();
        stdin.read_line(&mut buf)?;
        let mut it = buf.split_whitespace().map(|s| s.parse::<usize>().unwrap());
        let u = it.next().unwrap();
        let v = it.next().unwrap();
 
        dsu.merge(u, v, t);
    }
 
    let mut string_ans = String::new();
    for _ in 0..q {
        buf.clear();
        stdin.read_line(&mut buf)?;
        let mut it = buf.split_whitespace().map(|s| s.parse::<usize>().unwrap());
        let u = it.next().unwrap();
        let v = it.next().unwrap();
 
        let mut l = 0;
        let mut r = m + 2;
        while l + 1 < r {
            let m = (l + r - 1) / 2;
            if dsu.find(u, m) != dsu.find(v, m) {
                l = m + 1;
            } else {
                r = m + 1;
            }
        }
 
        string_ans += &format!("{}\n", if l > m { -1 } else { l as i32 } );
    }
 
    print!("{string_ans}");
 
    Ok(())
}