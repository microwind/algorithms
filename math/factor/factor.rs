
fn factorize(mut num: i32) -> Vec<i32> {
  let mut i = 2;
  let mut v: Vec<i32> = Vec::new();
  while i * i <= num {
    while num % i == 0 {
      println!("{:}", i);
      num = num / i;
      v.push(i);
    }
    i += 1;
  }
  if num > 1 {
    println!("{:}", num);
    v.push(num);
  }
  return v;
}

fn main() {
  println!("factorize:");
  let mut num = 20;
  println!("number is: {:}", num);
  let v: Vec<i32> = factorize(num);
  println!("{:?}", v);

  num = 140;
  println!("number is: {:}", num);
  let v: Vec<i32> = factorize(num);
  println!("{:?}", v);

  num = 120;
  println!("number is: {:}", num);
  let arr = factorize(num);
  println!("{:?}", arr);
}

/*
jarry@jarrys-MacBook-Pro rust % rustc -V  
rustc 1.51.0 (2fd73fabe)
jarry@jarrys-MacBook-Pro factor % rustc factor.rs
jarry@jarrys-MacBook-Pro factor % ./factor       
factorize:
number is: 20
2
2
5
[2, 2, 5]
number is: 140
2
2
5
7
[2, 2, 5, 7]
number is: 120
2
2
2
3
5
[2, 2, 2, 3, 5]
*/