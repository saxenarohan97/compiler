def isNonTerminal(x):
    return x[0].islower()


def isTerminal(x):
    return not(isNonTerminal(x))


rules = []

with open('./code/grammar', 'r') as file:
    rules = file.readlines()

rules = [x[:-1] for x in rules if x != '\n']

nonTerms = set()

for rule in rules:

    nonTerms.add(rule.split(' ')[0])

############################################################


def first(x):

    if isTerminal(x):
        return set([x])

    # x is a non terminal

    first_set = set()

    relevantRules = []

    for rule in rules:

        if rule.split(' ')[0] == x:
            relevantRules.append(rule)

    for rule in relevantRules:

        i = 2

        temp = rule.split(' ')[i]
        temp = first(temp)

        first_set = first_set.union(temp)

        while 'EPSILON' in temp and i + 1 < len(rule.split(' ')):

            i += 1

            temp = rule.split(' ')[i]
            temp = first(temp)

            first_set = first_set.union(temp)

    return first_set


# for n in nonTerms:
#     print(n, "->", end=' ')
#
#     for f in first(n):
#
#         print(f, end=' ')
#
#     print()
