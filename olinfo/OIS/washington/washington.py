def sus(S, U, s):
    if S == "NE": return ord(U) - ord('A'), int(s)
    if S == "NW": return ord('A') - ord(U), int(s)
    if S == "SE": return ord(U) - ord('A'), -((26 - int(s)) % 26)
    if S == "SW": return ord('A') - ord(U), -((26 - int(s)) % 26)

T = int(input())
for _ in range(T):
    sus1, sus2, sus3, sus4, sus5, sus6 = input().split()
    SUS1 = sus(sus1,sus2,sus3)
    SUS2 = sus(sus4,sus5,sus6)
    print(abs(SUS1[0]-SUS2[0])+abs(SUS1[1]-SUS2[1]))