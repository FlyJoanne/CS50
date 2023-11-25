# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run 要运行1000次模拟
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    filename = sys.argv[1]
    with open(filename) as file:
        reader = csv.DictReader(file)
        for team in reader:
            team["rating"] = int(team["rating"])
            teams.append(team)
    # 默认情况下，从文件读取的所有值都是字符串。
    # 因此，请务必首先将 team 转换rating为 an int
    # TODO: Read teams into memory from file

    counts = {}
    for i in range(N):
            winner = simulate_tournament(teams)
            if winner in counts:
                counts[winner] += 1
            else:
                counts[winner] = 1
    # counts[team_name] = x
    # if "Portugal" in counts:
    # 字典，队名-模拟赛中赢的次数eg.{"Uruguay": 2, "Portugal": 3}
    # TODO: Simulate N tournaments and keep track of win counts

    # Print each team's chances of winning, according to simulation 降序
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability
    # Python's random.random() function generates a random float number between 0.0 and 1.0.
    # The expression random.random() < probability will return a boolean value, either True or False.
    # If the randomly generated number is less than the specified probability, it will return True, otherwise it will return False.


def simulate_round(teams): # teams是list of teams
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2): # For example, if teams has 6 elements, i would take on the values 0, 2, and 4
        if simulate_game(teams[i], teams[i + 1]): # team 0 和 team 1。 team 0赢了的话
            winners.append(teams[i])              # team 0 进 赢家list
        else:
            winners.append(teams[i + 1])          #否则team 1 进赢家list

    return winners


def simulate_tournament(teams):
    if len(teams) == 2:
        return simulate_round(teams)[0]["team"]
    else:
        return simulate_tournament(simulate_round(teams))
    # 可以调用simulate_round函数，
    # 可以用len()确定列表里几个元素
    #可以假设参加锦标赛的球队数量是2的幂
    """Simulate a tournament. Return name of the final winning team."""
    # TODO


if __name__ == "__main__":
    main()
# This IF line checks if the script is being run directly or it's being imported as a module.
# When a Python file is run directly, the special variable __name__ is set to "__main__".
# So, if __name__ == "__main__": is checking if this file is the main program.If it is, then it calls the main() function.

# If this file is being imported from another script, this check prevents main() from being run automatically.
# This allows the file to be used as a module, providing its functions and classes for use in other scripts,
# without executing the main() function immediately upon import.
