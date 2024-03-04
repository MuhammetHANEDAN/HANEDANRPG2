#pragma once

/*

Ejderhaya binmeyi yap bunun için stateler ayarla1
karakter için riding state oluşturmak lazım 1
Ejderhaya attachlenme yuvası ayarla 1
ejderhaya attachlendiğinde sorun ortaya çıkıyor ejderha kamerasına geçmiyor collisionlar çarpıiıyor olabilir denedik1
çözemedik 1 

ejderhadan inebilmek için ejderhanın yerde olması lazım.1
ejderha için anim bp1
interact interfacesi ayarla 1
ejder için intercatı ride fonksiyonu yap1

baseitem 1
item için struct1
baseweapon1
basweapon için struct1



karakter için 2 enum var karakter eline silah alırken CharacterActionState equipped yapılacak anim bitince unocupied e dönecek
sonrasında equiplediği zaman silahı silahın sınıfına göre EquippedWeaponStyle enumu o sınıfa setlenecek silahı unequip yapıncada
EquippedWeaponStyle none a setlenecek unutma

--------------sonra yapılacaklar-------------
hedefe kitlenme için animbp ye gidecek olan direction infosunu c++ dan setle blendspacesine eklemek lazım

greatsword blendspacesi çalışmıyor artı greatsworddan none ye geçince default bs de çalışmıyor


-------------------KABULLER----------------------
--Karakter için tüm state checkler direk karakter sınıflarının içinde check edilecek.

----------------INFOS---------------------------------

//Skilleri ve vuruş animlerini direk silahın içindeki weapon struct içine koyuyuorum.

//karakterdeki State için enumlar------

hanedanrpg3 baseclasstadır

EActionStates CharacterActionState=EActionStates::Eas_Unocuppied;
EWeaponType WeaponType=EWeaponType::Ewt_None;

//karakter yürüme hızları----

walk 250
run 500
sprint 700
backward -250

//Character State Changes Adress ----
bisweapononhand boola dikkat et .
RideagbleDragon.cpp 137

//EN SON
en son yanlış bi sistem yaptık galiba animnotify kullanmadan yardırdık equip için :D




















 */
