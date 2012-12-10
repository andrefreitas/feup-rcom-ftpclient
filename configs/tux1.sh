clear
echo "#########################################"
echo "####          EXPERIENCIA 1          ####"
echo "#########################################"
echo
ifconfig eth0 172.16.30.1/24
echo "Configurado o tux 1 com o ip 172.16.30.1"
read -p "Pressione 'Enter' para pingar tux4..."
echo
ping -c 4 172.16.30.254
read -p "Pressione 'Enter' para continuar..."
echo
route -n
echo
arp -a
echo
arp -d 172.16.30.254
echo
wireshark&
read -p "Pressione 'Enter' para pingar tux4..."
ping -c 4 172.16.30.254
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 2          ####"
echo "#########################################"
echo
read -p "Configurar a vlan 30 e 31 para continuar ..."
wireshark&
read -p "Pressione 'Enter' para pingar tux4..."
ping -c 4 172.16.30.254
echo
read -p "Pressione 'Enter' para pingar tux2..."
ping -c 4 172.16.31.1
echo
wireshark&
read -p "Pressione 'Enter' para pingar broadcast..."
ping -b -c 4 172.16.30.255
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 3          ####"
echo "#########################################"
echo
read -p "Pressione 'Enter' para adicionar o tux4 a tabela de routing..."
route add default gw 172.16.30.254
echo
read -p "Pressione 'Enter' para pingar tux2..."
ping -c 4 172.16.31.1
echo
route -n
echo
wireshark&
read -p "Pressione 'Enter' para pingar '172.16.30.254'..."
ping -c 4 172.16.30.254
echo
read -p "Pressione 'Enter' para pingar '172.16.31.253'..."
ping -c 4 172.16.30.254
echo
read -p "Pressione 'Enter' para pingar '172.16.31.1'..."
ping -c 4 172.16.31.1
echo
read -p "Pressione 'Enter' para apagar as tabelas ARP dos tuxs..."
arp -d 172.16.30.254
echo
read -p "Pressione 'Enter' para pingar o tux 2..."
ping -c 4 172.16.31.1
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 4          ####"
echo "#########################################"
echo
read -p "Pressione enter depois de começar a configuração das rotas"
read -p "Pressione 'Enter' para pingar '172.16.30.254'..."
ping -c 4 172.16.30.254
read -p "Pressione 'Enter' para pingar '172.16.31.1'..."
ping -c 4 172.16.31.1
read -p "Pressione 'Enter' para pingar '172.16.31.254'..."
ping -c 4 172.16.31.254
read -p "Pressione 'Enter' para pingar '172.16.31.1'..."
ping -c 4 172.16.31.1
read -p "Pressione 'Enter' para fazer traceroute para o '172.16.31.1'..."
traceroute 172.16.31.1
read -p "Pressione 'Enter' para fazer traceroute para o '172.16.31.1'..."
traceroute 172.16.31.1
read -p "Pressione 'Enter' para pingar '172.16.1.254'..."
ping -c 4 172.16.1.254
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 5          ####"
echo "#########################################"
echo
read -p "Pressione enter para adicionar o servidor DNS 'lixa.netlab.fe.up.pt' ao tux 1"
echo "search lixa.netlab.fe.up.pt \n nameserver 192.168.109.2" > /etc/resolv.coonf
read -p "Pressione 'Enter' para pingar o Google..."
ping -c 4 google.com




