use std::cmp;
use std::io;

const Å: u8 = u8::MAX;

fn cmp(fst: &[u8], snd: &[u8]) -> Option<Vec<u8>> {
    let s = cmp::min(fst.len(), snd.len());
    let mut can = vec![false; s + 1];

    can[s] = true;
    for i in (0..s).rev() {
        can[i] = if snd[i] > fst[i] {
            true
        } else if snd[i] == fst[i] {
            can[i + 1] || (snd[i] == b'a' && snd[i + 1] == b'a')
        } else if fst[i] != Å {
            i + 1 < s && snd[i] == b'a' && snd[i + 1] == b'a'
        } else {
            i + 1 < s && snd[i] == b'a' && snd[i + 1] == b'a' && can[i + 2]
        }
    }

    if !can[0] {
        return None;
    }

    let mut ans = snd.to_owned();
    for i in 0..ans.len() {
        if fst[i] < ans[i] {
            break;
        } else if fst[i] > ans[i] {
            ans[i] = Å;
            ans[i + 1] = Å;
            if fst[i] !=  Å {
                break;
            }
        } else if fst[i] == ans[i] && !can[i + 1] {
            ans[i] = Å;
            ans[i + 1] = Å;
            break;
        }
    }

    Some(ans)
}

fn solve(n: i32, arr: &[Vec<u8>]) -> bool {
    let mut old = arr[0].clone();
    for i in 1..n {
        if let Some(min_valid) = cmp(&old, &arr[i as usize]) {
            old = min_valid;
        } else {
            return false;
        }
    }
    true
}

fn main() -> io::Result<()> {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf)?;
    let n: i32 = buf.trim().parse().unwrap();

    let mut arr: Vec<Vec<u8>> = Vec::new();
    for _ in 0..n {
        buf.clear();
        stdin.read_line(&mut buf)?;

        arr.push(buf.as_bytes().to_owned());
    }

    if solve(n, &arr) {
        println!("YES");
    } else {
        println!("NO");
    }

    Ok(())
}
