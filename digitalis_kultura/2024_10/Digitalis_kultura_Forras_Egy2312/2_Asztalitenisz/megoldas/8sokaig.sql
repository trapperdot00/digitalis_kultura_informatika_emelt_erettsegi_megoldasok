SELECT jatekos.nev, MAX(bajnok.ev) - MIN(bajnok.ev) AS "eltelt evek"
FROM jatekos, bajnok
WHERE jatekos.id = bajnok.jatekos_id
GROUP BY jatekos.id
HAVING MAX(bajnok.ev) - MIN(bajnok.ev) > 9
ORDER BY 2 DESC
