package main

import "fmt"

func power(base float64, exp int) float64 {
	if exp < 0 {
		return 1.0 / power(base, -exp)
	}
	if exp == 0 {
		return 1
	}
	result := 1.0
	for exp > 0 {
		if exp&1 == 1 {
			result *= base
		}
		base *= base
		exp >>= 1
	}
	return result
}

func powerMod(base, exp, mod int64) int64 {
	result := int64(1 % mod)
	base = base % mod
	for exp > 0 {
		if exp&1 == 1 {
			result = (result * base) % mod
		}
		base = (base * base) % mod
		exp >>= 1
	}
	return result
}

func TestPowerMain() {
	fmt.Println("幂运算:")
	for i := 0; i <= 10; i++ {
		fmt.Printf("2^%d = %.0f\n", i, power(2, i))
	}
	fmt.Printf("3^100 mod 1000 = %d\n", powerMod(3, 100, 1000))
}
