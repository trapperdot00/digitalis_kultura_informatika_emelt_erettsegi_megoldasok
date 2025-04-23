SELECT ingatlan.hazszam, hirdetes.ar
FROM hirdetes, ingatlan
WHERE hirdetes.ingatlanid = ingatlan.id
	AND hirdetes.allapot = "meghirdetve"
	AND kozterulet = "Agyagos utca"
