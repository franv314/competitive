fun solve() {
    val n = readln().toInt()
    val arr = readln().split(' ')

    var snd = -1
    var last = -1
    var rem = false
    for (x in arr) {
        val y = x.toInt()
        if (y < last) {
            if (rem) {
                println("NO")
                return
            }
            if (y < snd) {
            } else if (y == snd) {
                snd = last
                last = y + 1
            } else {
                snd = last
                last = y
            }
            rem = true;
        } else if (y == last) {
            snd = last
            last = y + 1
        } else {
            snd = last
            last = y;
        }
    }

    println("YES")
}

fun main() {
    val t = readln().toInt()
    for (i in 1..t) {
        solve()
    }
}