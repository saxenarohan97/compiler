import first


def isNonTerminal(x):
    return x[0].islower()


def isTerminal(x):
    return not(isNonTerminal(x))


def follow(x):

    follow_set = set()

    relevantRules = []

    for rule in first.rules:

        if x in rule.split(' ')[2:]:
            relevantRules.append(rule)

    for rule in relevantRules:

        temp = rule.split(' ')

        i = temp[2:].index(x) + 2

        flag = False

        while (i + 1) < len(temp):

            i += 1

            first_temp = first.first(temp[i])

            follow_set = follow_set.union(first_temp)

            if 'EPSILON' not in first_temp:
                flag = True
                break

        if(not(flag)):

            if(temp[0] != x):
                follow_set = follow_set.union(follow(temp[0]))

    if 'EPSILON' in follow_set:
        follow_set.remove('EPSILON')

    return follow_set


for n in first.nonTerms:

    print(n, "->", end=' ')

    for f in follow(n):

        print(f, end=' ')

    print()
