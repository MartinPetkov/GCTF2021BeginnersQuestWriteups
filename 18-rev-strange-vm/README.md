# Challenge #18: Strange Virtual Machine

Category: `rev`

## Story

>You press a button and enter through a tinted glass door. There is a vast oil painting on the wall that depicts a bold man with a scar under his left eye, under his arms rests a white chubby cat. Below the painting is the very same man, and he’s addressing you: "Well, well, well. Isn’t it the trouble maker? Huh, how did you get past the guards? Well, I have a final offer for you. I’ll let you live only on one condition: START WORKING FOR ME! BWAHAHAHAHA-" While he goes on with his monologue about conquering the world and some twisted philosophy about how he is actually the good guy and so on you start discretely fiddling with a control panel labeled "Self destruction". You need to quickly figure out the activation code while he’s distracted.<br/><br/>
>Everyone is coming up with their own programming language these days, so I came up with my own architecture. You can use it to run the attached program that will print the flag for you.

## Solution

This challenge comes with a download link. Let's fetch it and examine it:

```sh
$ wget -O strange-vm.zip https://storage.googleapis.com/gctf-2021-attachments-project/c48931b8e0b86e44cc5bcc08b9e1510d05f0bb0cde039c2e96147379fcb88d2f93a9acac37bd7093a92e7fdadce862835fadc0951d76bccbc8afd055ae736099
$ unzip strange-vm.zip
Archive:  strange-vm.zip
 extracting: vm-impl.tgz
 extracting: vm.rom
```

Let's look at the files and see what we're dealing with.

TODO
