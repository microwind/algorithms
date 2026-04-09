/**
 * Copyright https://github.com/microwind
 * Perfect Number Check
 */

function isPerfect(n) {
    if (n <= 1) return false;
    let sum = 1;
    for (let i = 2; i * i <= n; i++) {
        if (n % i === 0) {
            sum += i;
            if (i !== n / i) sum += n / i;
        }
    }
    return sum === n;
}

function main() {
    const perfects = [];
    for (let i = 1; i <= 1000; i++) {
        if (isPerfect(i)) perfects.push(i);
    }
    console.log("Perfect numbers up to 1000:", perfects.join(" "));
}

main();
if (typeof module !== 'undefined') module.exports = { isPerfect };
