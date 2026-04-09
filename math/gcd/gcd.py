"""
Copyright https://github.com/microwind
GCD - Greatest Common Divisor
"""

def gcd(x: int, y: int) -> int:
    while y != 0:
        x, y = y, x % y
    return x

def main():
    print(f"GCD(48, 18) = {gcd(48, 18)}")
    print(f"GCD(56, 98) = {gcd(56, 98)}")

if __name__ == "__main__":
    main()
