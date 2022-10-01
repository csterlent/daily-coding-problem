import sys


def ipify(string, n=3):
    if n == 0:
        # Check if string is a valid IP segment
        # If so, return [string] instead of []
        if len(string) == 0:
            return []
        if string[0] == '0' and len(string) > 1:
            return []
        if int(string) < 256:
            return [string]
        return []

    # check for valid IP segments in the first few
    # characters of string, and recurse to find the
    # solutions that start with those characters.
    out = []
    sub = ''
    for i, char in enumerate(string):
        sub += char
        if int(sub) < 256:
            for suffix in ipify(string[i+1:], n-1):
                out.append(sub+'.'+suffix)
        else:
            break
        if sub == '0':
            break
    return out


for sol in ipify(sys.argv[1]):
    print(sol)
