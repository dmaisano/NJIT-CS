def twoSum(nums: "List[int]", target: "int") -> "List[int]":
    for i in range(len(nums)):
        for j in range(len(nums)):
            if j == i:
                continue

            if nums[j] == target - nums[i]:
                return [i, j]

