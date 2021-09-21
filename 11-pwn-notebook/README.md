# Challenge #11 - Notebook

Category: `pwn`

## Story

>Wow, it’s a crowded day at Heathrow, lots of suits that bump into each other and try to catch their plane. You have to find the gate to the secret warehouse, it cannot be far away. You see a suspicious suit go into a fast food court and you spot him disappear behind the checkout. Hmmm, odd?! You follow, and when no one sees you follow him. You go through a desolated kitchen, it stinks, you cover your nose with the back of your hand. You pass through a small entrance, and enter the secret warehouse, wow, it’s vast!<br/><br/>
>Please help me restore my deleted note.

## Solution

This challenge comes with a URL and a port. We can connect to it with [netcat](https://en.wikipedia.org/wiki/Netcat) (see [connect.sh](connect.sh)]):

```sh
$ nc pwn-notebook.2021.ctfcompetition.com 1337
```

It also comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O notebook.zip https://storage.googleapis.com/gctf-2021-attachments-project/6c96641ce301c1cce0638c706ce6f08e03dd07a7206f13502814948b87956797cbfab4e5319df21bc2bed99834bd7aede661f86a8a0d5c7148c3158d566afc68
$ unzip notebook.zip
Archive:  notebook.zip
 extracting: notebook
```

Let's look at the files and see what we're dealing with.

TODO
