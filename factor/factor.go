package main

/**
 * @desc
 * 质因数分解go语言示例
 */
import "fmt"

func factorize(num int, len int) []int {
	var result = make([]int, len)
	var i int = 2
	var resultIdx int = 0
	for i*i <= num {
		for num%i == 0 {
			result[resultIdx] = i
			num /= i
			resultIdx++
		}
		i++
	}
	if num > 1 {
		result[resultIdx] = num
	}
	return result
}

func main() {
	fmt.Println("Hello, 质因数分解!")
	var num int = 120
	var len = num / 2
	var result []int = factorize(num, len)
	for i := 0; i < len; i++ {
		if result[i] <= 0 {
			break
		}
		if i > 0 {
			fmt.Print(" * ")
		}
		fmt.Print(result[i])
	}
}

/**
jarry@jarrys-MacBook-Pro factor % go version
go version go1.15 darwin/amd64
jarry@jarrys-MacBook-Pro factor % go build factor.go
jarry@jarrys-MacBook-Pro factor % ./factor
Hello, 质因数分解!
2 * 2 * 2 * 3 * 5%
jarry@jarrys-MacBook-Pro factor % go run factor.go
Hello, 质因数分解!
2 * 2 * 2 * 3 * 5%
*/
