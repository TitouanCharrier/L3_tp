create table ouvrages as
  select codOuv, titOuv, langue 
  from tpbd.l2ouvrages;

create table livres as
  select codOuv, titOuv, langue 
  from tpbd.l2ouvrages;

create table exemplaires as
  select E.codEx, O.codOuv, E.dateentBib, O.nbpag, O.nomedit 
  from tpbd.l2exemplaires E, tpbd.l2ouvrages O
  where E.codOuv = O.codOuv;

create table Bibliotheque as
  select codBib, nomBib, rueBib, cpBib, villeBib 
  from tpbd.l2bibliotheques;

create table personnes as
  select codPers, nomPers, prenomPers, ruePers, cpPers, villePers, dNaiss, datIns, codBib
  from tpbd.l2personnes;

create table pret as
  select codEx, codPers, dateP
  from tpbd.l2pret;

create table revues (
  codOuv char(4), 
  titOuv varchar(20), 
  langue varchar(20), 
  anEditPN date, 
  periodicite varchar(20),
  constraint pk_revues PRIMARY KEY(codOuv),
  constraint fk_revues_ouvrage FOREIGN KEY(codOuv) REFERENCES ouvrages(codOuv)
);

create table numeros (
  codOuv char(4), 
  numParu number, 
  titNum varchar(20), 
  dateParu date, 
  nbOccur number,
  constraint fk_numeros FOREIGN KEY(codOuv) REFERENCES revues(codOuv),
  constraint pk_numeros PRIMARY KEY(codOuv, numParu)
);

create table histopret (
  codEx char(5), 
  datePret date, 
  codPers char(4) not null, 
  dateRet date,
  constraint pk_histopret PRIMARY KEY(codEx, datePret),
  constraint fk_histopret_codEx FOREIGN KEY(codEx) REFERENCES exemplaires(codEx),
  constraint fk_histopret_codPers FOREIGN KEY(codPers) REFERENCES personnes(codPers)
  
);

create table auteurs (
  codAut number, 
  nomAut varchar(20), 
  prenomAut varchar(20),
  constraint pk_auteurs PRIMARY KEY(codAut)
);

create table ecrit (
  codAut number, 
  codOuv char(4),
  constraint pk_ecrit PRIMARY KEY(codAut, codOuv),
  constraint fk_ecr_auth FOREIGN KEY(codAut) REFERENCES auteurs(codAut),
  constraint fk_ecr_ouv FOREIGN KEY(codOuv) REFERENCES livres(codOuv)
);

create table motscles (
  codMot char(4), 
  libelleMot varchar(20), 
  codMotPere char(4),
  constraint pk_motscles PRIMARY KEY(codMot),
  constraint fk_motscles FOREIGN KEY(codMotPere) REFERENCES motscles(codMot)
);

create table traite (
  codOuv char(4), 
  codMot char(5),
  constraint pk_traite PRIMARY KEY (codOuv,codMot),
  constraint fk_traite_codOuv FOREIGN KEY(codOuv) REFERENCES ouvrages(codOuv),
  constraint fk_traite_motsCles FOREIGN KEY(codMot) REFERENCES motscles(codMot)
);

ALTER TABLE ouvrages 
ADD constraint pk_ouvrages PRIMARY KEY(codOuv);

ALTER TABLE livres 
ADD constraint pk_livres PRIMARY KEY(codOuv)
ADD constraint fk_livres FOREIGN KEY(codOuv) REFERENCES ouvrages(codOuv);

ALTER TABLE exemplaires
add constraint pk_exemplaire PRIMARY KEY(codEx)
add constraint fk_ex_ouv FOREIGN KEY(codOuv) REFERENCES ouvrages(codOuv)
add constraint fk_ex_bib FOREIGN KEY(codBib) REFERENCES Bibliotheque(codBib);

ALTER TABLE Bibliotheque
add constraint pk_bibliotheque PRIMARY KEY(codBib);

ALTER TABLE personnes
add constraint pk_personne PRIMARY KEY(codPers);

ALTER TABLE ecrit 

ALTER TABLE pret
add constraint pk_pret PRIMARY KEY (codEx)
add constraint fk_pret_codEx FOREIGN KEY(codEx) REFERENCES exemplaires(codEx)
add constraint fk_pret_codPers FOREIGN KEY(codPers) REFERENCES personnes(codPers);

update exemplaires new set codBib = (
  SELECT codBib 
    FROM tpbd.l2exemplaires_biblio old
    where new.codEx = old.codEx
);

create sequence auteurs_cle_primaire;

create view AutNoDoublons as 
select distinct nomAut, prenomAut from tpbd.l2ouvrages;

insert into auteurs 
  select auteurs_cle_primaire.nextval, nomAut, prenomAut
  from AutNoDoublons;

insert into ecrit E
  SELECT codAut, codOuv 
  FROM  auteurs A, tpbd.l2ouvrages O
  where A.nomAut = O.nomAut
  and A.prenomAut = O.prenomAut;

------------------------------------------------------------------------------------

select table_name from all_tables where owner='TCHARRIER004';


SELECT constraint_name, constraint_type, status
FROM user_constraints
WHERE table_name = 'NOM_DE_LA_TABLE';
