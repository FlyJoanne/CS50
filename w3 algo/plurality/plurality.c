#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates 最多能有9个候选人
#define MAX 9

// Candidates have name and vote count 定义一下数据类型：候选人
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates 定义一下候选人队伍
candidate candidates[MAX];

// Number of candidates 到底有几个候选人？36行告诉你
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage 如果除了./p没输入别的就报错
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1; // 总算知道了，用户输几个人名就几个候选人
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) // 既然你输入了人名，那我就排到队伍里
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: "); // 问用户要投票者个数

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: "); // 分别问投票者你投谁！

        // Check for invalid vote // 没这人那就是无效投票
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++; // 名字对了就要计票！
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max)
        {
            max = candidates[i].votes;
        }
    }

    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == max)
        {
            printf("%s\n", candidates[j].name);
        }
    }
}