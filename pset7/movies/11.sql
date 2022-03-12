-- write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated
SELECT title
FROM movies
INNER JOIN stars ON movies.id = stars.movie_id AND stars.person_id =
                                                                    (SELECT id
                                                                    FROM people
                                                                    WHERE name = 'Chadwick Boseman')
INNER JOIN ratings ON ratings.movie_id = stars.movie_id
ORDER BY rating DESC, title ASC
LIMIT 5;