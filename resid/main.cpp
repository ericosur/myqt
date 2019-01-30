#include <QCoreApplication>
#include <QDebug>
//#include <iostream>

#include "residutil.h"
#include "strdef.h"

//using namespace std;

void test_id(int id, const QString& strid)
{
    QStringList locs;

    locs << "ar_AE" << "en_US";

    QString str;
    foreach (const QString &loc, locs) {
        str = getStringByIntid(loc, id);
        qDebug() << "query:" << id << "return:" << str;
        str = getStringByStrid(loc, strid);
        qDebug() << "query:" << strid << "return:" << str;
    }

}

void test()
{
    qDebug() << getStringByStrid("es_MX", "stringid_plzconnectbt");
    qDebug() << getStringByStrid("ar_AE", "stringid_plzconnectbt");
#if 1
    qDebug() << getStringByIntid("ar_AE", STRING_MINSTRID-1);
    qDebug() << getStringByIntid("ar_AE", STRING_MINSTRID);
    qDebug() << getStringByIntid("ar_AE", STRING_MAXSTRID);
    qDebug() << getStringByIntid("ar_AE", STRING_MAXSTRID+  1);
    //findFileLocation("abc");
    test_id(9999999, "stringid_nosuchidexists");
    test_id(stringid_plzconnectbt, "stringid_plzconnectbt");
#endif
}

void test_cache()
{
for (int i = 0; i < 3; i++) {

qDebug() << "=====> repeat:" << i;

qDebug() << getStringByStrid("en_US", "stringid_homepage");
qDebug() << getStringByStrid("en_US", "stringid_ipod");
qDebug() << getStringByStrid("en_US", "stringid_usb");
qDebug() << getStringByStrid("en_US", "stringid_miracast");
qDebug() << getStringByStrid("en_US", "stringid_hdmi");
qDebug() << getStringByStrid("en_US", "stringid_aux");
qDebug() << getStringByStrid("en_US", "stringid_usbipod");
qDebug() << getStringByStrid("en_US", "stringid_btaudio");
qDebug() << getStringByStrid("en_US", "stringid_disc");
qDebug() << getStringByStrid("en_US", "stringid_setup");

qDebug() << getStringByStrid("pt_BR", "stringid_homepage");
qDebug() << getStringByStrid("pt_BR", "stringid_ipod");
qDebug() << getStringByStrid("pt_BR", "stringid_usb");
qDebug() << getStringByStrid("pt_BR", "stringid_miracast");
qDebug() << getStringByStrid("pt_BR", "stringid_hdmi");
qDebug() << getStringByStrid("pt_BR", "stringid_aux");
qDebug() << getStringByStrid("pt_BR", "stringid_usbipod");
qDebug() << getStringByStrid("pt_BR", "stringid_btaudio");
qDebug() << getStringByStrid("pt_BR", "stringid_disc");
qDebug() << getStringByStrid("pt_BR", "stringid_setup");

qDebug() << getStringByStrid("ar_AE", "stringid_homepage");
qDebug() << getStringByStrid("ar_AE", "stringid_ipod");
qDebug() << getStringByStrid("ar_AE", "stringid_usb");
qDebug() << getStringByStrid("ar_AE", "stringid_miracast");
qDebug() << getStringByStrid("ar_AE", "stringid_hdmi");
qDebug() << getStringByStrid("ar_AE", "stringid_aux");
qDebug() << getStringByStrid("ar_AE", "stringid_usbipod");
qDebug() << getStringByStrid("ar_AE", "stringid_btaudio");
qDebug() << getStringByStrid("ar_AE", "stringid_disc");
qDebug() << getStringByStrid("ar_AE", "stringid_setup");

qDebug() << getStringByStrid("en_US", "stringid_phone");
qDebug() << getStringByStrid("en_US", "stringid_media");
qDebug() << getStringByStrid("en_US", "stringid_navi");
qDebug() << getStringByStrid("en_US", "stringid_radio2");
qDebug() << getStringByStrid("en_US", "stringid_destsearch");
qDebug() << getStringByStrid("en_US", "stringid_qibla");
qDebug() << getStringByStrid("en_US", "stringid_mapnotinstall");
qDebug() << getStringByStrid("en_US", "stringid_prayeronn");
qDebug() << getStringByStrid("en_US", "stringid_radio");
qDebug() << getStringByStrid("en_US", "stringid_none");
qDebug() << getStringByStrid("en_US", "stringid_news");
qDebug() << getStringByStrid("en_US", "stringid_affairs");
qDebug() << getStringByStrid("en_US", "stringid_info");
qDebug() << getStringByStrid("en_US", "stringid_sport");
qDebug() << getStringByStrid("en_US", "stringid_educate");
qDebug() << getStringByStrid("en_US", "stringid_drama");
qDebug() << getStringByStrid("en_US", "stringid_culture");
qDebug() << getStringByStrid("en_US", "stringid_science");
qDebug() << getStringByStrid("en_US", "stringid_varied");
qDebug() << getStringByStrid("en_US", "stringid_popmusic");
#if 0
qDebug() << getStringByStrid("en_US", "stringid_rockmusic");
qDebug() << getStringByStrid("en_US", "stringid_easymusic");
qDebug() << getStringByStrid("en_US", "stringid_lightmusic");
qDebug() << getStringByStrid("en_US", "stringid_classmusic");
qDebug() << getStringByStrid("en_US", "stringid_othermusic");
qDebug() << getStringByStrid("en_US", "stringid_weather");
qDebug() << getStringByStrid("en_US", "stringid_finance");
qDebug() << getStringByStrid("en_US", "stringid_children");
qDebug() << getStringByStrid("en_US", "stringid_social");
qDebug() << getStringByStrid("en_US", "stringid_religion");
qDebug() << getStringByStrid("en_US", "stringid_phonein");
qDebug() << getStringByStrid("en_US", "stringid_travel");
qDebug() << getStringByStrid("en_US", "stringid_leisure");
qDebug() << getStringByStrid("en_US", "stringid_jazzmusic");
qDebug() << getStringByStrid("en_US", "stringid_countrymusic");
qDebug() << getStringByStrid("en_US", "stringid_nationalmusic");
qDebug() << getStringByStrid("en_US", "stringid_oldiesmusic");
qDebug() << getStringByStrid("en_US", "stringid_folkmusic");
qDebug() << getStringByStrid("en_US", "stringid_document");
qDebug() << getStringByStrid("en_US", "stringid_test");
qDebug() << getStringByStrid("en_US", "stringid_alarm");
qDebug() << getStringByStrid("en_US", "stringid_aswilloverwrite");
qDebug() << getStringByStrid("en_US", "stringid_pleasewait");
qDebug() << getStringByStrid("en_US", "stringid_seekpty");
qDebug() << getStringByStrid("en_US", "stringid_seek");
qDebug() << getStringByStrid("en_US", "stringid_confirmation");
qDebug() << getStringByStrid("en_US", "stringid_as");
qDebug() << getStringByStrid("en_US", "stringid_cancel");
qDebug() << getStringByStrid("en_US", "stringid_attention");
qDebug() << getStringByStrid("en_US", "stringid_trafficalert");
qDebug() << getStringByStrid("en_US", "stringid_media2");
qDebug() << getStringByStrid("en_US", "stringid_disconnected");
qDebug() << getStringByStrid("en_US", "stringid_isdisconnecting");
qDebug() << getStringByStrid("en_US", "stringid_connectfailed");
qDebug() << getStringByStrid("en_US", "stringid_connected");
qDebug() << getStringByStrid("en_US", "stringid_displaymcuver");
qDebug() << getStringByStrid("en_US", "stringid_boardid");
qDebug() << getStringByStrid("en_US", "stringid_btmodulever");
qDebug() << getStringByStrid("en_US", "stringid_m");
qDebug() << getStringByStrid("en_US", "stringid_h");
qDebug() << getStringByStrid("en_US", "stringid_d");
qDebug() << getStringByStrid("en_US", "stringid_y");
qDebug() << getStringByStrid("en_US", "stringid_pinerror");
qDebug() << getStringByStrid("en_US", "stringid_trytimes");
qDebug() << getStringByStrid("en_US", "stringid_pin");
qDebug() << getStringByStrid("en_US", "stringid_speedpulse");
qDebug() << getStringByStrid("en_US", "stringid_password");
qDebug() << getStringByStrid("en_US", "stringid_servicesexpiry");
qDebug() << getStringByStrid("en_US", "stringid_mediasettingosd");
qDebug() << getStringByStrid("en_US", "stringid_mediasettings");
qDebug() << getStringByStrid("en_US", "stringid_flat");
qDebug() << getStringByStrid("en_US", "stringid_classic");
qDebug() << getStringByStrid("en_US", "stringid_rock");
qDebug() << getStringByStrid("en_US", "stringid_pop");
qDebug() << getStringByStrid("en_US", "stringid_live");
qDebug() << getStringByStrid("en_US", "stringid_jazz");
qDebug() << getStringByStrid("en_US", "stringid_dance");
qDebug() << getStringByStrid("en_US", "stringid_treble");
qDebug() << getStringByStrid("en_US", "stringid_middle");
#endif
#if 0
qDebug() << getStringByStrid("en_US", "stringid_bass");
qDebug() << getStringByStrid("en_US", "stringid_voicecommand");
qDebug() << getStringByStrid("en_US", "stringid_timeout");
qDebug() << getStringByStrid("en_US", "stringid_invalidcommand");
qDebug() << getStringByStrid("en_US", "stringid_plzconnectbt");
qDebug() << getStringByStrid("en_US", "stringid_plzspeakbeep");
qDebug() << getStringByStrid("en_US", "stringid_invalidnumber");
qDebug() << getStringByStrid("en_US", "stringid_callfullname");
qDebug() << getStringByStrid("en_US", "stringid_vcprepare");
qDebug() << getStringByStrid("en_US", "stringid_vcupdated");
qDebug() << getStringByStrid("en_US", "stringid_volumecontrol");
qDebug() << getStringByStrid("en_US", "stringid_navigation");
qDebug() << getStringByStrid("en_US", "stringid_phone3");
qDebug() << getStringByStrid("en_US", "stringid_externalmedia");
qDebug() << getStringByStrid("en_US", "stringid_media3");
qDebug() << getStringByStrid("en_US", "stringid_prayer");
qDebug() << getStringByStrid("en_US", "stringid_statusbar");
qDebug() << getStringByStrid("en_US", "stringid_voicecomm");
qDebug() << getStringByStrid("en_US", "stringid_generalsettings");
qDebug() << getStringByStrid("en_US", "stringid_mediasettings2");
qDebug() << getStringByStrid("en_US", "stringid_toyotaparkassist");
qDebug() << getStringByStrid("en_US", "stringid_soundsettings");
qDebug() << getStringByStrid("en_US", "stringid_wirelessconnection");
qDebug() << getStringByStrid("en_US", "stringid_wirelesssettings");
qDebug() << getStringByStrid("en_US", "stringid_radiofm");
qDebug() << getStringByStrid("en_US", "stringid_radioam");
qDebug() << getStringByStrid("en_US", "stringid_noradiosignal");
qDebug() << getStringByStrid("en_US", "stringid_nodisc");
qDebug() << getStringByStrid("en_US", "stringid_nobtdevice");
qDebug() << getStringByStrid("en_US", "stringid_nousbdevice");
qDebug() << getStringByStrid("en_US", "stringid_nohdmidevice");
qDebug() << getStringByStrid("en_US", "stringid_nowificonn");
qDebug() << getStringByStrid("en_US", "stringid_wifidisplaydisconn");
qDebug() << getStringByStrid("en_US", "stringid_discinserted");
qDebug() << getStringByStrid("en_US", "stringid_usbdevice");
qDebug() << getStringByStrid("en_US", "stringid_ipodiphone");
qDebug() << getStringByStrid("en_US", "stringid_wifidisplaydev");
qDebug() << getStringByStrid("en_US", "stringid_general");
qDebug() << getStringByStrid("en_US", "stringid_unsupportedfs");
qDebug() << getStringByStrid("en_US", "stringid_network");
qDebug() << getStringByStrid("en_US", "stringid_wifi3g");
qDebug() << getStringByStrid("en_US", "stringid_unabletoplayavfront");
qDebug() << getStringByStrid("en_US", "stringid_usbnoresp");
qDebug() << getStringByStrid("en_US", "stringid_unsupportedusb");
qDebug() << getStringByStrid("en_US", "stringid_usbhubnotsupported");
qDebug() << getStringByStrid("en_US", "stringid_eula");
qDebug() << getStringByStrid("en_US", "stringid_enduserlicagree");
qDebug() << getStringByStrid("en_US", "stringid_dontshowagain");
qDebug() << getStringByStrid("en_US", "stringid_agree");
qDebug() << getStringByStrid("en_US", "stringid_previous");
qDebug() << getStringByStrid("en_US", "stringid_next");
qDebug() << getStringByStrid("en_US", "stringid_setlangplzrefrain");
qDebug() << getStringByStrid("en_US", "stringid_preparing");
qDebug() << getStringByStrid("en_US", "stringid_autoaccept");
qDebug() << getStringByStrid("en_US", "stringid_skip");
#endif
} // for loop

}

void test_all()
{

}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test_cache();

    return 0;
}
