function moveZeroes(nums) {
  let insertPos = 0;

  for (const num of nums) {
    if (num !== 0) {
      nums[insertPos] = num;
      insertPos++;
    }
  }

  while (insertPos < nums.length) {
    nums[insertPos] = 0;
    insertPos++;
  }

  return nums;
}

const arr = [0, 1, 0, 3, 12];
console.log(moveZeroes(arr)); // [1, 3, 12, 0, 0]
