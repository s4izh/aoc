def part1(input):
    l1 = [e.split()[0] for e in [l for l in input.split("\n")] if e]
    l2 = [e.split()[1] for e in [l for l in input.split("\n")] if e]
    l1.sort()
    l2.sort()
    return sum([abs(int(x) - int(y)) for x,y in list(zip(l1,l2))])

def part2(input):
    l1 = [e.split()[0] for e in [l for l in input.split("\n")] if e]
    l2 = [e.split()[1] for e in [l for l in input.split("\n")] if e]

    sum = 0
    for i in l1:
        partial = 0
        for j in l2:
            if i == j:
                partial += int(i)
        sum += partial

    return sum

with open("input/mini1_input.txt", "r+") as file:
    input1_mini = file.read()

with open("input/part1_input.txt", "r+") as file:
    input1 = file.read()

print(part1(input1_mini))
print(part1(input1))

with open("input/mini2_input.txt", "r+") as file:
    input2_mini = file.read()

with open("input/part2_input.txt", "r+") as file:
    input2 = file.read()

print(part2(input2_mini))
print(part2(input2))



