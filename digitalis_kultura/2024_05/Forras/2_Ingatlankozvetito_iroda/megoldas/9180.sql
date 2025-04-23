SELECT
	ingatlan.kozterulet, ingatlan.hazszam,
	SUM(helyiseg.hossz * helyiseg.szel / IF(helyiseg.funkcio = "terasz", 2, 1)) AS terulet
FROM ingatlan, helyiseg
WHERE ingatlan.id = helyiseg.ingatlanid
GROUP BY ingatlan.id
HAVING terulet > 180
