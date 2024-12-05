import re

def file_to_str(filename):
    with open(filename) as file:
        return file.read()

def part1(input):
    # suma = 0
    # for line in input.split("\n"):
    #     if line:
    #         suma += sum([int(x) * int(y) for x, y in re.findall("mul\((\d+),(\d+)\)", line)])

    return sum([int(x) * int(y) for line in input.split("\n") if line for x, y in re.findall("mul\((\d+),(\d+)\)", line)])

def part2(input):
    enable_mul = True
    suma = 0
    for line in input.split("\n"):
        if line:
            for token1 in re.split(r"(?=do\(\))", line):
                for token2  in re.split(r"(?=don't\(\))", token1):
                    if token2.startswith("don't()"):
                        enable_mul = False
                    elif token2.startswith("do()"):
                        print(token2)
                        suma += sum([int(x) * int(y) for x, y in re.findall("mul\((\d+),(\d+)\)", token2)])
                        enable_mul = True
                    elif enable_mul:
                        print(token2)
                        valor = sum([int(x) * int(y) for x, y in re.findall("mul\((\d+),(\d+)\)", token2)])
                        print("valor: ", valor)
                        suma +=  valor
    return suma


print(part1(file_to_str("input/input1_mini.txt")))
print(part1(file_to_str("input/input1_full.txt")))

print(part2(file_to_str("input/input1_mini.txt")))
print(part2(file_to_str("input/input1_full.txt")))
