## Hi Data Team Coders!

This is our code repository, and this file is the readme that gets displayed on our github page.

## How do I compile/run the code?

1. Clone the repository. Open a terminal in your desktop (or wherever you want the folder to be). Type

```
git clone https://github.com/ForrestFire0/RobotCode.git
``` 

and press enter.

2. Open the folder (RobotCode) and the open the folder libraries.
3. Copy the folder called helpers and slap that into `/Documents/Arduino/Libraries`
4. Open the file `/RobotCode/Richaron/CommsTest/CommsTest.ino` in the Arduino IDE. Don't edit it quite yet, though.

## How do I edit the code?

1. Follow steps 1-3 of compiling and running the code.
2. Create a new branch. A branch is kind of like your own copy of everything that you can edit. Do this by typing

```git checkout -b forrests_branch```
<br>*Note: Change forrests_branch to include your name.*

3. You are now on your own branch. Now make edits to the code.

## How do I save my edits?

1. `git add .` - this will add any new files and folders
2. `git commit -m "Summary Of Changes"` - This will take a snapshot of what the repo looks like. Change "Summary of
   changes" to an actual summary of your changes.
3. `git push` - pushes (uploads) your code to the server.



The repo (repository, aka main folder) consists of two folders. They each have arduino sketches in them.
<br>*Remember, an arduino sketch must be in a folder of the same name.*