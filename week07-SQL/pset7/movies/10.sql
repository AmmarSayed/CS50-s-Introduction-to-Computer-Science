/*
 SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
*/

SELECT p.name FROM people p WHERE p.id IN
(SELECT d.person_id FROM directors d WHERE d.movie_id IN
(SELECT r.movie_id FROM ratings r JOIN movies m ON r.movie_id = m.id WHERE r.rating >= 9.0));