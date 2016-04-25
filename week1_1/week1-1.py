from math import ceil, floor


def real_val(n):
    real_amount = 0
    for s in range(2, n + 1):
        for j in range(1, (s - int((ceil(s / 2) + 1))) + 1):
            real_amount += s - 1 - 2 * j
    return real_amount


def floor_ceil_sum(n):
    direct = 2 * ((1/6) * (n/2 * (n/2+1) * (2*n/2 + 1))) - ((n/2 * (n/2 + 1) / 2))  
    # indirect = sum([(s * ceil(s / 2)) - pow(ceil(s / 2), 2) for s in range(2, n + 1)])
    return direct

def online_even(n):
    return n * (n - 2) * (2*n - 5) / 24

def online_odd(n):
    return (n - 1) * (n - 3) * (2*n - 1) / 24


def short_val(n):
    if n % 2 == 0:
        return floor_ceil_sum(n) - (pow(n, 2) - n) / 2
    else:
        number = floor_ceil_sum(n - 1) - (pow(n, 2) - n) / 2
        number += ceil(n / 2)**2 - ceil(n / 2)
        return number

def online(n):
    if n % 2 == 0:
        return online_even(n)
    else:
        return online_odd(n)


for num in range(100):
    assert(real_val(num) == online(num))
    # if num % 1000 == 0:
    #     print(num)
    print(int(short_val(num)))