SELECT cim, eredeti, szerep, szinesz
FROM film, szinkron
WHERE film.filmaz=szinkron.filmaz
AND hang="Anger Zsolt";
