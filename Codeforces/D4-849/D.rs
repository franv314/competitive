use std::io;
use std::cmp;
use std::collections::HashMap;

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
        
        let mut s: Vec<char> = buf.trim().chars().collect();

        let mut am_l: HashMap<char, i32> = HashMap::new();
        let mut am_r: HashMap<char, i32> = HashMap::new();
        for &c in &s {
            if let Some(v) = am_r.get_mut(&c) {
                *v += 1;
            } else {
                am_r.insert(c, 1);
            }
        }

        let mut max = am_l.len() + am_r.len();
        for &c in &s {
            if let Some(v) = am_l.get_mut(&c) {
                *v += 1;
            } else {
                am_l.insert(c, 1);
            }

            *am_r.get_mut(&c).unwrap() -= 1;
            if (am_r.get(&c).unwrap() == &0) {
                am_r.remove(&c);
            }

            max = cmp::max(max, am_l.len() + am_r.len())
        }

        println!("{max}");
    }
}