-- write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year
SELECT DISTINCT name
FROM people
INNER JOIN stars ON person_id = people.id
INNER JOIN movies ON movies.id = movie_id AND year = '2004'
ORDER BY birth ASC;