#### Contents 

1. **Vagrantfile** - That will load the Ubuntu 14.04 Desktop VM on VirtualBox.
2. **script.sh**  - The script that will install all the requirements for the tool to run.

#### Requirements:
2. [Vagrant](https://www.vagrantup.com/downloads.html). 
3. [VirtualBox](https://www.virtualbox.org/wiki/Downloads).

#### Steps:

1. Copy the Vagrantfile and the script.sh in your working directory.
2. Through the command prompt open the directory where the two files are copied.
3. Type the folowing command:
 ```
 vagrant up --provider virtualbox
 ```
This will install the required softwares.

#### Following is installed through the script

1. Ubuntu Desktop 14.04.
2. gcc packages
3. OCaml
4. make

#### Username and Password

* username: *vagrant*
* password: *vagrant*
