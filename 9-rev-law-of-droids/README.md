# Challenge #9 - Law of Droids

Category: `reversing`

## Story

>Johannesburg is hot, and you are on your way to the secret lair. It seems like it is well fortified, even though you are expected under the alias of the assassin, perhaps it will be a better idea to sneak inside the lair, unseen? You climb up on a brick wall, and jump over it. On the other side you spot a lot of guards, quick, hide in a bush. Now you have to sneak past the guards into the main building's entrance.<br/><br/>
>In this challenge, you have to find the flag using memory forensics. Good luck! Note, surround the flag with CTF{...} to submit it. Note, API Level 25 is what you're looking for.

## Solution

This challenge comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O law-of-droids.zip https://storage.googleapis.com/gctf-2021-attachments-project/06f923cd67e28af3d409ff78fd8385ae6457f4ea153a827e9a39c57293b7832e5064e75b4c48c1ac95bd62504a495258a04baec89e813eba7758fb88db329ca8
$ unzip law-of-droids.zip
Archive:  law-of-droids.zip
 extracting: bzImage
 extracting: bzImage.elf
 extracting: bzImage.elf.i64
 extracting: gCTF.apk
```

*Note: Unfortunately, I can't include the `law-of-droids.zip` file here as it exceeds GitHub's file size limit of 100.00 MB*

Let's look at the files and see what we're dealing with.


