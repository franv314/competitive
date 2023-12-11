fun solve() {
    val (n, k) = readln().split(' ').map(String::toInt)
    var adj = MutableList(n) { MutableList<Int>(0) { 0 } }

    for (i in 2..n) {
        val (u, v) = readln().split(' ').map(String::toInt)
        adj[u - 1].add(v - 1)
        adj[v - 1].add(u - 1)
    }

    var sizes = MutableList<Long>(0) { 0 }

    fun dfs(node: Int, par: Int): Int {
        var size = 1
        for (x in adj[node]) {
            if (x == par) continue
            size += dfs(x, node)
        }
        sizes.add(size.toLong() * (n - size))
        return size
    }

    dfs(0, -1)
    sizes.sort()
    
    var ans: Long = 0
    for (i in 0..<n - k + 1) ans += 2 * sizes[i]
    for (i in n - k + 1..<n) ans += sizes[i]

    println(ans)
}

fun main() {
    val t = readln().toInt()
    for (i in 1..t) {
        solve()
    }
}