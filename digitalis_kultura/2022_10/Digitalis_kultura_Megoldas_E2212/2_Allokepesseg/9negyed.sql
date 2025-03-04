SELECT megye.nev AS Megyenév, sum(aerob.letszam)/megye.letszam AS Arány
FROM megye, aerob, allapot  
WHERE mkod=megye.kod AND allkod=allapot.kod
AND allapot.nev LIKE "%fejlesztés%"
GROUP BY mkod
HAVING Arány>0.25;
