SET SERVEROUTPUT ON;

-- 1. b) Ciclu cursoare

DECLARE 
    CURSOR j IS SELECT * FROM jobs;
    CURSOR e (jb VARCHAR2) IS SELECT * FROM employees e WHERE e.job_id = jb;
    nr NUMBER;
BEGIN
    FOR jjob IN j LOOP
        dbms_output.put_line('Job ' || jjob.job_title || ':');
    
        nr := 0;
        
        FOR employee IN e(jjob.job_id) LOOP
            nr := nr + 1;
            dbms_output.put_line(employee.first_name || ' ' || employee.last_name);
        END LOOP;
        
        IF nr = 0 THEN
            dbms_output.put_line('Nu exista angajati');
        END IF;
    END LOOP;
END;
/

-- 1. d) Expresii cursor

SELECT * FROM jobs;

DECLARE 
    TYPE rcursor_t IS REF CURSOR;
    CURSOR j IS (
        SELECT j.job_title, 
        CURSOR (SELECT * FROM employees e WHERE e.job_id = j.job_id)
        FROM jobs j);
        
    jjob VARCHAR2(100); 
    employee employees%ROWTYPE;
    ccursor rcursor_t;
    nr NUMBER;
    
BEGIN
    OPEN j;
    LOOP
        FETCH j INTO jjob, ccursor;
        EXIT WHEN j%NOTFOUND;
        nr := 0;
        dbms_output.put_line('Job ' || jjob || ':');
        
        LOOP
            FETCH ccursor INTO employee;
            EXIT WHEN ccursor%NOTFOUND;
            
            nr := nr + 1;
            dbms_output.put_line(employee.first_name || ' ' || employee.last_name);
        END LOOP;
        
        IF nr = 0 THEN
            dbms_output.put_line('Nu exista angajati');
        END IF;
    END LOOP;
    CLOSE j;
END;
/

-- 2.

DECLARE
    jobsum NUMBER;
    totalsum NUMBER;
    nrjob NUMBER;
    totalnr NUMBER;
    CURSOR j IS SELECT * FROM jobs;
    CURSOR e (jb VARCHAR2) IS SELECT * FROM employees e WHERE e.job_id = jb;
BEGIN
    totalsum := 0;
    totalnr := 0;
    
    FOR jjob IN j LOOP
        dbms_output.put_line('Jobul ' || jjob.job_title || ':');
    
        nrjob := 0;
        jobsum := 0;
        FOR employee IN e(jjob.job_id) LOOP
            nrjob := nrjob + 1;
            jobsum := jobsum + employee.salary;
        END LOOP;
        
        totalsum := totalsum + jobsum;
        totalnr := totalnr + nrjob;
        
        dbms_output.put_line(nrjob || ' angajati');
        IF nrjob > 0 THEN
            dbms_output.put_line('Suma salarii: ' || jobsum);
            dbms_output.put_line('Media salarii: ' || jobsum / nrjob); 
            dbms_output.put_line('Lista de angajati:'); 
        END IF;
            
        FOR employee IN e(jjob.job_id) LOOP
            dbms_output.put_line(employee.first_name || ' ' || employee.last_name);
        END LOOP;
        
        IF nrjob = 0 THEN
            dbms_output.put_line('Nu exista angajati');
        END IF;
    END LOOP;
    
    dbms_output.put_line('Exista ' || totalnr || ' angajati in total');
    dbms_output.put_line('Salariul total: ' || totalsum || ' lei pe luna');
    dbms_output.put_line('Salariul mediu: ' || totalsum / totalnr || ' lei pe luna');
END;
/

-- 3.

DECLARE
    individualSalary NUMBER;
    totalsum NUMBER;
    CURSOR j IS SELECT * FROM jobs;
    CURSOR e IS SELECT * FROM employees;
BEGIN
    totalsum := 0;
    
    FOR employee IN j LOOP
        totalsum := totalsum + employee.salary;
        
        IF employee.commission_pct IS NOT NULL THEN
            totalsum := totalsum + employee.salary * employee.commission_pct;
        END IF;   
    END LOOP;
    
    dbms_output.put_line('Suma totala de platit: ' || totalsum);

    FOR employee IN e LOOP
        individualSalary := employee.salary;
        IF employee.commission_pct IS NOT NULL THEN
            individualSalary := individualSalary * (1 + employee.commission_pct);
        END IF;
        
        dbms_output.put_line('Plata lunara catre ' || employee.first_name || ' ' || employee.last_name || ': ' ||
                individualSalary || ' -> ' || 100 * individualSalary / totalsum || '% din total');
    END LOOP;
END;
/

-- 4.

DECLARE
    nr NUMBER;
    CURSOR j IS SELECT * FROM jobs;
    CURSOR e (jb VARCHAR2) IS SELECT * FROM employees e WHERE e.job_id = jb ORDER BY e.salary DESC; 
BEGIN
    FOR jjob IN j LOOP
        dbms_output.put_line('Jobul ' || jjob.job_title || ':');
        
        nr := 0;
        FOR employee IN e(jjob.job_id) 
        LOOP
            IF nr = 5 THEN
                EXIT;
            END IF;
            
            nr := nr + 1;
            dbms_output.put_line(employee.first_name || ' ' || employee.last_name
                    || ', salariu: ' || employee.salary);
        END LOOP;
        
        IF nr < 5 THEN
            dbms_output.put_line('Sunt mai putin de 5 angajati');
        END IF;
    END LOOP;
END;
/

-- 5.

DECLARE
    nr NUMBER;
    prev NUMBER;
    CURSOR j IS SELECT * FROM jobs;
    CURSOR e (jb VARCHAR2) IS SELECT * FROM employees e WHERE e.job_id = jb ORDER BY e.salary DESC;
BEGIN
    FOR jjob IN j LOOP
        dbms_output.put_line('Jobul ' || jjob.job_title || ':');
        nr := 0;
        prev := 0;
        
        FOR employee IN e(jjob.job_id) 
        LOOP
            IF nr = 5 THEN
                EXIT;
            END IF;
          
            IF employee.salary = prev THEN
                dbms_output.put_line(employee.first_name || ' ' || employee.last_name);
            ELSE
                nr := nr + 1;
                prev := employee.salary;
                dbms_output.put_line(nr || '. Salariul: ' || employee.salary || ' Angajati: ');
                dbms_output.put_line(employee.first_name || ' ' || employee.last_name);
            END IF;
        END LOOP;
        
        
        IF nr < 5 THEN
            dbms_output.put_line('Sunt mai putin de 5 angajati');
        END IF;
    END LOOP;
END;
/