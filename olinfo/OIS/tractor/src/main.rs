use rand::prelude::*;
use rand::distributions::WeightedIndex;
use std::collections::HashMap;

// A  = 1, B = 2 (fulla subtask 3)

const A: i32 = 2;
const B: i32 = 3;
const MAX_ITER: i32 = 100_000;

fn solve(n: usize, k: usize) -> (i64, Vec<usize>) {
    let cost = |a: usize, b: usize| -> i64 {
        let d = if a > b { a - b } else { b - a };
        if d < k { i64::MAX } else { d as i64 }
    };

    let path_cost = |a: &[usize]| -> i64 {
        a.windows(2).map(|x| cost(x[0], x[1])).sum()
    };

    let mut rng = thread_rng();
    //let mut r = vec![vec![1_f64; n]; n];
    let mut r: HashMap<(usize, usize), f64> = HashMap::new();

    let mut best_cost = i64::MAX;
    let mut best_path = Vec::<usize>::new();

    'out: for z in 0..MAX_ITER {
        let mut visited = vec![false; n];
        let mut weights = vec![0.; n];
        let mut path = vec![0_usize];
        visited[0] = true;

        for _ in 1..n {
            for i in 0..n {
                weights[i] = if visited[i] {
                    0.
                } else {
                    let last = *path.last().unwrap();
                    if cost(last, i) == i64::MAX {
                        0.
                    } else {
                        let weight = r.get(&(last, i)).unwrap_or(&1.);
                        weight.powi(A) * (cost(last, i) as f64).powi(-B)
                    }
                }
            }
            if weights.iter().all(|x| x == &0.) {
                continue 'out;
            }

            let dist = WeightedIndex::new(&weights).unwrap();
            let new = dist.sample(&mut rng);
            path.push(new);
            visited[new] = true;
        }

        let cost = path_cost(&path);

        let inv_cost = 1. / cost as f64;
        for w in path.windows(2) {
            if r.get(&(w[0], w[1])).is_none() {
                r.insert((w[0], w[1]), 1.);
            }
            *r.get_mut(&(w[0], w[1])).unwrap() += inv_cost;
        }

        if cost < best_cost {
            best_cost = cost;
            best_path = path.clone();
        }
        eprintln!("{z} {} {}", path_cost(&path), best_cost);
    }
    (best_cost, best_path)
}

fn main() {
    let best = solve(100000, 5);
    println!("{:?},", best);
    /*println!("[None,");
    for n in 31..=100 {
        println!("[None,");
        for k in 1..=5 {
            
            eprintln!("{n} {k}");

            let best = solve(n, k);
            println!("{:?},", best);
        }
        println!("],");
    }
    println!("]");*/
}
