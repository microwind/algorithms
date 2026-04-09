/**
 * 数学基础 - 平均值计算 (Average)
 * 算术平均值，避免溢出
 */

function average(numbers) {
    if (numbers.length === 0) {
        throw new Error("数组不能为空");
    }
    const sum = numbers.reduce((acc, val) => acc + val, 0);
    return sum / numbers.length;
}

function averageSafe(a, b) {
    return a / 2 + b / 2;
}

function testAverage() {
    console.log("平均值计算:");
    const numbers = [10, 20, 30, 40, 50];
    console.log(`numbers = [${numbers.join(", ")}]`);
    console.log(`平均值 = ${average(numbers)}`);
    
    console.log("\n避免溢出:");
    const a = Number.MAX_SAFE_INTEGER - 100;
    const b = Number.MAX_SAFE_INTEGER - 200;
    console.log(`a = ${a}, b = ${b}`);
    console.log(`平均值 = ${averageSafe(a, b)}`);
}

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { average, averageSafe, testAverage };
    if (require.main === module) testAverage();
} else {
    window.averageModule = { average, averageSafe, testAverage };
}
