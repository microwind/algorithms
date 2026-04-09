"""
Copyright https://github.com/microwind
Prime Number Check
"""

def is_prime(n: int) -> bool:
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

def main():
    primes = [i for i in range(1, 51) if is_prime(i)]
    print(f"Primes up to 50: {' '.join(map(str, primes))}")

if __name__ == "__main__":
    main()
