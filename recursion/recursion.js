function factorial(x) {
  console.log('x=', x)
  if (x < 1) return
  if (x === 1) return
  return x * factorial(x - 1)
}


function factorial(x) {
  console.log('x=', x)
  if (x <= 1) return x
  return x * factorial(x - 1)
}

console.log('factorial(5)', factorial(5))


/**
   f(5)
  /   \
5 * f(5 - 1)
      /    \
    4 * f(4 - 1)
         /    \
       3 * f(3 - 1)
            /   \
          2 * f(2 - 1)
               /    \
             1 * f(1 - 1)

jarrys-MacBook-Pro:recursion jarry$ node recursion.js 
x= 5
x= 4
x= 3
x= 2
x= 1
x= 0
factorial(5) 120
 */

function recursion(n) {
  console.log('begin: n=', n);
  if (n >= 15) return n
  n *= 3
  return recursion(n + 1) + recursion(n * 2)
}

console.log('recursion(1)=', recursion(1))

/**

                               f(1)
                      /                  \
                f(3 + 1)      +        f(3 * 2)
               /      \                 /         \
        f(12 + 1)  + f(12 * 2)     f(18 + 1)  + f(18 * 2)
        /      \        24             19           36
  f(39 + 1) + f(39 * 2)
      40    +    78

      total = 40 + 78 + 24 + 19 + 36 = 197

// output 

begin: n= 1
begin: n= 4
begin: n= 13
begin: n= 40
begin: n= 78
begin: n= 24
begin: n= 6
begin: n= 19
begin: n= 36
recursion(1)= 197
 */

function recursion2(n) {
  console.log('begin: n=', n);
  if (n >= 15) return n
  n *= 3
  return recursion2(n + 1) - recursion2(n * 2)
}

console.log('recursion2(1)=', recursion2(1))

/**

                               f(1)
                      /                  \
                f(3 + 1)      -        f(3 * 2)
               /      \                 /         \
        f(12 + 1)  - f(12 * 2)     f(18 + 1)  - f(18 * 2)
        /      \        24             19           36
  f(39 + 1) - f(39 * 2)
      40    -    78

      total = (40 - 78) - (24) - (19 - 36) = -45

// output 
begin: n= 1
begin: n= 4
begin: n= 13
begin: n= 40
begin: n= 78
begin: n= 24
begin: n= 6
begin: n= 19
begin: n= 36
recursion2(1)= -45
 */