SELECT megye.nev, aerob.letszam
FROM aerob, megye, allapot
WHERE mkod=megye.kod AND nem=0 AND allkod=allapot.kod AND allapot.nev="egészséges"
ORDER BY 2 DESC;
