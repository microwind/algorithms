/**
 * 数学基础 - 最大值与最小值 (Max and Min)
 * 计算两个或多个数的最大值和最小值
 */

function max(a, b) {
    return a > b ? a : b;
}

function min(a, b) {
    return a < b ? a : b;
}

function maxOfArray(numbers) {
    return Math.max(...numbers);
}

function minOfArray(numbers) {
    return Math.min(...numbers);
}

function testMax() {
    console.log("最大值/最小值演示:");
    console.log(`max(5, 3) = ${max(5, 3)}`);
    console.log(`min(5, 3) = ${min(5, 3)}`);
    const numbers = [10, 25, 3, 100, 7];
    console.log(`数组 [${numbers.join(", ")}]:`);
    console.log(`最大值 = ${maxOfArray(numbers)}`);
    console.log(`最小值 = ${minOfArray(numbers)}`);
}

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { max, min, maxOfArray, minOfArray, testMax };
    if (require.main === module) testMax();
} else {
    window.maxModule = { max, min, maxOfArray, minOfArray, testMax };
}
