SELECT aerob.letszam
FROM aerob, megye, allapot
WHERE mkod=megye.kod AND allkod=allapot.kod 
  AND megye.nev="Zala" AND nem=1 
  AND allapot.nev="egészséges";
  