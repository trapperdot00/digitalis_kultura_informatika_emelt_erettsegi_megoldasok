SELECT SUM(hirdetes.ar) * 0.015 AS dij
FROM hirdetes
WHERE YEAR(hirdetes.datum) = 2021
	AND hirdetes.allapot = "eladva"
