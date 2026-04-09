function gcd(a: number, b: number): number {
    a = Math.abs(a);
    b = Math.abs(b);
    while (b !== 0) {
        const temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

function lcm(a: number, b: number): number {
    if (a === 0 || b === 0) return 0;
    return Math.abs(a / gcd(a, b) * b);
}

function gcdExtended(a: number, b: number): [number, number, number] {
    if (b === 0) return [a, 1, 0];
    const [g, x1, y1] = gcdExtended(b, a % b);
    return [g, y1, x1 - Math.floor(a / b) * y1];
}

function testGCD(): void {
    console.log("GCD/LCM计算:");
    console.log(`gcd(48, 18) = ${gcd(48, 18)}`);
    console.log(`lcm(4, 6) = ${lcm(4, 6)}`);
}

testGCD();
export { gcd, lcm, gcdExtended, testGCD };
