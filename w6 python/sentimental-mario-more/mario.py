def main():
    height = get_height()
    for i in range(height):
        for n in range(height - i - 1):
            print(" ", end="")
        for n in range(i + 1):
            print("#", end="")
        for n in range(2):
            print(" ", end="")
        for n in range(i + 1):
            print("#", end="")
        print()


def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0 and n < 9:
                return n
        except ValueError:
            print("Not an integer")


main()
