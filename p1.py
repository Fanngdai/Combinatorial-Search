def getValue(x, y, table):
    if x<0:
        return y
    if y<0:
        return x
    return table[x][y]

def editDistance(str1, str2):
    len1 = len(str1)
    len2 = len(str2)
    rtn = 0

    table = [[0 for x in range(len2)] for y in range(len1)]

    for row in range(len1):
        for col in range(len2):
            if row == 0 and str1[row] == str2[col]:
                value = getValue(row, col-1, table)
            elif col == 0 and str1[row] == str2[col]:
                value = getValue(row-1, col, table)
            elif row == 0:
                value = getValue(row, col-1, table) + 1
            elif col == 0:
                value = getValue(row-1, col, table) + 1
            elif str1[row] == str2[col]:
                value = getValue(row-1, col-1, table)
            else:
                left = getValue(row-1, col, table)
                up = getValue(row, col-1, table)
                diag = getValue(row-1, col-1, table)
                value = min(left, up, diag) + 1
            table[row][col] = value
            rtn = max(value, rtn)

    return table[len1-1][len2-1]

# 12 14 6
str1 = "watch the movie raising arizona?"
str2 = "watch da mets raze arizona?"
print(editDistance(str1, str2))

str1 = "this is what happens when I type slow"
str2 = "htishisth whaty havpens when ui type fasht"
print(editDistance(str1, str2))

str1 = "leonard skiena"
str2 = "lynard skynard"
print(editDistance(str1, str2))
