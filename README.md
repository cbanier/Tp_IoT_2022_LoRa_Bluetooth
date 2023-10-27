# Tp_IoT_2022_LoRa_Bluetooth

**[Corentin Banier](https://github.com/cbanier/) et [Yousri Lajnef](https://github.com/ylajnef)**

~~## 1. Client :~~
 
~~### 1. Récupération d'un paquet Mqtt sur test.mosquitto.org :  nomAP/ipaddr~~

~~### 2. Se connecter à une carte sur l'AP et faire une requete http donnant les valeurs nécessaire à LoRa.~~

~~### 3. Ecouter les données de LoRa.~~

## 2. Serveur :
*Implémentation dans [tpLoRa.cpp](/tpLoRa.cpp)*

Détails du code :
1. Envoyer paramètres LoRa au Client via un paquet Mqtt sur test.mosquitto.org: /info/youssance .

2. Écouter en LoRa.

3. Réceptionner un paquet LoRa et l'afficher.

~~## 3. Ensuite...~~

~~### 1. Ajouter une fonction permettant de switcher entre Serveur et Client~~

~~### 2. Sur le serveur, échangez la partie LoRa par du bluetooth (ou BLE)~~

~~### 3. Refaire la partie cliente pour répondre au bluetooth~~