SELECT ingatlan.kozterulet, ingatlan.hazszam, eladva.ar
FROM ingatlan, hirdetes AS meghirdetve, hirdetes AS eladva
WHERE ingatlan.id = meghirdetve.ingatlanid
	AND ingatlan.id = eladva.ingatlanid
	AND meghirdetve.allapot = "meghirdetve"
	AND eladva.allapot = "eladva"
	AND meghirdetve.ar = eladva.ar
