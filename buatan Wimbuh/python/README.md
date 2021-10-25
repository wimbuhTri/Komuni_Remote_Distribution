untuk menggunakan aplikasi server ini ganti terlebih dulu global variabel (yang ditulis menggunakan ALL CAPITALS) dengan credential influxDB yang sudah dibuat. Pastikan instance aplikasi ini daoat terkoneksi dengan sevice InfluxDB target. Bila menggunakan cloud influxDB pastikan machine dapat terhubung ke cloud service, bila menggunakan influxDB di dalam jaringan lokal, pastikan aplikasi bisa mengubungi instance influxDB.

Sesuaikan topic MQTT yang disubscibe, samakan dengan topic yang di publih oleh ESP8266
Pahrsing dan preprocesing data dapat dilakukan di function on_message(). Manipulasi variabel sting_telemeti sebelum method Querying_Job() dipanggil.

Program ini menggunakan multiprocessing dengan implementasi library untuk mengindari I/O bottleneck.
Module pada aplikasi ini tidak dipanggil pada main-app. Jalankan script bernama relay_point.py untuk memulai aplikasi. nstal dependecy telebih dahulu sebelum mengeksekusi program.