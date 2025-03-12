def isPrime(number: int):
    if number < 2:
        return False
    if number == 2 or number == 3:
        return True
    if number % 2 == 0 or number % 3 == 0:  # 排除偶数和 3 的倍数
        return False
    # 从 5 到 sqrt(n)，步长 6
    for i in range(5, int(number**0.5) + 1, 6):
        if number % i == 0 or number % (i + 2) == 0:  # 是否整除
            return False
    return True

def isPrime2(number: int):
    if number < 2:
        return False
    for i in range(2, number//2 + 1): # 从 2 到 n/2
        if number % i == 0:
            return False    # 是否整除
    return True

if __name__ == "__main__":
    for i in range(100):
        if isPrime2(i):
            print(i, end=" ")  # True
