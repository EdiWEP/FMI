-- 10.

select memTable.first_name, memTable.last_name, rentTable.title_id, rentTable.copy_id, count(*) as "Numar Imprumuturi"
from member memTable 
join rental rentTable 
on memTable.member_id = rentTable.member_id
group by memTable.first_name, memTable.last_name, rentTable.title_id, rentTable.copy_id
order by memTable.first_name;


-- 12. a)

select extract(day from book_date) as "Ziua", count(book_date) as "Imprumuturi"
from rental
where ( extract(month from sysdate) = extract(month from book_date) ) and ( (extract(day from book_date) = 1) or (extract(day from book_date) = 2) )
group by book_date;

-- 12. b)

select extract(day from book_date) as "Ziua", count(book_date) as "Imprumuturi"
from rental
where extract(month from sysdate) = extract(month from book_date)
group by book_date;