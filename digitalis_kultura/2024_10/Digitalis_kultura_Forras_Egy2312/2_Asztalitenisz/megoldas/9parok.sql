SELECT DISTINCT jatekos.nev
FROM jatekos, bajnok, versenyszam
WHERE jatekos.id = bajnok.jatekos_id
	AND bajnok.vsz_id = versenyszam.id
	AND bajnok.ev IN (
		SELECT bajnok.ev
		FROM jatekos, bajnok, versenyszam
		WHERE jatekos.id = bajnok.jatekos_id
			AND bajnok.vsz_id = versenyszam.id
			AND jatekos.nev = "Pergel Szandra"
			AND versenyszam.nev = "vegyes páros"
	)
	AND versenyszam.nev = "vegyes páros"
	AND jatekos.nev != "Pergel Szandra"
ORDER BY bajnok.ev ASC
