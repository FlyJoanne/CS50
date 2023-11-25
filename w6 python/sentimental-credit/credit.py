from cs50 import get_string
import re


def main():
    while True:
        number = get_string("Number: ")
        if not re.fullmatch(r"\d{13}|\d{15}|\d{16}", number):
            print("INVALID")
        else:
            print(which(number))
        break


def which(number):
    size = 0
    checksum = 0
    first_digit = 0
    second_digit = 0
    remain_digits = int(number)

    while remain_digits > 0:
        digit = remain_digits % 10
        if size > 0:
            second_digit = first_digit
        first_digit = digit
        remain_digits = remain_digits // 10
        if size % 2 == 0:
            checksum += digit
        else:
            checksum += (digit * 2) % 10 + (digit * 2) // 10
        size += 1

    if checksum % 10 != 0:
        return "INVALID"
    if size == 15 and first_digit == 3 and (second_digit == 4 or second_digit == 7):
        return "AMEX"
    if size == 16 and first_digit == 5 and (second_digit <= 5 and second_digit >= 1):
        return "MASTERCARD"
    if (size == 13 or size == 16) and first_digit == 4:
        return "VISA"
    return "INVALID"


main()
