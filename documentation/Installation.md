@page "Downloading / Compiling AVOE"


# Downloading AVOE

## Getting Latest Version on Github

Before compiling latest version of AVOE it is advised to get the latest version

### First time Downloading?

AVOE can be cloned from the git repository from this command
```
git clone https://github.com/URI-Hydrobotics-Team/AVOE.git

```


### Already Downloaded?

Go into the repository on the command and type the following command

```
git pull

```

This will ensure that the latest version of the repository is updated.

# Compiling AVOE

AVOE is compiled via a ` bash ` script 

## Before Compiling

Ensure you have the following Dependencies

```
- gcc/g++
- make and cmake (for cmake build option)
- libc6-dev
- linux-headers
```

## Compiling with Bash
Make sure you are in the core directory in the AVOE repository
``` ~/AVOE/core/ ```
to compile enter the following command see below for the options 
``` ./build.sh <option> ```
### Compilation options

There are options when you compile 

| Option  | Description |
|---------|-------------|
| virtual | compiles program using dummy data|
| virtual_verbose| Similar to virtual with verbose debug messages|
| virtual_g| Builds virtual target with the Address Sanitizer|
| physical | Builds the physical AVOE target with real world data|


