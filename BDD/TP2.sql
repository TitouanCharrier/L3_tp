
delete from pret 
where codex = '08s55';

create or replace trigger insert_rev_ouv
  before insert on revues
  for each row 
  begin
    insert into ouvrages (codOuv, titOuv, langue) 
    values (:new.codOuv, :new.titOuv, :new.langue);
  end;
/

create or replace trigger insert_liv_ouv
  before insert on livres
  for each row 
  begin
    insert into ouvrages (codOuv, titOuv, langue) 
    values (:new.codOuv, :new.titOuv, :new.langue);
  end;
/

insert into livres values ('CA12', 'CA', 'Français');
  
create or replace trigger delete_liv_ouv
  after delete on livres
  for each row 
  begin
    delete from ouvrages
    where codOuv = :old.codOuv;
  end;
/

create or replace trigger delete_rev_ouv
  after delete on revues
  for each row 
  begin
    delete from ouvrages
    where codOuv = :old.codOuv;
  end;
/

delete from livres 
where codOuv = 'CA12';

create or replace trigger redond_Pers
  after insert on pret;
  for each row 
  begin
  end;
/

alter table Personnes
  add nbPret number default 0
  add dateDerPret date
  add dateDerRet date 
;

alter table Personnes
  drop column nbPret
;
alter table Personnes
  drop column dateDerRet
;
alter table Personnes
  drop column dateDerPret
;

update Personnes x set nbPret = (
  SELECT count (*) FROM pret
  where (x.codpers = pret.codpers)
);

update Personnes x set dateDerPret = (
  SELECT max (dateP) FROM pret
  where (x.codpers = pret.codpers)
);

create or replace trigger add_pret
  after insert on pret
  for each row 
  begin
    update Personnes set nbPret = (nbPret+1);
    update livres set nbPretL = (nbPretL+1);
    update livres set dateDerRetL = SYSDATE;
    update Personnes set dateDerPret = SYSDATE;
  end;
/

create or replace trigger del_pret
  after delete on pret
  for each row 
  begin
    insert into histopret (codex, datepret, codpers, dateret)
    values (:old.codex, :old.datep, :old.codpers, sysdate);
    update Personnes set dateDerRet = SYSDATE;
    update livres set dateDerRetL = SYSDATE;
  end;
/

alter table livres
  add nbPretL number default 0
  add nbJourPret number default 0
  add dateDerRetL date 
;

UPDATE livres x set dateDerRetL = (
  SELECT max (dateP) 
  FROM pret , exemplaires
  where pret.codEx = exemplaires.codEx 
  and x.codOuv = exemplaires.codOuv
);
/

create or replace trigger maxEmprt
  before insert on pret
  for each row
  declare
    maxLiv number;
  begin
    select count(codex) into maxLiv 
      from pret
      where :new.codpers = pret.codpers;
    if maxLiv >= 10 then
      raise_application_error(-20500, 'trop de prets');
    end if;
  end;
/




