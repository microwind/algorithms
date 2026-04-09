function average(numbers: number[]): number {
    if (numbers.length === 0) {
        throw new Error("数组不能为空");
    }
    const sum = numbers.reduce((acc, val) => acc + val, 0);
    return sum / numbers.length;
}

function averageSafe(a: number, b: number): number {
    return a / 2 + b / 2;
}

function testAverage(): void {
    console.log("平均值计算:");
    const numbers = [10, 20, 30, 40, 50];
    console.log(`数组 [${numbers.join(", ")}]`);
    console.log(`平均值 = ${average(numbers)}`);
}

testAverage();
export { average, averageSafe, testAverage };
