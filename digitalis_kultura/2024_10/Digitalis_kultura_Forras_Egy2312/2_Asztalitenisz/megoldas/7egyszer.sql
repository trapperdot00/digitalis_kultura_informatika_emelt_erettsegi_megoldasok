SELECT jatekos.nev, bajnok.ev, versenyszam.nev
FROM jatekos, bajnok, versenyszam
WHERE jatekos.id = bajnok.jatekos_id
	AND bajnok.vsz_id = versenyszam.id
GROUP BY jatekos.id
HAVING COUNT(jatekos.id) = 1
