

spool C:\Users\User\Desktop\insertDepartments.sql;

set pagesize 0
set feedback off

select 'INSERT INTO departments(department_id, department_name, manager_id, location_id) VALUES(' || department_id || ', ''' || department_name || ''', ' || manager_id || ', ' || location_id || ');' 
from departments;

spool off;