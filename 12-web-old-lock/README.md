# Challenge #12 - Old Lock

Category: `web`

## Story

>Boy this has been a tough journey, you had luck that you entered a box that contained some food. You hear foul voices and feel that some people pick up your box, and carry it to another place. When the voices disappear, you take the chance to escape. You have successfully arrived in Singapore. You find a peaceful café, order a cup of tea and charge your cell phone. PLING, you’ve received another text message from the boss: "I pretend that I don’t know where you are, but I do. You’ll have to forgive me, but I’ve had a tracker on you all the time. You have finally reached Singapore, find "M/S. Revenger" and sneak onboard, it will take you to our enemy's hidden island, make it quick, the ship is leaving the harbor soon, I count on you AGENT!." Look, overthere "M/S Revenger", you have to get closer! Hmm, but it seems quite guarded. You will have to swim! You go away from the ship and dive into the warm and clear water. It’s nice to go for a swim but you would have preferred it to be under more relaxed circumstances. You swim slowly towards the ship, finally you reach it, climb up on the side of it and in through a window. You find yourself in a cabin with locked doors. Thankfully, it's an electronic lock.<br/><br/>
>You're not sure what metal the keypad was made of, but either it was very soft, or whoever punches in the code has waay too much strength in their fingers. This also means you're in luck, since it's pretty obvious which digits are actually used in the 5-digit code. The order is unknown, but there can't be that many possibilities, right? Note: Online brute forcing is allowed in this task.

## Solution

This challenge comes with a URL: https://old-lock-web.2021.ctfcompetition.com/

Let's visit it and see what we're dealing with.

There's a keypad with some clearly worn-out buttons.

![Keypad with worn out buttons 3, 5, 7, 8 and 0](old_keypad.png)

There are also some instructions.

![Instructions to try a 5-digit code](instructions.png)

This seems pretty straightforward. It says it's a 5-digit code and there are 5 buttons worn out, so we just need to generate and try all the [permutations](https://en.wikipedia.org/wiki/Permutation) of `35780` (see [solve.sh](solve.sh)). This is easy to do because the webpage simply submits a form with the `v` parameter.

```sh
#!/bin/bash

# Generate permutations.
permutations=($(python -c 'from itertools import permutations; print("\n".join(["".join(perm) for perm in permutations("35780")]))'))


# Try them out.
for perm in ${permutations[@]}; do
  echo -n "Checking ${perm}... "
  body="$(curl -s -X POST -F "v=${perm}" https://old-lock-web.2021.ctfcompetition.com/)"
  if echo -ne "${body}"| grep -q 'Hmm no'; then
    echo 'WRONG'
  else
    echo 'RIGHT'
    echo -ne "${body}" | grep -o 'CTF{.*}'
    exit 0
  fi
done

exit 1
```

Running this quickly gives us the flag.

```
CTF{IThinkWeNeedToReplaceTheKeypad}
```
