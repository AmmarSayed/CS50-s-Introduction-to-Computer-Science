/*
SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
Your query should output a table with a single column for the name of each person.
There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
Kevin Bacon himself should not be included in the resulting list.
*/
SELECT p.name FROM people p WHERE p.id IN(
SELECT DISTINCT s.person_id FROM stars s WHERE s.movie_id IN(
SELECT s.movie_id FROM stars s WHERE s.person_id IN(
SELECT p.id FROM people p WHERE p.name = ("Kevin Bacon")AND p.birth = 1958))
AND s.person_id <> (SELECT p.id FROM people p WHERE p.name = ("Kevin Bacon")))
;