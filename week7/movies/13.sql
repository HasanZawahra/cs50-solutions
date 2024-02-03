SELECT distinct(name) FROM people
JOIN stars
ON people.id = stars.person_id
JOIN movies
ON stars.movie_id = movies.id
WHERE movies.id IN (SELECT movie_id FROM stars
WHERE stars.person_id == (SELECT id FROM people
WHERE people.birth == 1958
AND people.name == 'Kevin Bacon'))
AND people.name != 'Kevin Bacon';
