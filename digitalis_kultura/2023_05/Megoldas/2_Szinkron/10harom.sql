SELECT szinesz, hang, count(szinkid) AS FilmDB
FROM szinkron
GROUP BY szinesz, hang
HAVING count(szinkid) >= 3
ORDER BY FilmDB DESC;