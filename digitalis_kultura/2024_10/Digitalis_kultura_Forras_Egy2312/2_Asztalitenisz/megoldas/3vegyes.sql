SELECT bajnok.ev
FROM bajnok, versenyszam
WHERE bajnok.vsz_id = versenyszam.id
	AND versenyszam.nev = "vegyes páros"
ORDER BY 1 ASC
LIMIT 1
