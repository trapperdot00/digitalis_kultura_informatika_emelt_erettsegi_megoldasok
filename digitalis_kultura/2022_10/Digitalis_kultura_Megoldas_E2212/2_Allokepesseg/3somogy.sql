SELECT sum(aerob.letszam)
FROM aerob, megye
WHERE mkod=kod AND nev="Somogy";