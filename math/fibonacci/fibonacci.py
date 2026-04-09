"""
Copyright https://github.com/microwind
Fibonacci Sequence
"""

def fibonacci(n: int) -> int:
    if n <= 1:
        return n
    first, second = 0, 1
    for _ in range(1, n):
        first, second = second, first + second
    return second

def main():
    print("Fibonacci Sequence:")
    for i in range(11):
        print(f"F({i}) = {fibonacci(i)}")

if __name__ == "__main__":
    main()
