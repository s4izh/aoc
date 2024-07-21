import sys

def check_and_replace(m, i, j, k, l):
    num_str = []
    sum = 0

    while j >= 0:
        if m[i + k][j + l] >= '0' and m[i + k][j + l] <= '9':
            j -= 1
        else:
            j += 1
            break

    while j < len(m[0]):
        if i + k < len(m) and j + l < len(m[0]):
            if m[i + k][j + l] >= '0' and m[i + k][j + l] <= '9':
                num_str.append(m[i + k][j + l])
                m[i + k][j + l] = '.'
                j += 1
            else:
                break
        else:
            break

    sum = int(''.join(num_str))

    return m, sum

def main():
    m = [list(line.rstrip()) for line in sys.stdin]
    # for fila in m:
    #     print(fila)

    total = 0

    for i in range(len(m)):
        for j in range(len(m[0])):
            if (m[i][j] < '0' or m[i][j] > '9') and m[i][j] != '.':
                for k in range(-1, 2):
                    for l in range(-1, 2):
                        if m[i + k][j + l] >= '0' and m[i + k][j + l] <= '9':
                            m, sum = check_and_replace(m, i, j, k, l)
                            total += sum

    print(total)

if __name__ == "__main__":
    main()
