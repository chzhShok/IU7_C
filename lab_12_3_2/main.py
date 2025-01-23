from ctypes import CDLL
from ctypes import POINTER, c_int

import os

lib_path = os.path.join('out', 'libmylib.so')
mylib = CDLL(lib_path)

_fill_prime_numbers = mylib.fill_prime_numbers
_fill_prime_numbers.argtypes = (POINTER(c_int), c_int)
_fill_prime_numbers.restype = c_int

_insert_after_even = mylib.insert_after_even
_insert_after_even.argtypes = (POINTER(c_int), c_int, POINTER(c_int), c_int)
_insert_after_even.restype = c_int


def fill_prime_numbers(n: int) -> list[int]:
    arr = (c_int * n)()

    rc = _fill_prime_numbers(arr, n)
    if (rc != 0):
        raise ValueError("Введенный размер массива некорректен")

    return list(arr)


def insert_after_even(arr: list[int], k: int) -> list[int]:
    src_len = len(arr)
    src = (c_int * src_len)(*arr)

    dst_len = _insert_after_even(src, src_len, None, k)
    if (dst_len == -1):
        raise ValueError("Введенный размер массива некорректен")

    dst = (c_int * dst_len)()
    _insert_after_even(src, src_len, dst, k)

    return list(dst)

n = int(input("Введите количество элементов в массиве простых чисел: "))
prime_arr = fill_prime_numbers(n)
print(f"Массив простых чисел: {prime_arr}")

print("Введите массив, в который будет вставляться число: ")
arr = list(map(int, input().split()))
k = int(input("Введите число, которое будет вставляться: "))
dst_arr = insert_after_even(arr, k)
print(f"Результирующий массив: {dst_arr}")
