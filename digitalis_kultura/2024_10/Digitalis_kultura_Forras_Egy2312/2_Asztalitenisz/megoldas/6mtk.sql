SELECT jatekos.nev
FROM jatekos, bajnok, egyesulet
WHERE jatekos.id = bajnok.jatekos_id
	AND bajnok.egyesulet_id = egyesulet.id
	AND egyesulet.nev = "MTK"
GROUP BY jatekos.id
ORDER BY jatekos.neme ASC, jatekos.nev ASC
