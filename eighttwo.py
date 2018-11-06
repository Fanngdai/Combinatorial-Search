def isShuffle(x, y, z):
    prevLoc = 0
    remainder = ""
    for a in x:
        # Get the index which this char first shows up
        loc = z.index(a)
        remainder += z[prevLoc:loc]
        z = z[loc+1:]
        prevLoc = loc

    if z!="":
        remainder = remainder + z[prevLoc]
    print(remainder == y)

isShuffle("chocolate", "chips", "cchocohilaptes")
isShuffle("chocolate", "chips", "chocochilatspe")
