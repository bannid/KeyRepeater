# KeyRepeater
This simple utility program helps to turn given keys to turbo mode and can also be used to map keys in Windows.

# Motivation
I sometimes play https://agar.io game, where I am required to press 'w' repeatedly all the time.  I tried to look for some key repeater utilities online, however, could not find any.  Therefore, I decided to write my own. While I was writing the key repeater utility, I figured that sometimes I want to play some games with arrows insted of using 'w', 'a', 's', 'd' keys to move, therefore, I decided to write the key mapping capability in this program as well.  I am aware that there are some software that can do the key mappings by editing the registeries, however I prefer to run a small program each time I want to enable the key mappings.

# How to build
### Build requirements
1. You need to have cl installed on your computer.
2. vcvar64.bat file should be run to setup the development environment.

### Build
1. Clone this repository into your computer.
2. Open the command prompt
3. Navigate to the folder where you have cloned this repository.
4. Run releaseBuild.bat.
5. The executable should be outputted in 'KeyRepeater' directory inside the folder where you cloned this repository.

# How to use
Using this utility program is simple - 
1. First go to https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes to get the hex codes for the interesetd keys. Ie. for 'w' its 0x57
2. Create .config file or copy from this repository.
3. For the keys you want to put into repeating mode, put the hex code inside turboList inside .config file like following:
```
        turboList{
            0x57
            0x59
        }
```
4. For key mappings, use the following syntax:
```
        keyMappings{
            0x51:0x57
        }
```
5. You can disable the program at anytime by pressing Alt + f9.
# Performance
This utility program is very small executable and only depends on WIN32_API.  I have tested this program on Windows 10 Home and it runs extremely efficient.

# TODO List
-- Write now the mappings only works for Individual keys and System Keys ie. Alt + f4 are ignored.
-- Make the disable key ie. Alt + f9 configurable, so a user can set that key inside the .config file as well.
