# centric


запросы:

1

  SELECT a.name,a.gdp, b.name, b.gdp
  FROM Countries as a JOIN (Select names, gdp From countries as b WHERE b.continent LIKE 'Europe') ON a.gdp > b.gdb
  WHERE a.name NOT LIKE 'Europe'
 
2

  SELECT continent,COUNT()
  FROM  Countries
  WHERE population >= 10000000
  GROUP BY continent 
		
3
 
  SELECT continent
  FROM Countries 
  GROUP BY continent HAVING AVG( gdb)  > ( SELECT AVG(gdb) FROM  Countries)

 
