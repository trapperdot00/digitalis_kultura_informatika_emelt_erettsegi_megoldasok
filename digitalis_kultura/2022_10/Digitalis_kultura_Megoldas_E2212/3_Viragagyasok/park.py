print("1. feladat")
bemenet = open("felajanlas.txt")
felajánlások = []
for sor in bemenet:
    adatsor = sor.strip().split()
    if (len(adatsor) == 3):
        felajánlások.append([ int(adatsor[0]), int(adatsor[1]), adatsor[2] ])
    else:
        hossz = int(adatsor[0])

print("2. feladat")
felajánlások_száma = len(felajánlások)
print(f"A felajánlások száma: {len(felajánlások)}")

print("3. feladat")
print("A bejárat mindkét oldalán ültetők:", end = " ")
for felajánlás_sorszáma in range(1, felajánlások_száma+1):
    if felajánlások[felajánlás_sorszáma-1][0] > felajánlások[felajánlás_sorszáma-1][1]:
        print(felajánlás_sorszáma, sep="", end=" ")
print()

print("4. feladat")
ágyás = int(input("Adja meg az ágyás sorszámát! "))
ültetés = []
for felajánlás in felajánlások:
    if felajánlás[0] <= ágyás <= felajánlás[1] \
            or felajánlás[0] > felajánlás[1] and (felajánlás[0] <= ágyás or felajánlás[1] >= ágyás):
        ültetés.append(felajánlás[2])
print(f"A felajánlók száma: {len(ültetés)}")
if len(ültetés) > 0:
    print(f"A virágágyás színe, ha csak az első ültet: {ültetés[0]}")
    színek_listája = " ".join(list(set(ültetés)))
    print(f"A virágágyás színei: {színek_listája}")
else:
    print("Ezt az ágyást nem ültetik be.")

print("5. feladat")
beültetve = set()
beültetett_hossz = 0
for felajánlás in felajánlások:
    if felajánlás[0] < felajánlás[1]:
        beültetett_hossz += felajánlás[1] - felajánlás[0] + 1
        for ágyás in range(felajánlás[0], felajánlás[1]+1):
            beültetve.add(ágyás)
    else:
        beültetett_hossz += hossz - felajánlás[0] + 1 + felajánlás[1]
        for ágyás in range(felajánlás[0], hossz+1):
            beültetve.add(ágyás)
        for ágyás in range(1, felajánlás[1]+1):
            beültetve.add(ágyás)
if len(beültetve) == hossz:
    print("Minden ágyás beültetésére van jelentkező.")
elif beültetett_hossz > hossz:
    print("Átszervezéssel megoldható a beültetés.")
else:
    print("A beültetés nem oldható meg.")

print("6. feladat")
végleges = []
for index in range(hossz):
    végleges.append(['#', 0])
sorszám = 0
for felajánlás in felajánlások:
    sorszám += 1
    for ágyás_sorszám in range(1, hossz+1):
        if felajánlás[0] <= ágyás_sorszám <= felajánlás[1] \
                or felajánlás[0] > felajánlás[1] and (felajánlás[0] <= ágyás_sorszám or felajánlás[1] >= ágyás_sorszám):
            if végleges[ágyás_sorszám-1][1] == 0:
                végleges[ágyás_sorszám-1][0] = felajánlás[2]
                végleges[ágyás_sorszám-1][1] = sorszám
kimenet = open("szinek.txt", "w")
for ágyás in végleges:
    print(ágyás[0], ágyás[1], file=kimenet)
kimenet.close()
