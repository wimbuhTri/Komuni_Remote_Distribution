komuni1 sudah ditambahkan function untuk berkomunikasi ke ESP8266 via SerialPort.

Format payload :
"parameter:value"
Payload dikirmkan ke ESP8266 dan di-relay-kan via MQTT client ke server python

Sesuaikan baudrate dan delay agar data yg masuk dan diterima tidak corrupt. 

NOTE:
menggunakan jumper kualitas buruk untuk menguhungkan Serial pin Ardu Mega ke ESP8266 berakibat payload degradation yang disebabkan oleh byte-flip khususnya untuk payload dengan karakter yang banyak. Solusinya adalah dengan menghubungkan kedua board dengan PCB (mempersingkat koneksi fisik -> degradasi payload berkurang)