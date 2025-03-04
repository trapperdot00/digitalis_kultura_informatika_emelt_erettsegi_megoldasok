bemenet = open("taborok.txt")
táborok = []
for sor in bemenet:
    adatsor = sor.strip().split()
    for i in range(4):
        adatsor[i] = int(adatsor[i])
    táborok.append(adatsor)
bemenet.close()

print("2. feladat")
print(F"Az adatsorok száma: {len(táborok)}")
print(f"Az először rögzített tábor témája: {táborok[0][-1]}")
print(f"Az utoljára rögzített tábor témája: {táborok[-1][-1]}")

print("3. feladat")
nincs_ilyen = True
for tábor in táborok:
    if tábor[-1] == "zenei":
        nincs_ilyen = False
        print(f"Zenei tábor kezdődik {tábor[0]}. hó {tábor[1]}. napján.")
if nincs_ilyen:
    print("Nem volt zenei tábor.")

print("4. feladat")
maxlétszám = 0
for tábor in táborok:
    maxlétszám = max(maxlétszám, len(tábor[-2]))
print("Legnépszerűbbek:")
for tábor in táborok:
    if len(tábor[-2]) == maxlétszám:
        print(tábor[0],tábor[1],tábor[-1])

def sorszam(hó, nap):
    if hó == 6:
        return nap-15
    if hó == 7:
        return nap+15
    if hó == 8:
        return nap+46

print("6. feladat")
h = int(input("hó: "))
n = int(input("nap: "))
db = 0
for tábor in táborok:
    if sorszam(tábor[0], tábor[1]) <= sorszam(h, n) <= sorszam(tábor[2], tábor[3]):
        db += 1
print(f"Ekkor éppen {db} tábor tart.")

print("7. feladat")
tanuló = input("Adja meg egy tanuló betűjelét: ")
egytanuló = []
for tábor in táborok:
    if tanuló in tábor[-2]:
        egytanuló.append(tábor)
for i in range(len(egytanuló)-1):
    for j in range(len(egytanuló)-1):
        if sorszam(egytanuló[j][0], egytanuló[j][1]) > sorszam(egytanuló[j+1][0], egytanuló[j+1][1]):
            segéd = egytanuló[j]
            egytanuló[j] = egytanuló[j+1]
            egytanuló[j+1] = segéd
kimenet = open("egytanulo.txt", "w")
for tábor in egytanuló:
    print(f"{tábor[0]}.{tábor[1]}-{tábor[2]}.{tábor[3]}. {tábor[-1]}", file=kimenet)
kimenet.close()
mind = True
for i in range(len(egytanuló)-1):
    if sorszam(egytanuló[i][2], egytanuló[i][3]) >= sorszam(egytanuló[i+1][0], egytanuló[i+1][1]):
        mind = False
if mind:
    print("Mindegyik táborban részt vehet.")
else:
    print("Nem mehet el mindegyik táborba.")
