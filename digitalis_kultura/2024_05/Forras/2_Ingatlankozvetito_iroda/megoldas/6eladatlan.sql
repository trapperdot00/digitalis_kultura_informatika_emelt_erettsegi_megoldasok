SELECT ingatlan.kozterulet, ingatlan.hazszam, hirdetes.datum
FROM hirdetes, ingatlan
WHERE hirdetes.ingatlanid = ingatlan.id
GROUP BY ingatlan.id
HAVING COUNT(ingatlan.id) = 1
ORDER BY 3 ASC
LIMIT 1
