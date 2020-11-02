/**
 * @desc
 * 质因数分解kotlin语言示例
 */

fun facorize(number: Int): List<Int> {
    val result = ArrayList<Int>();
    var i = 2;
//    var num = number;
    while (i * i <= num) {
        while (num % i == 0) {
            num = num / i;
            result.add(i);
        }
        i++;
    }
    if (num > 1) {
        result.add(num);
    }
    return result;
}

fun main() {
    var num: Int = 20;
    println("prime factorize:");
    val result = facorize(num);
    for (i in result.indices) {
        // println("resule[${i}] = ${result[i]} and  result.size = ${result.size}");
        print(result[i]);
        if (i < result.size - 1) {
            print(" * ");
        }
    }
}

/**
jarry@jarrys-MacBook-Pro factor % kotlinc factor.kt -include-runtime -d factor.jar
Java HotSpot(TM) 64-Bit Server VM warning: Options -Xverify:none and -noverify were deprecated in JDK 13 and will likely be removed in a future release.
jarry@jarrys-MacBook-Pro factor % java  -jar factor.jar          
prime factorize:
2 * 2 * 5%
*/