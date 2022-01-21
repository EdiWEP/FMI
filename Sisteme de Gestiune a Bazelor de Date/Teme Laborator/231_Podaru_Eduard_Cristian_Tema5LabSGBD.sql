SET SERVEROUTPUT ON;
-- 1.

SELECT 
CASE
    WHEN COUNT(employee_id) = 0 then 'In departamentul ' || depTable.department_name || ' nu lucreaza angajati'
    WHEN COUNT(employee_id) = 1 then 'In departamentul ' || depTable.department_name || ' lucreaza un angajat'
    WHEN COUNT(employee_id) > 1 then 'In departamentul ' || depTable.department_name || ' lucreaza ' || COUNT(employee_id) || ' angajati'
END AS propozitie
FROM employees empTable
RIGHT JOIN departments depTable ON empTable.department_id = depTable.department_id
GROUP BY depTable.department_name;


-- 2. a)

DECLARE
    
    TYPE dictEntry IS RECORD(depName departments.department_name%TYPE, depCount NUMBER(4));
    TYPE dictType IS TABLE OF dictEntry;
    
    dict dictType;
    
    CURSOR c IS
        SELECT department_name nume, COUNT(employee_id) nr 
        FROM departments d, employees e
        WHERE d.department_id=e.department_id(+)
        GROUP BY department_name; 
BEGIN
    
    OPEN c;
    FETCH c BULK COLLECT INTO dict LIMIT 5;
 
    WHILE(dict.count > 0) LOOP
        FOR i IN dict.FIRST..dict.LAST LOOP
            IF dict(i).depCount = 0 THEN
                dbms_output.put_line('In departamentul ' || dict(i).depName ||  ' nu lucreaza angajati');
            ELSIF dict(i).depCount = 1 THEN
                dbms_output.put_line('In departamentul ' || dict(i).depName || ' lucreaza un angajat');
            ELSIF dict(i).depCount > 1 THEN
                dbms_output.put_line('In departamentul ' || dict(i).depName || ' lucreaza ' || dict(i).depCount || ' angajati');
            END IF;
 
        END LOOP;
 
        FETCH c BULK COLLECT INTO dict LIMIT 5;
    END LOOP;

    CLOSE c;

END;
/

-- 2. b)

DECLARE
    
    TYPE dictEntry IS RECORD(depName departments.department_name%TYPE, depCount NUMBER(4));
    TYPE dictType IS TABLE OF dictEntry;
    
    dict dictType;

    idx NUMBER(4);
    idx2 NUMBER(4);
BEGIN
    
    SELECT department_name nume, COUNT(employee_id) nr 
    BULK COLLECT INTO dict
    FROM departments d, employees e
    WHERE d.department_id=e.department_id(+)
    GROUP BY department_name;
 
    idx := dict.FIRST;
    
    WHILE idx<=dict.LAST LOOP
        IF idx+4 > dict.LAST THEN
            idx2 := dict.LAST;
        ELSE idx2 := idx+4;
        END IF;
        
        FOR i IN idx..idx2 LOOP
            IF dict(i).depCount = 0 THEN
                dbms_output.put_line('In departamentul ' || dict(i).depName ||  ' nu lucreaza angajati');
            ELSIF dict(i).depCount = 1 THEN
                dbms_output.put_line('In departamentul ' || dict(i).depName || ' lucreaza un angajat');
            ELSIF dict(i).depCount > 1 THEN
                dbms_output.put_line('In departamentul ' || dict(i).depName || ' lucreaza ' || dict(i).depCount || ' angajati');
            END IF;
 
        END LOOP;
        
        idx := idx2+1;
    END LOOP;
END;
/
