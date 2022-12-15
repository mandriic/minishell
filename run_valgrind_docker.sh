#!/bin/bash
# echo "Create <1> or <2> to connect\n"
read -p "Create <1> or <2> to connect => " num
# read var
# if [ $var -eq 1 ]
# then
case $num in
[1]* )ssh-keygen -f id_rsa_shared
	docker stop $(docker ps -a -q)
	# docker rm $(docker ps -a -q) #!!!!! ALERT !!!!Elimina todos containers
	# docker rmi $(docker image list) #!ATTEEEENCION!!!! elimina imagenes
	#docker build -t minishell . 
	docker build -t test_ssh . 
	docker run -v $PWD/:/home/sshcls/mounted -itd -p 2222:22 test_ssh 
	sleep 2 
	ssh -i id_rsa_shared sshcls@localhost -p 2222;;
# else
[2]* )ssh -i id_rsa_shared sshcls@localhost -p 2222;
# fi
esac


# docker run -v $PWD/:/home/sshcls/mount -itd -p 2222:22  mandriic/minishell #esta montamdo carpeta con minishell en /home/mount
# sleep 3
# ssh sshcls@localhost -p 2222 
# pass 12345/home/sshcls/
