"""
Copyright https://github.com/microwind
Multiplication Table
"""

def print_table(max_n: int) -> None:
    for i in range(1, max_n + 1):
        for j in range(1, i + 1):
            print(f"{j}×{i}={i*j:2d}  ", end="")
        print()

def main():
    print("Multiplication Table (9x9):")
    print_table(9)

if __name__ == "__main__":
    main()
