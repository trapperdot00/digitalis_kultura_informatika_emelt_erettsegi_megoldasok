SELECT sum(aerob.letszam)/megye.letszam
FROM aerob,megye
WHERE mkod=kod AND megye.nev="Pest";