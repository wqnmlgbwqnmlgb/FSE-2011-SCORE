
# Instructions for building VM
This folder contains the files needed to build a virtual machine for SCORE using Vagrant.
***

#### Contents:

1. **Vagrantfile** - This will load the Ubuntu 14.04 Desktop VM on VirtualBox.
2. **script.sh**  - The script that will install all the requirements for the tool to run.

#### Requirements:

1. [Vagrant](https://www.vagrantup.com/downloads.html). 
2. [VirtualBox](https://www.virtualbox.org/wiki/Downloads).

#### Installation Steps:
1. Download and install [Vagrant](https://www.vagrantup.com/downloads.html).
2. Download and install [VirtualBox](https://www.virtualbox.org/wiki/Downloads).
3. Clone [this repository](https://github.com/SoftwareEngineeringToolDemos/FSE-2011-SCORE) to your system.
4. Open command prompt/terminal and navigate to the _build-vm_ directory.
5. Run the command "_vagrant up_" to set up and launch the VM. A VirtualBox VM should be launched, as the GUI option has been enabled in Vagrant.
6. For the first launch, allow the provisioning tasks to complete execution. These will install the required software for SCORE.

#### Provisioning:

1. Ubuntu Desktop 14.04.
2. gcc packages
3. OCaml
4. make

#### Username and Password

* username: *vagrant*
* password: *vagrant*
* 

#### Acknowledgement

* https://docs.vagrantup.com/v2/provisioning/shell.html
