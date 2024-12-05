def part1(input):
    lines = input.split("\n")
    safe = 0
    for line in lines:
        if line:
            nums = [int(n) for n in line.split()]
            increasing = nums[0] < nums[1]

            for i in range(len(nums) - 1):
                if nums[i] == nums[i + 1]:
                    break
                if increasing != (nums[i] < nums[i + 1]):
                    break
                if abs(nums[i] - nums[i + 1]) > 3:
                    break
                if i == (len(nums) - 2):
                    safe += 1
    return safe

def nums_safe(nums, replaced=False):
    increasing = nums[0] < nums[1]
    for i in range(len(nums) - 1):
        if nums[i] == nums[i + 1] or increasing != (nums[i] < nums[i + 1]) or abs(nums[i] - nums[i + 1]) > 3:
            if not replaced:
                for j in range(len(nums)):
                    aux = nums.copy()
                    aux.pop(j)
                    if nums_safe(aux, True):
                        return True
            return False
        if i == (len(nums) - 2):
            return True
    return False

def part2(input):
    lines = input.split("\n")
    safe = 0
    for line in lines:
        if line:
            nums = [int(n) for n in line.split()]
            safe += nums_safe(nums)
    return safe

with open("input/input1_mini.txt", "r+") as file:
    input1_mini = file.read()

with open("input/input1_full.txt", "r+") as file:
    input1_full = file.read()

print(part1(input1_mini))
print(part1(input1_full))

print(part2(input1_mini))
print(part2(input1_full))
