use std::io;

fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();

    stdin.read_line(&mut buf);
    let t: i32 = buf.trim().parse().unwrap();

    for _ in 0..t {
        buf.clear();
        stdin.read_line(&mut buf);
        let x = buf.as_bytes()[0];

        if String::from("codeforces").contains(|c| c == x.into()) {
            println!("YES");
        } else {
            println!("NO");
        }
    }
}