// 递归分解数组，最小粒度为2个
let step = 0

function divide(arr) {
  // 如果数组剩余1个或0个则无法继续分解
  console.log('start:', arr)
  const len = arr.length
  if (len < 2) {
    return arr
  }
  const mid = Math.round(len / 2)
  let left = arr.slice(0, mid)
  let right = arr.slice(mid)
  left = divide(left)
  right = divide(right)
  step += 1
  console.log('after:', step + '->', arr, left, right)
  return left.concat(right)
}

divide([3, 1, 2, 5, 6, 4])

/**
           f([3, 1, 2, 5, 6, 4])
              /             \
          f([3, 1, 2])    f([5, 6, 4])
          /        \         /        \
      f([3, 1])   f([2])  f([5, 6]), f([4])
      /     \              /      \
  f([3])    f([1])      f([5]) f([6])