SELECT egyesulet.orszag
FROM egyesulet, bajnok
WHERE egyesulet.id = bajnok.egyesulet_id
	AND bajnok.ev>2000
	AND egyesulet.orszag != "Magyarország"
GROUP BY egyesulet.orszag
