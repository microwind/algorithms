"""
Copyright https://github.com/microwind
Check if number is even/odd
"""

def is_even(n: int) -> bool:
    return n % 2 == 0

def main():
    test_numbers = [2, 3, 4, 5, 10, 15]
    for n in test_numbers:
        print(f"{n} is {'even' if is_even(n) else 'odd'}")

if __name__ == "__main__":
    main()
