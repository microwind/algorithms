/**
 * @desc
 * 质因数分解TypeScript语言示例
 */
class PrimeFactor {
  num: number;
  result: Array<number>;
  constructor(num: number) {
    this.num = num;
    console.log("being init");
  }
  factorize() {
    let i = 2;
    this.result = [];
    let num = this.num;
    while (i * i <= num) {
      while (num % i === 0) {
        console.log(this.result);
        this.result.push(i);
        num /= i;
      }
      i++;
    }
    if (num > 1) {
      this.result.push(num);
    }
  }
}

// test
const num = 9102;
const primeFactor = new PrimeFactor(num);
primeFactor.factorize();
console.log(primeFactor.result.join(" * "));

/**
  jarry@jarrys-MacBook-Pro factor % tsc PrimeFactor.ts 
  jarry@jarrys-MacBook-Pro factor % node PrimeFactor.js
  being init
  []
  [ 2 ]
  [ 2, 3 ]
  2 * 3 * 37 * 41
 */