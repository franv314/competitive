fun solve() {
    val n = readln().toInt()
    val arr = readln().split(' ').map(String::toInt)
    
    var r1 = arr[0]
    var r2 = -1
    for (v in arr) {
        if (v % r1 != 0) {
            r2 = v
            break
        }
    }

    val r1l = MutableList<Int>(0) { 0 }
    val r2l = MutableList<Int>(0) { 0 }

    for (v in arr) {
        if (v % r1 == 0) {
            r1l.add(v)
        }
        if (r2 != -1 && v % r2 == 0) {
            r2l.add(v)
        }
        if (r2 != -1) {
            if (v % r1 != 0 && v % r2 != 0) {
                println("INVALID")
                return
            }
        }
    }

    r1l.sort()
    r2l.sort()

    for (i in 0..r1l.count() - 1) {
        if ((i + 1).toLong() * r1 != r1l[i].toLong()) {
            println("INVALID")
            return
        }
    }
    for (i in 0..r2l.count() - 1) {
        if ((i + 1).toLong() * r2 != r2l[i].toLong()) {
            println("INVALID")
            return
        }
    }

    if (r2 != -1) {
        var last_1 = r2l.last() / r1 * r1;
        var last_2 = r1l.last() / r2 * r2;

        if (last_1 > r1l.last() || last_2 > r2l.last()) {
            println("INVALID")
            return
        }
    }

    println("VALID")
}

fun main() {
    val t = readln().toInt()
    for (i in 1..t) {
        solve()
    }
}