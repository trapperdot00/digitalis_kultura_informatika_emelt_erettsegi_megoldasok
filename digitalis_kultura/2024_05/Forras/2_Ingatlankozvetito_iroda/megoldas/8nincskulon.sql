SELECT kozterulet, hazszam
FROM ingatlan
WHERE id NOT IN (
		SELECT ingatlanid
		FROM helyiseg
		WHERE funkcio = "konyha"
	)
	AND id NOT IN (
		SELECT ingatlanid
		FROM helyiseg
		WHERE funkcio = "WC"
	);
