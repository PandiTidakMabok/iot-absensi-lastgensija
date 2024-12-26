<h1 align="center">Mesin Absensi berbasis NodeMCU dan web dashboard</p>

## Software

Kelompok software mengerjakan bagian tampilan web dan logika server untuk menampilkan data dari database

#### Prerequisted

- [Laragon](https://laragon.org/)
- [Visual Studio Code](https://code.visualstudio.com/)

## Hardware

Kelompok hardware mengerjakan bagian mesin absensi menggunakan mikrokontroller NodeMCU

#### Prerequisted

- [NodeMCU ESP8266](https://www.amazon.com/HiLetgo-Internet-Development-Wireless-Micropython/dp/B010O1G1ES/ref=sr_1_5?crid=301SLTDS3NDQM&dib=eyJ2IjoiMSJ9.4xEr54v6vHUSws_RbogXUaZGKvfd4sn0xSV9GgtI44aw8FIOjQt1hrjrlj680AjLIaM899uDmhlmtGybWH2uoADRt5iXWMr2_tnFPpSifTG9ovmwSGnVUex8MMD9t79dEwBFTsiIj3cWu1pmK8AdIVB2unEKmnY2GPf8TPJuQl4thlzfRW02GstLmLFSm_9k_YszIbxUkP-oZLLwvC5YoACQmUbKn7D_BUGJFi-7M0k.qQ5k667ccQ8t2Nb-P26PgqgirqIoF_5BC_oczIRUxvI&dib_tag=se&keywords=nodemcu+esp8266&qid=1735100959&sprefix=nodemcu+esp8266%2Caps%2C325&sr=8-5)
- [Cable USB A to USB Micro](https://www.amazon.com/Charging-Android-Charger-Samsung-Devices/dp/B0BLL6QW4T/ref=sr_1_16?crid=2OWJJNORFFXF&dib=eyJ2IjoiMSJ9.kiS5XOtRRLEfmRbK_dU0W7ZSANgpB8V9J95sVMjcd0cjrymLzwUuZo0qjsP3AoIBbcZCATI4a3-uzGQg88TTpsVub_Vmsg7zqcXGYiz4-Eg3zXdbJmFSrnVL9JhrwPITwBkZhTn1R_x5-LkMV3Fo5HdM3Q1EemZvBa1LHd89DwykNGV9Utt4YaaJW53D-3Ch-ZWQwzLdt4kUsv5tlcV9gK2B5uG9UI_vvh1Kie25XrM.XlXDc0HzxlqM2m_CStbps8vEBi0G9d9ZL1HI62q4McY&dib_tag=se&keywords=usb+a+to+micro&qid=1735101014&sprefix=usb+a+to+micr%2Caps%2C336&sr=8-16)
- [PCB Board](https://www.amazon.com/ELEGOO-Prototype-Soldering-Compatible-Arduino/dp/B072Z7Y19F/ref=sr_1_3?crid=3HXXUR8UFQPCX&dib=eyJ2IjoiMSJ9.cFO3IbuqDHBg13mO-bkEuPUwa_xXnLSggleH0XvSIPRP3H1MdjmIHErOmLRbqESbiUR-PibG281cxobffKjzeCrw00ARE0CCLVUbWQt5uzybs6YD5qHLzFklO9AZj__XATD1pTd0-6pIVb_2f5b3Rcuw6aDOLKjjahm_dm2oZAOd8nZNg_v0BX7rqJKU2uNFux578pMdCuIAojNq7LfvLODr2D3W6Jcj3ygiHGIdX-U.RiUz71UiQRnWtpNTWKlo-eP3hk0_AIyJF9tyQIRLIYE&dib_tag=se&keywords=pcb&qid=1735101049&sprefix=pcb%2Caps%2C311&sr=8-3)
- [2 LED](https://www.tokopedia.com/cncstorebandung/paket-1-box-led-5mm-3mm-5-color-rgbyw-100pcs?extParam=src%3Dshop%26whid%3D15512&aff_unique_id=&channel=others&chain_key=)
- [LCD I2C 20x4](https://www.amazon.com/SunFounder-Serial-Module-Arduino-Mega2560/dp/B01GPUMP9C/ref=sr_1_9?crid=PPQ1T8TB8HG&dib=eyJ2IjoiMSJ9.QYeVwCp156qlqD4Ok4gFqWWjIxnYMeUdaVJ2laWA9mcElNpCcU1AUmrRKytJHOug-Fcx17Mij1ABR-R7vOdkz7Gat8saFv1gGtiuwIQRvbeM2WdLGtJbpCQZjfezcvldrLCIcMZ0X5HXCTbMNp2WDZtFBCFPm2jyQfyvtnDXktzKg8L-LyvC9H5ESnRQMy9G2AB_nHjS_nWx3A-qhYe2HQL3Njdlr1EiSZSr16bjZUU.GxJ8xu3sVcwm4UAXcuDx8iBDHU-mrQk2Km9kDUhReq8&dib_tag=se&keywords=lcd+i2c&qid=1735101247&sprefix=lcd+i2%2Caps%2C447&sr=8-9)
- [Buzzer](https://www.tokopedia.com/cncstorebandung/cnc-buzzer-speaker-active-3v-3-3v-12x9-5mm-for-arduino-uno-mega-mini?extParam=src%3Dshop%26whid%3D15512&aff_unique_id=&channel=others&chain_key=)
- [Jumper Cables](https://www.tokopedia.com/cncstorebandung/40pcs-kabel-jumper-cable-40cm-male-male-female-female-male-female-female-t-female-3e81c?extParam=src%3Dshop%26whid%3D15512&aff_unique_id=&channel=others&chain_key=)
- [Arduino IDE](https://www.arduino.cc/en/software)
- [Driver CH340](https://www.arduined.eu/ch340-windows-10-driver-download/)
- [Node.Js LTS](https://nodejs.org/en)
- [Node-RED](https://nodered.org/docs/getting-started/local)
- [Laragon](https://laragon.org/)

## Catatan

Repository ini hanya dikelola oleh anggota dari kedua kelompok yang memiliki kemampuan, baik dari segi hardware maupun software **(bukan beban)**
