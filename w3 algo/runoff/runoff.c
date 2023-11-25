#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i 偏好是二维array
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates 这里定下来有几个投票者，有几个候选人
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[]) // ./后面用户会输入候选人们的名字
{
    // Check for invalid usage 如果没有输入候选人那就报错1
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates 确定好候选人数量了，如果不大于一百人就ok
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) // 排好候选人的数列，给他们赋值也就是用户输入的名字，然后初始化设定：票数为0，还没淘汰
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: "); // 确定好投票者数量了，如果不大于9个人就OK
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes 要每一个投票者的选票
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank 要具体某个投票者的偏好排序
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1); // 第一次循环，rank1: 输入一个人名；第二次循环，rank2：输入第二个人名

            // Record vote, unless it's invalid 除非选票无效（函数vote返回false），否则记录选票，请看127行
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates 计票
        tabulate();

        // Check if election has been won 这个布林函数叫won，如果调用print_winner后返回true，那won也就是true，说明有人已经赢了
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();   // 找出现在最低有多少票
        bool tie = is_tie(min); // 判断是不是所有人都一样是最低票数

        // If tie, everyone wins 大家都一样烂，那就是都一样好
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes 大家并不一样烂所以要淘汰末位了
        eliminate(min);

        // Reset vote counts back to zero 每一个候选人票数都清零了
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid 除非选票无效（函数vote返回false），否则记录偏好。
bool vote(int voter, int rank, string name) // voter是当下投票者的编号，rank是当下这个投票者偏好的第某位
{
    for (int i = 0; i < candidate_count; i++) // 找遍候选人名单看有没这人
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i; // 记入偏好收集本
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++) // 每一个投票者
    {
        for (int j = 0; j < candidate_count; j++) // 具体某个投票者对所有候选人
        {
            if (!candidates[preferences[i][j]].eliminated) // 找出没被淘汰的候选人中排名最靠前的来计一票。
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        float decivote = candidates[i].votes;
        float half = (float) voter_count / 2;
        if (decivote > half)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = 100;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && (candidates[i].votes < min))
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min) // 其实也可以if找到起码一个票数不是min而且还活着的候选人然后就return false
{
    int alive = 0;
    int same = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated) // 找出有几个活着的候选人
        {
            alive++;
        }
        if (candidates[i].votes == min) // 找出候选人里同时有多少人是有min票的
        {
            same++;
        }
    }
    if (alive == same)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && !candidates[i].eliminated) // 找出票数最小的还活着的候选人
        {
            candidates[i].eliminated = true; // 淘汰ta
        }
    }
}
