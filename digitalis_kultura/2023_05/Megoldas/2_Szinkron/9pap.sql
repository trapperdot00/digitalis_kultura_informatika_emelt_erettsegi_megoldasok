SELECT MAS.hang, film.cim
FROM szinkron AS PK, szinkron AS MAS, film
WHERE PK.filmaz=MAS.filmaz AND PK.filmaz=film.filmaz
	AND PK.hang="Pap Kati"
	AND MAS.hang<>"Pap Kati"
ORDER BY film.cim, MAS.hang;