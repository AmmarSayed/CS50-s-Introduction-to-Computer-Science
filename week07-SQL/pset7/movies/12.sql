/*
SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
Your query should output a table with a single column for the title of each movie.
You may assume that there is only one person in the database with the name Johnny Depp.
You may assume that there is only one person in the database with the name Helena Bonham Carter.
*/
SELECT  m.title FROM movies m WHERE m.id IN(
SELECT s.movie_id FROM stars s WHERE s.person_id IN(
SELECT p.id FROM people p WHERE p.name IN ("Helena Bonham Carter")))
INTERSECT
SELECT  m.title FROM movies m WHERE m.id IN(
SELECT s.movie_id FROM stars s WHERE s.person_id IN(
SELECT p.id FROM people p WHERE p.name IN ("Johnny Depp")));