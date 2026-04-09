// Copyright https://github.com/microwind
// Sieve of Eratosthenes

package main

import "fmt"

func sieve(n int) {
	isPrime := make([]bool, n+1)
	for i := 2; i <= n; i++ {
		isPrime[i] = true
	}
	
	for p := 2; p*p <= n; p++ {
		if isPrime[p] {
			for i := p * p; i <= n; i += p {
				isPrime[i] = false
			}
		}
	}
	
	fmt.Printf("Primes up to %d: ", n)
	for i := 2; i <= n; i++ {
		if isPrime[i] {
			fmt.Printf("%d ", i)
		}
	}
	fmt.Println()
}

func main() {
	sieve(50)
}
