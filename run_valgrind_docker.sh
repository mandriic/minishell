#!/bin/bash
docker stop $(docker ps -a -q)
docker rm $(docker ps -a -q) #!!!!! ALERT !!!!Elimina todos containers
#docker rmi $(docker image list) #!ATTEEEENCION!!!! elimina imagenes
#docker build -t minishell . 
docker run -v $PWD/:/home/sshcls/mount -itd -p 2222:22  mandriic/minishell #esta montamdo carpeta con minishell en /home/mount
ssh sshcls@localhost -p 2222 
# pass 12345/home/sshcls/
