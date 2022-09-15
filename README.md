# D&D Combat Program

## Description
This program allows you to perform D&D combat on your computer with two groups of player characters
(monsters not yet implimented). Simply input each character's info or files containing their info to
start and say what you want each character to do when prompted. The program will do all the rolling
and math for you!

> Note: When prompted for multiple pieces of info, seperate each with a space

## Running the Program
After you've made the prgram (`make Combat`), you can run it with no arguments (`./Combat`) and
it will ask you to enter information for each character manually. If you would rather input files
containing this info, you can do this through command line arguments. The format is:

> `./Combat [# in Group 1] [# in Group 2] [character files]`

Enter Group 1's files first followed by Group 2's. The format of these character files must be:

> \[character name]
>
> \[class] \[level]
>
> \[stats] (each seperated by a space)
>
> \[HP] \[AC] \[speed]
>
> \[weapon]

Using this method allows you to skip having to enter each character's info each time you run the program.

## Not yet Implemented Features
- Subclasses
- Conditions
- Monsters (to fight instead of other PCs)
- Non-instantaneous spells
- Non-damaging spells
- Spell secondary effects