clear
echo "#########################################"
echo "####          EXPERIENCIA 1          ####"
echo "#########################################"
echo
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 2          ####"
echo "#########################################"
echo
ifconfig eth0 172.16.31.1/24
echo "Configurado o tux 2 com o ip 172.16.31.1"
read -p "Configurar a vlan 30 e 31 para continuar ..."
wireshark&
read -p "Pressione 'Enter' para pingar broadcast..."
ping -b -c 4 172.16.31.255
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 3          ####"
echo "#########################################"
echo
read -p "Pressione 'Enter' para adicionar o tux4 a tabela de routing..."
route add default gw 172.16.31.253
echo
read -p "Pressione 'Enter' para pingar tux1..."
ping -c 4 172.16.30.1
echo
route -n
echo
read -p "Pressione 'Enter' para apagar as tabelas ARP dos tuxs..."
arp -d 172.16.31.253
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 4          ####"
echo "#########################################"
echo
route add default gw 172.16.31.254
echo "Adicionada a rota para o Rc"
read -p "Pressione 'Enter' para eliminar a rota para o Tux4"
route del default gw 172.16.31.253
echo "Removida a rota para o tux4"
read -p "Pressione 'Enter' para limpar a tabela de arp's"
arp -d 172.16.31.253
arp -d 172.16.31.254
echo "Tabela Limpa"
wireshark&
read -p "Pressione 'Enter' para adicionar a rota para o Tux4"
route add default gw 172.16.31.253
route del default gw 172.16.31.254
read -p "Pressione 'Enter' para limpar a tabela de arp's"
arp -d 172.16.31.253
arp -d 172.16.31.254
echo "Tabela Limpa"
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 5          ####"
echo "#########################################"
echo
read -p "Pressione enter para adicionar o servidor DNS 'lixa.netlab.fe.up.pt' ao tux 2"
echo "search lixa.netlab.fe.up.pt \n nameserver 192.168.109.2" > /etc/resolv.coonf
read -p "Pressione 'Enter' para pingar o Google..."
ping -c 4 google.com

