SELECT IF(jatekos.neme=0,"no","ferfi") AS "nem",
	   COUNT(*) AS "darab"
FROM jatekos
GROUP BY jatekos.neme
