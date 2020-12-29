/**
 * @desc
 * 质因数分解TypeScript语言示例
 */
var PrimeFactor = /** @class */ (function () {
    function PrimeFactor(num) {
        this.num = num;
        console.log("being init");
    }
    PrimeFactor.prototype.factorize = function () {
        var i = 2;
        this.result = [];
        var num = this.num;
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
    };
    return PrimeFactor;
}());
// test
var num = 9102;
var primeFactor = new PrimeFactor(num);
primeFactor.factorize();
console.log(primeFactor.result.join(" * "));
