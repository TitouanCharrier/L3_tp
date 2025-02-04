
-- Question 1 -------------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION inactive_func(Bib in char)  
RETURN number 
IS
  a number;
  b number;
BEGIN
  SELECT count(codPers) 
    into a
    from personnes  
    where (SYSDATE - dateDerPret) > 365 
    and codBib = Bib;

  SELECT count(codPers) 
    into b
    from personnes
    where codBib = Bib;
  

  RETURN ((a/b)*100);

  EXCEPTION when ZERO_DIVIDE then RETURN -2;
END inactive_func;
/


DECLARE
  v_resultat number;
BEGIN
  v_resultat := inactive_func('MTLO');
  DBMS_OUTPUT.PUT_LINE('la réponse est : ' || v_resultat || '%');
END;
/

-- Question 2 -------------------------------------------------------------------------------------

CREATE OR REPLACE PROCEDURE displayInfo(EX in char)  
IS
  r personnes%rowtype;
BEGIN
  SELECT personnes.* 
    into r
    from personnes, pret
    where pret.codEx = EX
    and personnes.codPers = pret.codPers;
  
 DBMS_OUTPUT.PUT_LINE(r.nomPers || ' ' || r.prenomPers);

END displayInfo;
/

DECLARE
BEGIN
  displayInfo('08S03');
END;

-- Question 3 -------------------------------------------------------------------------------------

CREATE OR REPLACE PROCEDURE glob_inactive_func 
IS

  CURSOR WAIIII IS
    SELECT codBib
    FROM Bibliotheque;

  res number;

BEGIN
  
  for tmpbib in WAIIII LOOP
    
    res := inactive_func(tmpbib.codBib);

    DBMS_OUTPUT.PUT_LINE('pour la Bibliotheques : ' || tmpbib.codBib || ' : ' || res || ' %');

  END LOOP;
 
END glob_inactive_func;
/

DECLARE
BEGIN
  glob_inactive_func;
END;
/

-- Question 4 -------------------------------------------------------------------------------------

CREATE or REPLACE PROCEDURE find_motcles(m in char)
IS 
res number;
BEGIN

  select count(traite.codOuv)
    into res
    from traite, motscles
    where traite.codmot = motscles.codmot
    and motscles.libellemot = m;

  DBMS_OUTPUT.PUT_LINE('le nombre d ouvrages pour "' || m || '" est : ' || res);

END find_motcles;
/

DECLARE
BEGIN
  find_motcles('coucou');
END;
/















