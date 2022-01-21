
SET SERVEROUTPUT ON;
-- 2. b)

create table octombrie_pec(id number, data date);

declare
d date := trunc(sysdate, 'mm');
n number := extract(day from last_day(sysdate));
begin
    for i IN 1..n LOOP
          insert into octombrie_pec
          values (i, d);
          d := d+1;
    END LOOP;
end;

select data as "Data", count(data) as "Imprumuturi"
from octombrie_pec
group by data
order by data;

-- 3.

DECLARE
    nume VARCHAR(100) := '&nume';
    numar NUMBER := 0;
    numarPersoane NUMBER := 0;
BEGIN
    SELECT COUNT(*) INTO numar
        FROM rental rentTable 
        JOIN member memTable 
        ON (rentTable.member_id = memTable.member_id)
        WHERE LOWER(nume) = LOWER(memTable.last_name);
    SELECT COUNT(*) INTO numarPersoane
        FROM member memTable
        WHERE LOWER(nume) = LOWER(memtable.last_name);
        
    IF numarPersoane = 0 THEN
        dbms_output.put_line('Persoana nu exista');
    END IF;
    IF numarPersoane > 1 THEN
        dbms_output.put_line('Exista mai multe persoane cu acest nume');
    END IF;
    IF numarPersoane = 1 THEN
        dbms_output.put_line('Numarul de imprumuturi ale lui ' || nume || ': ' || numar);
    END IF;
END;


-- 4.

DECLARE
    nume VARCHAR(100) := '&nume';
    numar NUMBER := 0;
    numarImprumutate NUMBER := 0;
    numarTotal NUMBER := 0;
    procent NUMBER := 0;
    numarPersoane NUMBER := 0;
BEGIN
    SELECT COUNT(*) INTO numarPersoane
        FROM member memTable
        WHERE LOWER(nume) = LOWER(memtable.last_name);
    
    IF numarPersoane = 0 THEN
        dbms_output.put_line('Persoana nu exista');
    END IF;
    IF numarPersoane > 1 THEN
        dbms_output.put_line('Exista mai multe persoane cu acest nume');
    END IF;
    IF numarPersoane = 1 THEN     
        
        SELECT COUNT(*) INTO numar
            FROM rental rentTable 
            JOIN member memTable 
            ON (rentTable.member_id = memTable.member_id)
            WHERE LOWER(nume) = LOWER(memTable.last_name);
        
        dbms_output.put_line('Numarul de imprumuturi ale lui ' || nume || ': ' || numar);
    
        SELECT COUNT(*) INTO numarTotal
        FROM title titleTable;
        
        SELECT COUNT(DISTINCT title_id) INTO numarImprumutate
            FROM rental rentTable 
            JOIN member memTable 
            ON (rentTable.member_id = memTable.member_id)
            WHERE LOWER(nume) = LOWER(memTable.last_name);
    
        procent := numarImprumutate / numarTotal * 100;
        
        IF procent > 75 THEN
            dbms_output.put_line('(Categoria 1)');
        ELSIF procent > 50 THEN
            dbms_output.put_line('(Categoria 2)');
        ELSIF procent > 25 THEN
            dbms_output.put_line('(Categoria 3)');
        ELSE
            dbms_output.put_line('(Categoria 4)');
        END IF;

    END IF;    
END;


-- 5.


CREATE TABLE member_pec AS SELECT * FROM member;
    
ALTER TABLE member_pec ADD discount NUMBER;
    
SELECT * FROM member_pec;

DECLARE
    numarImprumutate NUMBER := 0;
    numarTotal NUMBER := 0;
    procent NUMBER := 0;
    reducere NUMBER := 0;
    cod NUMBER := '&cod';
    persoanaExista NUMBER := 0;
BEGIN
    SELECT COUNT(*) INTO persoanaExista
    FROM member_pec memTable
    WHERE memTable.member_id = cod;
    
    IF persoanaExista = 0 THEN
        dbms_output.put_line('Nu exista o persoana cu acest cod.');
    ELSE 
    
        SELECT COUNT(*) INTO numarTotal
        FROM title titleTable;
    
        SELECT COUNT(DISTINCT title_id) INTO numarImprumutate
            FROM rental rentTable 
            WHERE rentTable.member_id = cod;
            
        procent := numarImprumutate / numarTotal * 100;
    
        IF procent > 75 THEN
            reducere := 0.1;
        ELSIF procent > 50 THEN
            reducere := 0.5;
        ELSIF procent > 25 THEN
            reducere := 0.3;
        ELSE
            reducere := 0.0;
        END IF;
        
        UPDATE member_pec memTable
            SET memTable.discount = reducere
            WHERE memTable.member_id = cod;
        
        dbms_output.put_line('Discount actualizat');
    END IF;
END;

-- 6.

VARIABLE angajati NUMBER;
VARIABLE departament VARCHAR2;

BEGIN
    SELECT department_name, COUNT(*) INTO :departament, :angajati
        FROM employees empTable
        JOIN departments depTable
        ON empTable.department_id = depTable.department_id
        GROUP BY department_name
        HAVING COUNT(*) = (SELECT MAX(COUNT(*)) FROM employees GROUP BY department_id);

    dbms_output.put_line('Departamentul ' || :departament || ' are numarul maxim de ' || :angajati || ' angajati.');
END;
/
PRINT departament
PRINT angajati
