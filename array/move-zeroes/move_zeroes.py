def move_zeroes(nums):
    insert_pos = 0
    for num in nums:
        if num != 0:
            nums[insert_pos] = num
            insert_pos += 1

    while insert_pos < len(nums):
        nums[insert_pos] = 0
        insert_pos += 1


if __name__ == '__main__':
    arr = [0, 1, 0, 3, 12]
    move_zeroes(arr)
    print(arr)  # [1, 3, 12, 0, 0]
