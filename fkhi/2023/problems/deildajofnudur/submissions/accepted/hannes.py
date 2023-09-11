from collections import defaultdict

n = int(input())
grants = input()

scores = {}

for start in range(len(grants)):
    for end in range(start, len(grants)):
        tally = 0
        substring_char_count = defaultdict(int)
        # ensure string contains equal number of digits
        for i in range(start, end+1):
            substring_char_count[grants[i]] += 1
            tally += 1
        # if the char counts are the same
        if len(set(substring_char_count.values())) == 1:
            scores[(start, end)] = tally

print(max(scores.values()))
