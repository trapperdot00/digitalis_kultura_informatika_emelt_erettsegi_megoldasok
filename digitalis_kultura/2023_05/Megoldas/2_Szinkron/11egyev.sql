SELECT MAFI.ev, MASZI.hang, MAFI.cim, NEMF.cim, MAFI.magyszov, NEMF.magyszov
FROM film MAFI, szinkron MASZI, film NEMF, szinkron NEMSZ
WHERE MAFI.filmaz=MASZI.filmaz AND NEMF.filmaz=NEMSZ.filmaz
AND MAFI.studio="Mafilm Audio Kft." 
AND NEMF.studio<>"Mafilm Audio Kft."
AND MAFI.ev=NEMF.ev AND MASZI.hang=NEMSZ.hang
ORDER by MASZI.hang;;
