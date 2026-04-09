"""
Copyright https://github.com/microwind
Zeno's Paradox - Dichotomy Paradox
"""

def zeno_paradox(total_distance: float, steps: int) -> None:
    remaining = total_distance
    print("Zeno's Dichotomy Paradox:")
    for i in range(1, steps + 1):
        remaining /= 2
        print(f"Step {i}: remaining distance = {remaining:.6f}")

def main():
    zeno_paradox(1.0, 10)

if __name__ == "__main__":
    main()
