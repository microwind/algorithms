// Copyright https://github.com/microwind
// Zeno's Paradox - Dichotomy Paradox

package main

import "fmt"

func zenoParadox(totalDistance float64, steps int) {
	remaining := totalDistance
	fmt.Println("Zeno's Dichotomy Paradox:")
	for i := 1; i <= steps; i++ {
		remaining /= 2
		fmt.Printf("Step %d: remaining distance = %.6f\n", i, remaining)
	}
}

func main() {
	zenoParadox(1.0, 10)
}
