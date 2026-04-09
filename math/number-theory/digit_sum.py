"""
Copyright https://github.com/microwind
Digit Sum
"""

def digit_sum(n: int) -> int:
    total = 0
    while n > 0:
        total += n % 10
        n //= 10
    return total

def main():
    n = 12345
    print(f"Digit sum of {n} = {digit_sum(n)}")

if __name__ == "__main__":
    main()
