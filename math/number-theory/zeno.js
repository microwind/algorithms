/**
 * Copyright https://github.com/microwind
 * Zeno's Paradox - Dichotomy Paradox
 */

function zenoParadox(totalDistance, steps) {
    let remaining = totalDistance;
    console.log("Zeno's Dichotomy Paradox:");
    for (let i = 1; i <= steps; i++) {
        remaining /= 2;
        console.log(`Step ${i}: remaining distance = ${remaining.toFixed(6)}`);
    }
}

function main() {
    zenoParadox(1.0, 10);
}

main();
if (typeof module !== 'undefined') module.exports = { zenoParadox };
