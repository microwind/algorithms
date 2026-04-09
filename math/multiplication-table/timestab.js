/**
 * Copyright https://github.com/microwind
 * Multiplication Table
 */

function printTable(max) {
    for (let i = 1; i <= max; i++) {
        let line = '';
        for (let j = 1; j <= i; j++) {
            line += `${j}×${i}=${(i * j).toString().padStart(2)}  `;
        }
        console.log(line);
    }
}

function main() {
    console.log("Multiplication Table (9x9):");
    printTable(9);
}

main();
if (typeof module !== 'undefined') module.exports = { printTable };
