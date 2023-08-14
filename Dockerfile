FROM debian
RUN apt update && apt install -y openssh-server\
    && apt install -y sudo && apt install nano\
    && apt install net-tools && apt install -y vsftpd\
    && apt install -y gcc && apt install -y make && apt install -y zlib1g zlib1g-dev traceroute valgrind git
RUN useradd -m -p '$1$M0Ld1W6K$V6mxfJ3LBT71EE/V3.0cX/' -s /bin/bash sshcls
RUN usermod -aG sudo sshcls
COPY id_rsa_shared.pub /home/sshcls/.ssh/
COPY script.sh /home/sshcls
# RUN apt install -y libreadline6 libreadline6-dev
RUN apt --no-install-recommends install -y libreadline6-dev
# RUN make test
WORKDIR /home/sshcls/
RUN chown -R sshcls:sshcls /home/sshcls/*
RUN chmod +x script.sh
# RUN echo "sshcls:yoquese" | chpasswd
CMD /home/sshcls/script.sh
WORKDIR /home/

# docker build -t minishell . 
# docker run -v $PWD/:/home/sshcls/mount -itd -p 2222:22  minishell
# ssh sshcls@localhost -p 2222 
# pass 12345
