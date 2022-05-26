// 1. 去掉数组里的多余重复项，保证成员唯一
function unique (arr) {
  const result = arr.filter((item, index) => {
    return arr.indexOf(item) === index
  })
  return result
}
const arr1 = [1, 2, 2, 3, 5, 3, 3, 4]
console.log('unique:', unique(arr1))

// 2. 获取数组里的重复项
function getDuplicates (arr) {
  const result = []
  arr.filter((item, index) => {
    if (arr.indexOf(item) !== index &&
      result.indexOf(item) === -1) {
      result.push(item)
    }
  })
  return result
}
const arr2 = [1, 2, 2, 3, 5, 3, 3, 4]
console.log('getDuplicates:', getDuplicates(arr2))

// 3. 删除数组里全部的重复项
function removeDuplicates (arr) {
  const result = arr.filter((item, index) => {
    if (arr.indexOf(item) === index) {
      return arr.indexOf(item, index + 1) === -1
    }
  })
  return result
}
const arr3 = [1, 2, 2, 3, 5, 3, 3, 4]
console.log('removeDuplicates:', removeDuplicates(arr3))
