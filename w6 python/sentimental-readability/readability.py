from cs50 import get_string


def main():
    para = get_string("Text: ")
    L = count_letters(para) / count_words(para) * 100.00
    S = count_sentence(para) / count_words(para) * 100.00
    index = round(0.0588 * L - 0.296 * S - 15.8)
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    l = 0
    for char in text:
        if char.isalpha():
            l += 1
    return l


def count_words(text):
    w = 0
    for char in text:
        if char.isspace():
            w += 1
    return w + 1


def count_sentence(text):
    s = 0
    for char in text:
        if char == "." or char == "?" or char == "!":
            s += 1
    return s


main()
