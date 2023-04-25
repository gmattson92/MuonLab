#! /bin/bash

echo 'sudo udevadm control --reload-rules'
sudo udevadm control --reload-rules
echo 'udevadm trigger'
udevadm trigger
