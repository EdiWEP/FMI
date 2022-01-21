SET SERVEROUTPUT ON;

-- 2.

CREATE OR REPLACE TYPE tip_orase_pec AS VARRAY(100) OF VARCHAR2(100);
/


DROP TABLE excursie_pec;
CREATE TABLE excursie_pec (
    id_excursie NUMBER(5) PRIMARY KEY,
    denumire VARCHAR2(20),
    orase tip_orase_pec,
    status VARCHAR2(20)
);

-- a.

INSERT INTO excursie_pec VALUES(1, 'Sudul Romaniei', tip_orase_pec('Braila', 'Galati'), 'disponibila');
INSERT INTO excursie_pec VALUES(2, 'La Munte', tip_orase_pec('Brasov', 'Predeal'), 'anulata');
INSERT INTO excursie_pec VALUES(3, 'La Mare', tip_orase_pec('Costinesti', 'Mamaia', 'Vama'), 'anulata');
INSERT INTO excursie_pec VALUES(4, 'La Facultate', tip_orase_pec('FMI', 'Litere'), 'anulata');
INSERT INTO excursie_pec VALUES(5, 'Vacanta Random', tip_orase_pec('Bucuresti', 'Iasi', 'Cluj'), 'disponibila');


-- b.

-- Adaugare oras la final

DECLARE
    destinatii tip_orase_pec;
    idexcursie NUMBER(5) := &Idul_excursiei;
    oras VARCHAR(20) := '&Numele_orasului';
BEGIN

    SELECT orase INTO destinatii
    FROM excursie_pec 
    WHERE idexcursie = id_excursie;
  
    destinatii.extend();
    destinatii(destinatii.last) := oras;
    
    UPDATE excursie_pec 
    SET orase = destinatii
    WHERE idexcursie = id_excursie;
END;
/

-- Adaugare oras pe indexul 2

DECLARE
    destinatii tip_orase_pec;
    idexcursie NUMBER(5) := &Idul_excursiei;
    oras VARCHAR(20) := '&Numele_orasului';
    idx BINARY_INTEGER;
BEGIN

    SELECT orase INTO destinatii
    FROM excursie_pec
    WHERE idexcursie = id_excursie;
    
    destinatii.extend();
    
    idx := destinatii.last;
    
    WHILE idx > destinatii.first LOOP
        destinatii(idx) := destinatii(idx - 1);
        idx := idx - 1;
    END LOOP;
    
    destinatii(2) := oras;
    
    UPDATE excursie_pec
    SET orase = destinatii
    WHERE idexcursie = id_excursie;
END;
/


-- Swap intre doua orase

DECLARE
    destinatii tip_orase_pec;
    idexcursie NUMBER(5) := &Idul_excursiei;
    oras1 VARCHAR(20) := '&Numele_orasului_1';
    oras2 VARCHAR(20) := '&Numele_orasului_2';
    idx BINARY_INTEGER;
BEGIN

    SELECT orase INTO destinatii
    FROM excursie_pec
    WHERE idexcursie = id_excursie;
    
    idx := destinatii.first;
    
    WHILE idx <= destinatii.last LOOP
        
        IF destinatii(idx) = oras1 THEN
            destinatii(idx) := oras2;
        ELSIF destinatii(idx) = oras2 THEN
            destinatii(idx) := oras1;
        END IF;
        
        idx := idx + 1;
    END LOOP;
    
    UPDATE excursie_pec
    SET orase = destinatii
    WHERE idexcursie = id_excursie;
END;
/

-- Stergerea unui oras

DECLARE
    destinatii tip_orase_pec;
    idexcursie NUMBER(5) := &Idul_excursiei;
    oras VARCHAR(20) := '&Numele_orasului';
    idx BINARY_INTEGER;
    gasit BOOLEAN := false;
BEGIN
    
    SELECT orase INTO destinatii
    FROM excursie_pec
    WHERE idexcursie = id_excursie;
    
    idx := destinatii.first;
    
    WHILE idx < destinatii.last LOOP
    
        IF destinatii(idx) = oras THEN
            gasit := true;
        END IF;
        IF gasit = true THEN
            destinatii(idx) := destinatii(idx + 1);
        END IF;
        
        idx := idx + 1;
        
    END LOOP;
    
    IF gasit = true THEN
        destinatii.trim();
    END IF;
    
    UPDATE excursie_pec
    SET orase = destinatii
    WHERE idexcursie = id_excursie;
END;
/


-- c)

DECLARE
    destinatii tip_orase_pec;
    idexcursie NUMBER(5) := &Idul_excursiei;
BEGIN
    
    SELECT orase INTO destinatii
    FROM excursie_pec
    WHERE idexcursie = id_excursie;
    
    dbms_output.put_line('Numarul de destinatii: ' || destinatii.last);
    
    FOR idx IN destinatii.first .. destinatii.last LOOP
        dbms_output.put_line('Orasul ' || idx || ': ' || destinatii(idx));
    END LOOP;
END;
/

-- d)

DECLARE
    destinatii tip_orase_pec;
    nrExcursii NUMBER(5);
    nume VARCHAR(20);
BEGIN

    SELECT COUNT(*) INTO nrExcursii
    FROM excursie_pec;
    
    FOR i IN 1 .. nrExcursii LOOP
        
        SELECT orase, denumire INTO destinatii, nume
        FROM excursie_pec
        WHERE id_excursie = i;
        
        dbms_output.put_line('Excursia ' || nume);
    
        FOR idx IN destinatii.first .. destinatii.last LOOP
            dbms_output.put_line('Orasul ' || idx || ': ' || destinatii(idx));
        
        END LOOP;
    
        dbms_output.new_line();
        
    END LOOP;
END;
/

-- e)

DECLARE
    destinatii tip_orase_pec;
    nrExcursii NUMBER(5);
    minim NUMBER(3) := 999;
BEGIN

    SELECT COUNT(*) INTO nrExcursii
    FROM excursie_pec;
    
    FOR i IN 1 .. nrExcursii LOOP
        
        SELECT orase INTO destinatii
        FROM excursie_pec
        WHERE id_excursie = i;
        
        IF minim > destinatii.count THEN
            minim := destinatii.count;
        END IF;
    END LOOP;
    
    FOR i IN 1 .. nrExcursii LOOP
        
        SELECT orase INTO destinatii
        FROM excursie_pec
        WHERE id_excursie = i;
        
        IF minim = destinatii.count THEN
            UPDATE excursie_pec
            SET status = 'anulata'
            WHERE id_excursie = i;
        END IF;
    END LOOP;
END;
/


-- 3. La fel ca 2 dar folosim nested table

DROP TABLE excursie_pec;

CREATE OR REPLACE TYPE tip_orase_pec IS TABLE OF VARCHAR2(100);
/

CREATE TABLE excursie_pec(
    id_excursie NUMBER(5) PRIMARY KEY,
    denumire VARCHAR2(20),
    status VARCHAR2(20)
);

ALTER TABLE excursie_pec
    ADD (orase tip_orase_pec) NESTED TABLE orase STORE AS orase_pec;

-- a)

INSERT INTO excursie_pec VALUES(1, 'Sudul Romaniei', 'disponibila', tip_orase_pec('Braila', 'Galati'));
INSERT INTO excursie_pec VALUES(2, 'La Munte', 'anulata', tip_orase_pec('Brasov', 'Predeal'));
INSERT INTO excursie_pec VALUES(3, 'La Mare', 'anulata', tip_orase_pec('Costinesti', 'Mamaia', 'Vama'));
INSERT INTO excursie_pec VALUES(4, 'La Facultate', 'anulata', tip_orase_pec('FMI', 'Litere'));
INSERT INTO excursie_pec VALUES(5, 'Vacanta Random', 'disponibila', tip_orase_pec('Bucuresti', 'Iasi', 'Cluj'));

-- b.

-- Adaugare oras la final

DECLARE
    destinatii tip_orase_pec;
    idexcursie NUMBER(5) := &Idul_excursiei;
    oras VARCHAR(20) := '&Numele_orasului';
BEGIN

    SELECT orase INTO destinatii
    FROM excursie_pec 
    WHERE idexcursie = id_excursie;
  
    destinatii.extend();
    destinatii(destinatii.last) := oras;
    
    UPDATE excursie_pec 
    SET orase = destinatii
    WHERE idexcursie = id_excursie;
END;
/

-- Adaugare oras pe indexul 2

DECLARE
    destinatii tip_orase_pec;
    idexcursie NUMBER(5) := &Idul_excursiei;
    oras VARCHAR(20) := '&Numele_orasului';
    idx BINARY_INTEGER;
BEGIN

    SELECT orase INTO destinatii
    FROM excursie_pec
    WHERE idexcursie = id_excursie;
    
    destinatii.extend();
    
    idx := destinatii.last;
    
    WHILE idx > destinatii.first LOOP
        destinatii(idx) := destinatii(idx - 1);
        idx := idx - 1;
    END LOOP;
    
    destinatii(2) := oras;
    
    UPDATE excursie_pec
    SET orase = destinatii
    WHERE idexcursie = id_excursie;
END;
/


-- Swap intre doua orase

DECLARE
    destinatii tip_orase_pec;
    idexcursie NUMBER(5) := &Idul_excursiei;
    oras1 VARCHAR(20) := '&Numele_orasului_1';
    oras2 VARCHAR(20) := '&Numele_orasului_2';
    idx BINARY_INTEGER;
BEGIN

    SELECT orase INTO destinatii
    FROM excursie_pec
    WHERE idexcursie = id_excursie;
    
    idx := destinatii.first;
    
    WHILE idx <= destinatii.last LOOP
        
        IF destinatii(idx) = oras1 THEN
            destinatii(idx) := oras2;
        ELSIF destinatii(idx) = oras2 THEN
            destinatii(idx) := oras1;
        END IF;
        
        idx := idx + 1;
    END LOOP;
    
    UPDATE excursie_pec
    SET orase = destinatii
    WHERE idexcursie = id_excursie;
END;
/

-- Stergerea unui oras

DECLARE
    destinatii tip_orase_pec;
    idexcursie NUMBER(5) := &Idul_excursiei;
    oras VARCHAR(20) := '&Numele_orasului';
    idx BINARY_INTEGER;
    gasit BOOLEAN := false;
BEGIN
    
    SELECT orase INTO destinatii
    FROM excursie_pec
    WHERE idexcursie = id_excursie;
    
    idx := destinatii.first;
    
    WHILE idx < destinatii.last LOOP
    
        IF destinatii(idx) = oras THEN
            gasit := true;
        END IF;
        IF gasit = true THEN
            destinatii(idx) := destinatii(idx + 1);
        END IF;
        
        idx := idx + 1;
        
    END LOOP;
    
    IF gasit = true THEN
        destinatii.trim();
    END IF;
    
    UPDATE excursie_pec
    SET orase = destinatii
    WHERE idexcursie = id_excursie;
END;
/


-- c)

DECLARE
    destinatii tip_orase_pec;
    idexcursie NUMBER(5) := &Idul_excursiei;
BEGIN
    
    SELECT orase INTO destinatii
    FROM excursie_pec
    WHERE idexcursie = id_excursie;
    
    dbms_output.put_line('Numarul de destinatii: ' || destinatii.last);
    
    FOR idx IN destinatii.first .. destinatii.last LOOP
        dbms_output.put_line('Orasul ' || idx || ': ' || destinatii(idx));
    END LOOP;
END;
/

-- d)

DECLARE
    destinatii tip_orase_pec;
    nrExcursii NUMBER(5);
    nume VARCHAR(20);
BEGIN

    SELECT COUNT(*) INTO nrExcursii
    FROM excursie_pec;
    
    FOR i IN 1 .. nrExcursii LOOP
        
        SELECT orase, denumire INTO destinatii, nume
        FROM excursie_pec
        WHERE id_excursie = i;
        
        dbms_output.put_line('Excursia ' || nume);
    
        FOR idx IN destinatii.first .. destinatii.last LOOP
            dbms_output.put_line('Orasul ' || idx || ': ' || destinatii(idx));
        
        END LOOP;
    
        dbms_output.new_line();
        
    END LOOP;
END;
/

-- e)

DECLARE
    destinatii tip_orase_pec;
    nrExcursii NUMBER(5);
    minim NUMBER(3) := 999;
BEGIN

    SELECT COUNT(*) INTO nrExcursii
    FROM excursie_pec;
    
    FOR i IN 1 .. nrExcursii LOOP
        
        SELECT orase INTO destinatii
        FROM excursie_pec
        WHERE id_excursie = i;
        
        IF minim > destinatii.count THEN
            minim := destinatii.count;
        END IF;
    END LOOP;
    
    FOR i IN 1 .. nrExcursii LOOP
        
        SELECT orase INTO destinatii
        FROM excursie_pec
        WHERE id_excursie = i;
        
        IF minim = destinatii.count THEN
            UPDATE excursie_pec
            SET status = 'anulata'
            WHERE id_excursie = i;
        END IF;
    END LOOP;
END;
/