use std::io;
use std::cmp;
use cp_library::inout::{InputReader, OutputWriter};
use cp_library::ds::coord_comp::CoordinateCompressor;
use cp_library::ds::segtree::SegTree;
use cp_library::binsearch::{first_true, first_none};

fn solve(
    rin: &mut InputReader<io::Stdin>,
    rout: &mut OutputWriter<io::Stdout>
) {
    let n: usize = rin.get();
    let mut points = vec![(0, 0); n];

    for i in 0..n {
        points[i] = (rin.get(), rin.get());
    }

    points.sort();

    let comp = CoordinateCompressor::from_coords(points.iter().map(|(_, y)| *y).collect());
    let mut left = SegTree::<usize>::new(comp.size());
    let mut right = SegTree::<usize>::new(comp.size());

    for (_, y) in &points {
        let y = comp.compress(y);
        left.update(y, &(left[y] + 1));
    }

    let check_cnt = |segtree: &SegTree<usize>, k: usize| {
        if 2 * k > segtree.query(0, comp.size()) {
            return (0, 0);
        }
        
        let l = first_true(0, comp.size(), |r| segtree.query(0, r + 1) >= k);
        let r = first_true(0, comp.size(), |r| segtree.query(r + 1, comp.size()) < k);

        (l, r)
    };

    let mut ans = (0, 0, 0);

    for (i, &(x, y)) in points.iter().enumerate() {
        if i == 0 || x != points[i - 1].0 {
            if let (c, Some(y)) = first_none(1, 1 + n / 4, |k| {
                let (ll, lr) = check_cnt(&left, k);
                let (rl, rr) = check_cnt(&right, k);

                let l = cmp::max(ll, rl);
                let r = cmp::min(lr, rr);

                if r <= l {
                    None
                } else {
                    Some(r)
                }
            }) {
                ans = cmp::max(ans, (c - 1, x, comp.decompress(y)));
            }
        }

        let y = comp.compress(&y);
        left.update(y, &(left[y] - 1));
        right.update(y, &(right[y] + 1));
    }

    rout.put_d(&ans.0, '\n');
    rout.put_d(&ans.1, ' ');
    rout.put_d(&ans.2, '\n');
}

fn main() {
    let mut rin = InputReader::new(io::stdin());
    let mut rout = OutputWriter::new(io::stdout());

    let t: usize = rin.get();

    for _ in 0..t {
        solve(&mut rin, &mut rout);
    }
}
