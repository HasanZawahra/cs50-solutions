SELECT title FROM movies
JOIN stars
ON movies.id = stars.movie_id
JOIN people
ON stars.person_id = people.id
WHERE name = 'Johnny Depp'
AND movies.id IN (SELECT movie_id FROM stars
WHERE person_id = (SELECT id FROM people
WHERE name = 'Helena Bonham Carter'));
