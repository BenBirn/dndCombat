# D&D Combat Program

## Description
This program allows you to perform D&D combat on your computer with two groups of player characters
(monsters not yet implimented). Simply input each character's info or files containing their info to
start and say what you want each character to do when prompted. The program will do all the rolling
and math for you!

> Note: When prompted for multiple pieces of info, seperate each with a space

## Running the Program
After you've made the program (`make Combat`), you can run it with no arguments (`./Combat`) and
it will ask you to enter information for each character manually. Alternatively, you can use files
containing the character information to skip having to enter their info each time you run the program.
The format of these character files must be:

> \[character name]  
> \[class] \[level]  
> \[stats] (each seperated by a space)  
> \[HP] \[AC] \[speed]  
> \[weapon]

There are example character files provided in this repository as a model. To use these files in the
program input, you can use command line arguments in the following format:

> `./Combat [# in Group 1] [# in Group 2] [character files]`

Enter Group 1's files first followed by Group 2's. For example, a 1v1 using the two example character
files would be:

> `./Combat 1 1 wizard.txt monk.txt`

## Not yet Implemented Features
- Subclasses
- Conditions
- Monsters (to fight instead of other PCs)
- Non-instantaneous spells
- Non-damaging spells
- Spell secondary effects