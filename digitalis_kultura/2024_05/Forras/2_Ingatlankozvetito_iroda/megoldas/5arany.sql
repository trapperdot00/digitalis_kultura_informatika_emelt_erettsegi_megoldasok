SELECT MAX(hirdetes.ar) / MIN(hirdetes.ar) as arany
FROM hirdetes
WHERE hirdetes.allapot = "meghirdetve"
