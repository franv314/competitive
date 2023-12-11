fun solve() {
    val s = readln()

    if (!('+' in s)) {
        println("-1")
        return
    }

    if (!('-' in s)) {
        println("1 1")
        return
    }

    var first = 0
    var last = 0

    for (i in 0..<s.count()) {
        if (s[i] == '-') {
            first = i
            break
        }
    }

    for (i in s.count() - 1 downTo 0) {
        if (s[i] == '+') {
            last = i
            break
        }
    }

    var cnt = 0
    for (i in 0..<s.count()) {
        if (i == first && first < last) cnt++
        else if (i == last && first < last) cnt--
        else if (s[i] == '+') cnt++
        else cnt--

        if (cnt < 0) {
            println("-1")
            return
        }
    }

    if (first < last) println("${first + 1} ${last + 1}")
    else println("1 1")
}

fun main() {
    val t = readln().toInt()
    for (i in 1..t) {
        solve()
    }
}