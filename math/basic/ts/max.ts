function max(a: number, b: number): number {
    return a > b ? a : b;
}

function min(a: number, b: number): number {
    return a < b ? a : b;
}

function maxOfArray(numbers: number[]): number {
    return Math.max(...numbers);
}

function minOfArray(numbers: number[]): number {
    return Math.min(...numbers);
}

function testMax(): void {
    console.log("最大值/最小值:");
    console.log(`max(5, 3) = ${max(5, 3)}`);
    console.log(`min(5, 3) = ${min(5, 3)}`);
    const numbers = [10, 25, 3, 100, 7];
    console.log(`数组 [${numbers.join(", ")}]:`);
    console.log(`最大值 = ${maxOfArray(numbers)}`);
    console.log(`最小值 = ${minOfArray(numbers)}`);
}

testMax();
export { max, min, maxOfArray, minOfArray, testMax };
