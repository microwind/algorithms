/** 
 * @desc
 * dart语言版
 */
fibonacciFor(int num)
{
    var i, result;
    var first = 0;
    var second = 1;
    print('fibonacci(${first}) =   ${first}');
    print('fibonacci(${second}) =   ${second}');
    for (i = 2; i <= num; i++)
    {
        result = first + second;
        print('fibonacci(${i}) =   ${result}');
        first = second;
        second = result;
    }
}

void main() {
  int fibonacciRecurse(int n) {
    if (n == 0 || n == 1) return n;
    return fibonacciRecurse(n - 1) + fibonacciRecurse(n - 2);
  }
  var result = fibonacciRecurse(20);
  // fibonacciRecurse
  print('fibonacciRecurse(20):');
  print('fibonacciRecurse result:${result}');

  print('\r\n');

  // fibonacciFor
  print('fibonacciFor(20):');
  fibonacciFor(20);
}

/** test
jarry@jarrys-MacBook-Pro number % dart --version
Dart SDK version: 2.10.2 (stable) on "macos_x64"
jarry@jarrys-MacBook-Pro number % dart fibonacci.dart
fibonacciRecurse(20):
fibonacciRecurse result:6765


fibonacciFor(20):
fibonacci(0) =   0
fibonacci(1) =   1
fibonacci(2) =   1
fibonacci(3) =   2
fibonacci(4) =   3
fibonacci(5) =   5
fibonacci(6) =   8
fibonacci(7) =   13
fibonacci(8) =   21
fibonacci(9) =   34
fibonacci(10) =   55
fibonacci(11) =   89
fibonacci(12) =   144
fibonacci(13) =   233
fibonacci(14) =   377
fibonacci(15) =   610
fibonacci(16) =   987
fibonacci(17) =   1597
fibonacci(18) =   2584
fibonacci(19) =   4181
fibonacci(20) =   6765
*/