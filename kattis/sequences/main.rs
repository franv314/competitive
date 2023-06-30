use std::fmt;
use std::io;
use std::ops::{Add, AddAssign, Mul};

const MOD: i32 = 1_000_000_007;

#[derive(Clone, Copy)]
struct ModInt(i32);

impl Add for ModInt {
    type Output = Self;
    fn add(self, rhs: Self) -> Self::Output {
        Self((self.0 + rhs.0) % MOD)
    }
}

impl AddAssign for ModInt {
    fn add_assign(&mut self, rhs: Self) {
        self.0 = (self.0 + rhs.0) % MOD;
    }
}

impl Mul for ModInt {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self::Output {
        Self(((self.0 as i64 * rhs.0 as i64) % MOD as i64) as _)
    }
}

impl fmt::Display for ModInt {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

fn solve(sequence: &[u8]) -> ModInt {
    let mut powers = vec![ModInt(1); sequence.len()];
    for i in 1..sequence.len() {
        powers[i] = powers[i - 1] * ModInt(2);
    }

    let mut ans = ModInt(0);
    let mut j = sequence.into_iter().filter(|x| **x == b'?').count();
    let mut q = 0;
    let mut k = 0;
    for &d in sequence {
        if d == b'?' {
            j -= 1;
        }

        if d == b'0' || d == b'?' {
            ans += (
                if q == 0 { ModInt(0) } else { ModInt(q as _) * powers[q - 1] }
                + ModInt(k) * powers[q]
            ) * powers[j];
        }
        if d == b'?' {
            q += 1;
        }
        if d == b'1' {
            k += 1;
        }
    }

    ans
}

fn main() -> io::Result<()> {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.read_line(&mut input)?;

    println!("{}", solve(&input.trim().as_bytes()));

    Ok(())
}
