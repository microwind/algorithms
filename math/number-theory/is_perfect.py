"""
Copyright https://github.com/microwind
Perfect Number Check
"""

def is_perfect(n: int) -> bool:
    if n <= 1:
        return False
    total = 1
    i = 2
    while i * i <= n:
        if n % i == 0:
            total += i
            if i != n // i:
                total += n // i
        i += 1
    return total == n

def main():
    perfects = [i for i in range(1, 1001) if is_perfect(i)]
    print(f"Perfect numbers up to 1000: {' '.join(map(str, perfects))}")

if __name__ == "__main__":
    main()
