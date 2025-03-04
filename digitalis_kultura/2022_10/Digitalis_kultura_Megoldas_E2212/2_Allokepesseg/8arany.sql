SELECT megye.nev, SUM(aerob.letszam)/megye.letszam
FROM megye, aerob
WHERE mkod=megye.kod
GROUP BY megye.nev
ORDER BY 2 DESC
LIMIT 1;