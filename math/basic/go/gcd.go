package main

import "fmt"

func gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func lcm(a, b int) int {
	if a == 0 || b == 0 {
		return 0
	}
	return (a / gcd(a, b)) * b
}

func TestGCDMain() {
	fmt.Println("GCD/LCM计算:")
	fmt.Printf("gcd(48, 18) = %d\n", gcd(48, 18))
	fmt.Printf("lcm(4, 6) = %d\n", lcm(4, 6))
}
