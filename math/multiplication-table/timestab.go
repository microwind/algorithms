// Copyright https://github.com/microwind
// Multiplication Table

package main

import "fmt"

func printTable(max int) {
	for i := 1; i <= max; i++ {
		for j := 1; j <= i; j++ {
			fmt.Printf("%d×%d=%2d  ", j, i, i*j)
		}
		fmt.Println()
	}
}

func main() {
	fmt.Println("Multiplication Table (9x9):")
	printTable(9)
}
