from cs50 import get_float


def main():
    while True:
        owed = get_float("Change owed: ")
        if owed > 0:
            print(coins(round(owed * 100)))
            break


# 有Floating-point precision issues所以要round
# 比如0.1 + 0.2 = 0.30000004


def coins(money):
    quarters = int(money / 25)
    money = money - quarters * 25
    dimes = int(money / 10)
    money = money - dimes * 10
    nickels = int(money / 5)
    money = money - nickels * 5
    pennies = money
    return quarters + dimes + nickels + pennies


main()
