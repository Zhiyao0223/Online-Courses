-- write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred
SELECT DISTINCT name
FROM people
INNER JOIN stars ON people.id = stars.person_id AND people.name != 'Kevin Bacon'
INNER JOIN movies ON movies.id = stars.movie_id AND stars.movie_id IN
                                                                    (SELECT movie_id
                                                                    FROM stars
                                                                    WHERE person_id =
                                                                                    (SELECT id
                                                                                    FROM people
                                                                                    WHERE name = 'Kevin Bacon' AND birth = '1958'))
ORDER BY name ASC;