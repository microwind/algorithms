"""
Copyright https://github.com/microwind
Approximate Equality Check
"""

def approx_equal(a: float, b: float, epsilon: float) -> bool:
    return abs(a - b) < epsilon

def main():
    print("Approximate Equality Check:")
    print(f"0.1 + 0.2 ≈ 0.3: {approx_equal(0.1 + 0.2, 0.3, 1e-10)}")

if __name__ == "__main__":
    main()
