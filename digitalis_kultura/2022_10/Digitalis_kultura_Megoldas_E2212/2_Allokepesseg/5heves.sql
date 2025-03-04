SELECT count(nev) 
FROM megye
WHERE letszam<(SELECT letszam FROM megye WHERE nev="Heves");