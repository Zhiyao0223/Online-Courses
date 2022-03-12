-- write a SQL query that lists the names of any songs that have danceability, energy, and valence greater than 0.75
SELECT DISTINCT name
FROM songs
WHERE energy > 0.75 AND valence > 0.75 AND danceability > 0.75;