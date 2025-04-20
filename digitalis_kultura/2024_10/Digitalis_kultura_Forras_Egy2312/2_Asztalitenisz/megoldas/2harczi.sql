SELECT bajnok.ev, versenyszam.nev
FROM jatekos, bajnok, versenyszam
WHERE jatekos.id = bajnok.jatekos_id
	AND bajnok.vsz_id = versenyszam.id
	AND jatekos.nev = "Harczi Zsolt"
