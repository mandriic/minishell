#!/bin/bash
cat /home/sshcls/.ssh/id_rsa_shared.pub >> /home/sshcls/.ssh/authorized_keys
chmod 600 /home/sshcls/.ssh/authorized_keys
chown -R sshcls:sshcls /home/sshcls/.ssh/
service ssh start
service vsftpd start

/bin/bash
