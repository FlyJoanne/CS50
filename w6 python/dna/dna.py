import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Missing command-line argument")
        sys.exit(1)

    # TODO: Read database file into a variable
    with open(sys.argv[1]) as file1:
        reader = csv.DictReader(file1)
        data = list(reader)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file2:
        dna = file2.read()

    # TODO: Find longest match of each STR in DNA sequence
    STR = list(data[0].keys())  # 获取STR 比如small.csv的AGATC,AATG,TATC
    STR.remove("name")
    STRlm = []  # 把每个STR对应的最大连续循环次数存入一个list里
    for i in STR:
        STRlm.append(longest_match(dna, i))

    # TODO: Check database for matching profiles
    for i in range(len(data)):  # 对每个人
        match = True
        for j in range(len(STR)):  # 对每一个具体的STR
            if int(data[i][STR[j]]) != STRlm[j]:  # csv.DictReader读取CSV文件并将值存储为字符串,
                match = False  # 所以左边要转化为整数
                break
        if match:  # 只有在STR全匹配上时
            print(data[i]["name"])
            return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
