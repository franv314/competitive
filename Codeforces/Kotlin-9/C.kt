fun solve() {
    val n = readln().toInt()
    val s = readln()
    val t = readln()

    var ans = n - 1

    for (i in 0..<n - 1) {
        if (s[i] != s[i + 1]) {
            ans--
        }
    }

    println(ans)  
}

fun main() {
    val t = readln().toInt()
    for (i in 1..t) {
        solve()
    }
}