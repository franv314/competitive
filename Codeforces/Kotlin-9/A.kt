fun solve() {
    val s = readln()
    var j = 0
    var d = true
    for (i in s.count() - 1 downTo 0) {
        if (!(s[i] in "0123456789") || (s[i] == '0' && !d)) {
            j = i
            break
        }
        if (s[i] != '0') d = false
    }

    for (i in 0..j) {
        print(s[i])
    }
    print("\n")
}

fun main() {
    val t = readln().toInt()
    for (i in 1..t) {
        solve()
    }
}