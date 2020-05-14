SELECT title FROM movies WHERE year ='2008'

select birth from people where name = 'Emma Stone'

select title from movies where year >= 2018 order by title

select count(movie_id) from ratings where rating = 10.0

select title, year from movies
where title like 'Harry Potter%'
order by year

select avg(rating) from ratings where movie_id in (select id from movies where year = '2012')

select movies.title, ratings.rating
from movies
join ratings
on movies.id = ratings.movie_id
where movies.year = '2010'
order by rating desc, title

select name from people where id in (select person_id from stars where movie_id in (select id from movies where title = 'Toy Story'))

select name from people where id in (select person_id from stars where movie_id in (select id from movies where year = '2004'))
order by birth

select name from people where id in (select person_id from directors where movie_id in (select movie_id from ratings where rating >= 9.0))

select title from movies
join ratings
on movies.id = ratings.movie_id
where id in (select movie_id from stars where person_id in (select id from people where name = 'Chadwick Boseman'))
order by rating desc
limit 5

select title from movies join stars on movies.id = stars.movie_id join people on stars.person_id = people.id
where name in ('Johnny Depp', 'Helena Bonham Carter')
group by movie_id
having count(distinct person_id) = 2

select distinct name from people where id in
(select person_id from stars where movie_id in
(select movie_id from stars where person_id in
(select id from people where name = 'Kevin Bacon')
and (select id from people where birth = '1958')))
except
select name from people where name = 'Kevin Bacon'
order by name
