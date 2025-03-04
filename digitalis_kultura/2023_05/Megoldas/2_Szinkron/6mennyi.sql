SELECT eredeti, cim, count(szinkid) 
FROM szinkron, film
WHERE film.filmaz=szinkron.filmaz
GROUP BY eredeti;
