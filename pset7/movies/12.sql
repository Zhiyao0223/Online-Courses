-- write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred
SELECT title
FROM movies
INNER JOIN stars ON movies.id = stars.movie_id AND stars.person_id IN
                                                                    (SELECT id
                                                                    FROM people
                                                                    WHERE name = 'Johnny Depp' OR name = 'Helena Bonham Carter')
GROUP BY title
Having count(title) = 2
ORDER BY title ASC
LIMIT 10;
